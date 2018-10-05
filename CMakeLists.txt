
cmake_minimum_required(VERSION 2.8)

project(zaber)
set(PROJECT_VERSION 0.0.0)
set(PROJECT_BRIEF "\"Driver for the zaber motion control modules. \"")


# Enable/disable testing
option(TESTS_ENABLED "Enable automatic tests" OFF)
# Enable/disable test coverage
option(COVERAGE_ENABLED "Enable test coverage" OFF)
# Turn on verbose makefile.
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

if(COVERAGE_ENABLED)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -fPIC -O0 -ggdb -fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -ggdb")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Doxygen module search.
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_subdirectory(zaber)
