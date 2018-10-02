set(TARGET ultra_flex_lib)
set(TEST_TARGET ${TARGET}_test)
file(GLOB_RECURSE TESTS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

 message(STATUS "Test files: " ${TESTS_FILES})

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/Catch/single_include/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(${TEST_TARGET} ${TESTS_FILES})
target_link_libraries(
    ${TEST_TARGET}
    ${TARGET}
    ${LIBRARIES}
    Catch
)

