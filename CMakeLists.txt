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

conan_cmake_run(
  REQUIRES fmt/5.2.1@bincrafters/stable
  REQUIRES spdlog/1.2.1@bincrafters/stable
  REQUIRES catch2/2.4.1@bincrafters/stable
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD fmt spdlog catch2 boost
)

# Serial lib
add_subdirectory(vendor/serial)
set(LIBRARIES ${LIBRARIES} serial)

# cxxopts
add_subdirectory(vendor/cxxopts)
set(LIBRARIES ${LIBRARIES} cxxopts)

add_subdirectory(${PROJECT_NAME})

if(TESTS_ENABLED)
add_subdirectory(test)
endif(TESTS_ENABLED)

if(EXAMPLE_ENABLED)
add_subdirectory(example)
endif(EXAMPLE_ENABLED)

