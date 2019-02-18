cmake_minimum_required(VERSION 3.9)

project(zaber
  VERSION 1.0.0
  LANGUAGES CXX
  )

include(cmake/conan.cmake)

# Enable/disable testing
option(TESTS_ENABLED "Enable automatic tests" ON)
option(EXAMPLE_ENABLED "Enable application example" OFF)
option(COVERAGE_ENABLED "Enable test coverage" OFF)


set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Spdlog
set(spdlog_SOURCE_DIR vendor/spdlog)
include_directories(${spdlog_SOURCE_DIR}/include)

# FMT library.
add_subdirectory(vendor/fmt EXCLUDE_FROM_ALL)
set(LIBRARIES ${LIBRARIES} fmt::fmt-header-only)

# Serial lib
add_subdirectory(vendor/serial)
set(LIBRARIES ${LIBRARIES} serial)

# cxxopts
add_subdirectory(vendor/cxxopts)
set(LIBRARIES ${LIBRARIES} cxxopts)

message(STATUS "Finished adding libraries: ")
foreach (_lib ${LIBRARIES})
    message(STATUS "  ${_lib}")
endforeach()

add_subdirectory(${PROJECT_NAME})

message("${TESTS_ENABLED}")
message("${EXAMPLE_ENABLED}")

if(TESTS_ENABLED)
add_subdirectory(test)
endif(TESTS_ENABLED)

if(EXAMPLE_ENABLED)
add_subdirectory(example)
endif(EXAMPLE_ENABLED)

