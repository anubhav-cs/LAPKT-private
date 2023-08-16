# Check version requirement
cmake_minimum_required(VERSION 3.19)

project(catch2)
include(ExternalProject)

ExternalProject_Add(external_catch2
  # GIT_REPOSITORY https://github.com/catchorg/Catch2
  # GIT_TAG  v3.0.0-preview4
  # URL ${PROJECT_SOURCE_DIR}/external_package/Catch2-3.0.0-preview4.tar.gz
  SOURCE_DIR ${CATCH2_SOURCE}
  #SOURCE_SUBDIR src
  BINARY_DIR ${DEPS_BUILD_DIR}/Catch2/build
  INSTALL_DIR ${DEPS_INSTALL_PREFIX}/Catch2
  #GIT_REMOTE_UPDATE_STRATEGY    CHECKOUT
  CMAKE_ARGS 
    -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_PREFIX}/Catch2
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
  # INSTALL_COMMAND  cmake --install ${PROJECT_BINARY_DIR}/../build_external/Catch2/build
)