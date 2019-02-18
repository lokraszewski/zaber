add_library(${PROJECT_NAME}
  src/zaber_control.cpp
  src/zaber_device.cpp
  src/zaber_types.cpp
  src/zaber_rotary.cpp
  src/zaber_linear.cpp
 )

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  serial
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 14
)



include(GNUInstallDirs)

set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${PROJECT_SOURCE_DIR}/generated")
# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    ${version_config} COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)


# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${TARGETS_EXPORT_NAME}
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES
      "${project_config}"
      "${version_config}"
    DESTINATION
      "${config_install_dir}"
)


# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT
      "${TARGETS_EXPORT_NAME}"
    NAMESPACE
      "${namespace}"
    DESTINATION
      "${config_install_dir}"
)


# set(APP_SRC main.cpp)
# add_executable(${CMAKE_PROJECT_NAME}_app  ${APP_SRC})
# target_link_libraries(${CMAKE_PROJECT_NAME}_app ${TARGET_LIB_NAME})


# message(STATUS "Testing : ${TESTS_ENABLED}")
# if(TESTS_ENABLED)
#   add_subdirectory(test)
# endif()
