


file(GLOB_RECURSE TESTS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/Catch/single_include/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

foreach( test_file ${TESTS_FILES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${test_file} )

    message("Adding ${testname} made from ${test_file}, linking with ${PROJECT_NAME}")

    add_executable( ${testname}
      ${test_file} )

    # Make sure YourLib is linked to each app
    target_link_libraries( ${testname}
      ${PROJECT_NAME}
      Catch
      )

    set_target_properties( ${testname}
      PROPERTIES
        CXX_STANDARD 14
    )
endforeach( test_file ${APP_SOURCES} )




