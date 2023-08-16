# Check version requirement
cmake_minimum_required(VERSION 3.19)

project(pybdin11)
include(ExternalProject)

ExternalProject_Add(external_pybind11
  SOURCE_DIR ${pybind11_SOURCE}
  BINARY_DIR ${DEPS_BUILD_DIR}/pybind11/build
  INSTALL_DIR ${DEPS_INSTALL_PREFIX}/pybind11
  CMAKE_ARGS 
    -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_PREFIX}/pybind11
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DPYBIND11_TEST=OFF
)