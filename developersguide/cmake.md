# Importing LAPKT in your Cmake project

There are many ways to import LAPKT, we explain three of them.  The other populates the LAPKT targets directly inside your project.

## Method 1 - Add Subdirectory

```
add_subdirectory(<PATH-TO-LAPKT-SOURCE> <BUILD-PATH>)

add_library(<lib-name> SHARED)

target_link_libraries(<lib-name> lapkt::core)
```

## Method 2 - External Project

One can build LAPKT as an external project which can be shared between multiple projects.

For this option, we would assume that LAPKT source is already downloaded and all required git-submodules have been initialized. 


1. Add the following to your root `CMakeLists.txt`

```
# Check version requirement
cmake_minimum_required(VERSION 3.19)

project(test_lapkt)

##### EXTERNAL_PROJECT

message(STATUS "Building LAPKT")

set(DEPS_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/_deps/install")
set(DEPS_BUILD_DIR "${PROJECT_BINARY_DIR}/_deps/build")

execute_process(
  COMMAND ${CMAKE_COMMAND} -S ${PROJECT_SOURCE_DIR}/cmake/lapkt
  -B ${DEPS_BUILD_DIR}/lapkt
  -DDEPS_INSTALL_PREFIX=${DEPS_INSTALL_PREFIX}
  -DDEPS_BUILD_DIR=${DEPS_BUILD_DIR}
  -DLAPKT_SOURCE=<PATH-TO-LAPKT-SOURCE>
  -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
  -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
)

execute_process(
  COMMAND ${CMAKE_COMMAND} --build  ${DEPS_BUILD_DIR}/lapkt
)

set(lapkt_ROOT ${DEPS_INSTALL_PREFIX}/lapkt)

find_package(lapkt REQUIRED core
# As of cmake-v3.12 <PackageName>_ROOT is the first path that is checked
# PATHS ${lapkt_ROOT} 
# NO_DEFAULT_PATH
)

add_library(<lib-name> SHARED)

target_link_libraries(<lib-name> lapkt::core)
```

2. Add the following to <root>/cmake/lapkt

```
# Check version requirement
cmake_minimum_required(VERSION 3.19)

project(catch2)
include(ExternalProject)

ExternalProject_Add(external_lapkt
  SOURCE_DIR ${LAPKT_SOURCE}
  BINARY_DIR ${DEPS_BUILD_DIR}/lapkt/build
  INSTALL_DIR ${DEPS_INSTALL_PREFIX}/lapkt
  CMAKE_ARGS 
    -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_PREFIX}/lapkt
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
)
```

> [!NOTE]
> `ExternalProject_Add` is very powerful with options to download LAPKT source from a url. Feel free to explore...

## Method 3 - Fetch Content

The fetch content method should be preferred if the user intends to link the project with a specific commit of LAPKT on github. 

```
include(FetchContent)

FetchContent_Declare (lapkt
    GIT_REPOSITORY <github-url>
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_TAG <commit-hash>
  )
FetchContent_MakeAvailable(lapkt)

add_library(<lib-name> SHARED)

target_link_libraries(<lib-name> lapkt::core)
```