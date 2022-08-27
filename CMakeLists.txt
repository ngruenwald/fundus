cmake_minimum_required(VERSION 3.15)

project(fundus VERSION 1.0.2 LANGUAGES CXX)

option(VERSIONED_INSTALL "Install into versioned folders" ON)

set(HEADER_INSTALL_DIR include/fundus)
set(CONFIG_INSTALL_DIR lib/cmake/fundus)

if(VERSIONED_INSTALL)
  set(HEADER_INSTALL_DIR ${HEADER_INSTALL_DIR}/${PROJECT_VERSION})
  set(CONFIG_INSTALL_DIR ${CONFIG_INSTALL_DIR}-${PROJECT_VERSION})
endif()

add_library(fundus INTERFACE)
add_library(fundus::fundus ALIAS fundus)

target_include_directories(
  fundus
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${HEADER_INSTALL_DIR}>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  fundusConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(TARGETS fundus EXPORT fundusTargets)
install(DIRECTORY common DESTINATION ${HEADER_INSTALL_DIR})

install(
  EXPORT fundusTargets
  FILE fundusTargets.cmake
  NAMESPACE fundus::
  DESTINATION ${CONFIG_INSTALL_DIR}
)

install(
  FILES fundusConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/fundusConfigVersion.cmake
  DESTINATION ${CONFIG_INSTALL_DIR}
)
