
set(TARGET_LIB_NAME ${CMAKE_PROJECT_NAME}_lib)

add_library(${TARGET_LIB_NAME}
  src/zaber_control.cpp
  src/zaber_device.cpp
  src/zaber_types.cpp
  src/zaber_rotary.cpp
  src/zaber_linear.cpp
 )

target_include_directories(${TARGET_LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


# setup export preprocessor definitions
if(BUILD_SHARED_LIBS)
  target_compile_definitions(${TARGET_LIB_NAME} PRIVATE FAREWELLER_EXPORTS)
  target_compile_definitions(${TARGET_LIB_NAME} INTERFACE FAREWELLER_IMPORTS)
endif()

target_link_libraries(${TARGET_LIB_NAME} ${LIBRARIES})

set(APP_SRC main.cpp)
add_executable(${CMAKE_PROJECT_NAME}_app  ${APP_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME}_app ${TARGET_LIB_NAME})


if(TESTS_ENABLED)
  message(STATUS "Testing enabled.")
  add_subdirectory(test)
else()
  message(STATUS "Testing disabled.")
endif()
