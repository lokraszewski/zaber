
add_executable(zaber_example main.cpp )

target_include_directories(zaber_example
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(zaber_example
  ${PROJECT_NAME}
)

set_target_properties(zaber_example
  PROPERTIES
    CXX_STANDARD 14
)
