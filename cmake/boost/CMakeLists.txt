# Check version requirement
cmake_minimum_required(VERSION 3.19)

project(boost)
include(ExternalProject)


set(CMAKE_BOOST_BUILD_TYPE "Boost build - Release/Debug " CACHE STRING "Release")


# Allow boost to be compiled with debug flag
if(CMAKE_BOOST_BUILD_TYPE STREQUAL "Debug")
  set(BOOST_VARIANT "debug")
else()
  set(BOOST_VARIANT "release")
endif()
message(STATUS "Building Boost in " ${BOOST_VARIANT} " mode")

# LOGS
# message(STATUS "Boost is built using python  :  ${Python_VERSION_MAJOR}.${Python_VERSION_MINOR} ;")

# Determine the build system
message(STATUS "THE LOCAL BUILD SYSTEM NAME IS : ${CMAKE_SYSTEM_NAME}")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX_BUILD ON)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(MACOS_BUILD ON)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows" AND MINGW)
  set(WINDOWS_BUILD ON)
else()
  message(FATAL_ERROR
"The build is only configured for Linux, Windows(MINGW), and Darwin(Macos)."
  )
endif()

if(WINDOWS_BUILD)
  list(APPEND CONFIGURE_COMMAND
    cd tools/build && bootstrap.bat mingw
  )
  list(APPEND BUILD_COMMAND
    ${BOOST_SOURCE}/tools/build/b2 -d0
    toolset=gcc 
  )
elseif(MACOS_BUILD)
  list(APPEND CONFIGURE_COMMAND
    ./bootstrap.sh
  )
  list(APPEND BUILD_COMMAND
    ./b2 -d0
    toolset=darwin
  )
else()
  list(APPEND CONFIGURE_COMMAND
    ./bootstrap.sh
  )
  list(APPEND BUILD_COMMAND
    ./b2 -d0
    toolset=gcc 
  )
endif()

# file(WRITE ${DEPS_BUILD_DIR}/boost/user-config.jam "using python  :  ${Python_VERSION_MAJOR}.${Python_VERSION_MINOR} ;")

list(APPEND BUILD_COMMAND
    # --user-config=${DEPS_BUILD_DIR}/boost/user-config.jam
    --build-dir=${DEPS_BUILD_DIR}/boost/build
    --with-program_options --with-random --with-headers
    --prefix=${DEPS_INSTALL_PREFIX}/boost install
    cxxflags=-fPIC cflags=-fPIC 
    # toolset=gcc link=shared
    link=static
    variant=${BOOST_VARIANT}
)

message(STATUS "The boost configure command is : ${CONFIGURE_COMMAND}")
message(STATUS "The boost build command is : ${BUILD_COMMAND}")

ExternalProject_Add(external_boost
  SOURCE_DIR  ${BOOST_SOURCE}/
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
  BUILD_COMMAND ${BUILD_COMMAND}
  INSTALL_COMMAND ""
)