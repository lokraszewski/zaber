
file(GLOB_RECURSE TESTS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach( test_file ${TESTS_FILES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${test_file} )

    message("Adding ${testname} made from ${test_file}, linking with ${PROJECT_NAME}")

    add_executable( ${testname}
      ${test_file} )

    # Make sure YourLib is linked to each app
    target_link_libraries( ${testname}
      ${PROJECT_NAME}
      CONAN_PKG::spdlog
      CONAN_PKG::catch2
      )

    set_target_properties( ${testname}
      PROPERTIES
        CXX_STANDARD 14
    )
endforeach( test_file ${APP_SOURCES} )




