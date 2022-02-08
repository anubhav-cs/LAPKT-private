#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#
#xxxx SECTION 1 - PREREQUISITES

#----SECTION 1.1 -Install python prerequisites ----#

# Fetch Python Exec
find_package(Python3 COMPONENTS Interpreter Development)
if(${Python3_VERSION} VERSION_LESS 3.7.0)
    message(SEND_ERROR 
        "INCOMPATIBLE PYTHON VERSION, expected >3.7.x but found - " 
        ${Python3_VERSION})
endif()
message("The PYTHON_VERSION is ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")

# Install pip requirements
execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install 
    -r ${PROJECT_SOURCE_DIR}/config/pre_build/pip_requirements.txt
    RESULT_VARIABLE out
)
message(STATUS "Python result: ${out}")

#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#
#xxxx SECTION 2 - ADD EXTERNAL PROJECTS

include(ExternalProject)
set(CMAKE_CXX_STANDARD 17)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)

# Dependencies of LAPKT
set(DEPENDENCIES)  

# DOXYGEN EXTRACT BINARIES
list(APPEND DEPENDENCIES 
    external_doxygen
)
ExternalProject_Add( external_doxygen
    URL https://sourceforge.net/projects/doxygen/files/rel-1.9.3/doxygen-1.9.3.linux.bin.tar.gz
    URL_MD5 3aa5c8b282f194f0d0d3e9c5b8010e20
    DOWNLOAD_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}
    SOURCE_DIR  ${CUSTOM_EXT_INSTALL_PREFIX}/doxygen
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "" # ./b2 install
)
list (APPEND EXTRA_CMAKE_ARGS
    -DDOXYGEN_ROOT=${CUSTOM_EXT_INSTALL_PREFIX}/doxygen
)

# BUILD BOOST

list(APPEND DEPENDENCIES 
    external_boost 
)

# Allow boost to be compiled with debug flag
if(CMAKE_BOOST_BUILD_TYPE STREQUAL "Debug")
    set(BOOST_VARIANT "debug")
else()
    set(BOOST_VARIANT "release")
endif()
message("Building Boost in " ${BOOST_VARIANT} " mode")
file(WRITE ${CUSTOM_EXT_BUILD_DIR}/boost/user-config.jam "using python  :  ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR} ;")

# LOGS
message("Boost is built using python  :  ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR} ;")
message("The boost build command is :  b2 --user-config=${CUSTOM_EXT_BUILD_DIR}/boost/user-config.jam --with-python --with-program_options --build-dir=${CUSTOM_EXT_BUILD_DIR}/boost/build toolset=gcc variant=${BOOST_VARIANT} optimization=space link=shared install")

# 
message(STATUS "test ---${CUSTOM_EXT_BUILD_DIR}/boost/src/tools/build")
ExternalProject_Add( external_boost
    URL https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.bz2
    URL_MD5 db0112a3a37a3742326471d20f1a186a
    DOWNLOAD_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}
    TMP_DIR     ${CUSTOM_EXT_BUILD_DIR}/boost/tmp
    SOURCE_DIR  ${CUSTOM_EXT_BUILD_DIR}/boost/src
    # SOURCE_SUBDIR  tools/build
    BUILD_IN_SOURCE 1
    #INSTALL_DIR ${PROJECT_BINARY_DIR}/boost/lib
    #CONFIGURE_COMMAND ./bootstrap.sh --libdir=${CMAKE_INSTALL_PREFIX}/lib/lapkt/boost --includedir=${CMAKE_INSTALL_PREFIX}/include
    CONFIGURE_COMMAND cd tools/build && bootstrap.bat mingw  
    BUILD_COMMAND ${CUSTOM_EXT_BUILD_DIR}/boost/src/tools/build/b2 
        --user-config=${CUSTOM_EXT_BUILD_DIR}/boost/user-config.jam 
        --build-dir=${CUSTOM_EXT_BUILD_DIR}/boost/build 
        --with-random --with-python --with-program_options 
        toolset=gcc variant=${BOOST_VARIANT} optimization=space link=static 
        --prefix=${CUSTOM_EXT_INSTALL_PREFIX}/boost install
    INSTALL_COMMAND ""
)
# ExternalProject_Add_Step(external_boost build_custom
#     WORKING_DIRECTORY ${CUSTOM_EXT_BUILD_DIR}/boost/src/tools/build/
#     COMMAND ./b2 --user-config=${CUSTOM_EXT_BUILD_DIR}/boost/user-config.jam --with-python --with-program_options --build-dir=${CUSTOM_EXT_BUILD_DIR}/boost/build toolset=gcc variant=${BOOST_VARIANT} optimization=space link=static install
# )
# ExternalProject_Add_StepDependencies(external_boost build_custom external_boost)
# Set the path to find Boost Cmake Config
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CUSTOM_EXT_INSTALL_PREFIX}/boost/lib/cmake/Boost-1.78.0")

list (APPEND EXTRA_CMAKE_ARGS
    -DBOOST_ROOT=${CUSTOM_EXT_INSTALL_PREFIX}/boost
    -DBOOST_INCLUDEDIR=${BOOST_ROOT}/include
    -DBOOST_LIBRARYDIR=${BOOST_ROOT}/lib
#   -DBoost_NO_SYSTEM_PATHS=ON
#   -DBoost_REALPATH=ON
#   -DBoost_NO_BOOST_CMAKE=ON
)

# COPY FD PY LIB
# Update the submodule if not done manually 
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external_package/fd_translate/translate.py)
  find_package(Git REQUIRED)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND_ERROR_IS_FATAL ANY)
endif()

# BUILD FF
if(CMAKE_FF_CXX OR CMAKE_FF_PYWRAPPER)
    list(APPEND DEPENDENCIES 
        external_ff
    )
    ExternalProject_Add(external_ff
        GIT_REPOSITORY https://github.com/LAPKT-dev/libff_parser
        SOURCE_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}/libff
        #SOURCE_SUBDIR src
        BINARY_DIR ${CUSTOM_EXT_BUILD_DIR}/ff/build
        INSTALL_DIR ${CUSTOM_EXT_INSTALL_PREFIX}/ff
        #GIT_REMOTE_UPDATE_STRATEGY    CHECKOUT
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CUSTOM_EXT_INSTALL_PREFIX}/ff
        # INSTALL_COMMAND  cmake --install ${PROJECT_BINARY_DIR}/../build_external/ff/build 
    )
endif(CMAKE_FF_CXX OR CMAKE_FF_PYWRAPPER)
list (APPEND EXTRA_CMAKE_ARGS
    -DFF_ROOT=${CUSTOM_EXT_INSTALL_PREFIX}/ff
)

# BUILD KCL-VAL
if(CMAKE_VAL)
    list(APPEND DEPENDENCIES 
        external_VAL
    )
    ExternalProject_Add( external_VAL
        GIT_REPOSITORY https://github.com/KCL-Planning/VAL
        SOURCE_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}/VAL
        BINARY_DIR ${CUSTOM_EXT_BUILD_DIR}/VAL
        INSTALL_DIR ${CUSTOM_EXT_INSTALL_PREFIX}/VAL
        #GIT_REMOTE_UPDATE_STRATEGY    CHECKOUT
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CUSTOM_EXT_INSTALL_PREFIX}/VAL
        INSTALL_COMMAND ""
    )
endif(CMAKE_VAL)

# BUILD CATCH2
list(APPEND DEPENDENCIES 
    external_catch2
)
ExternalProject_Add(external_catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG  v3.0.0-preview4
    SOURCE_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}/Catch2
    #SOURCE_SUBDIR src
    BINARY_DIR ${CUSTOM_EXT_BUILD_DIR}/Catch2/build
    INSTALL_DIR ${CUSTOM_EXT_INSTALL_PREFIX}/Catch2
    #GIT_REMOTE_UPDATE_STRATEGY    CHECKOUT
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CUSTOM_EXT_INSTALL_PREFIX}/Catch2
    # INSTALL_COMMAND  cmake --install ${PROJECT_BINARY_DIR}/../build_external/Catch2/build 
)
list (APPEND EXTRA_CMAKE_ARGS
    -DCATCH2_ROOT=${CUSTOM_EXT_INSTALL_PREFIX}/Catch2
)
# CLINGO BINARIES
list(APPEND DEPENDENCIES 
    external_clingo_linux 
)
ExternalProject_Add( external_clingo_linux
    URL https://github.com/potassco/clingo/releases/download/v5.4.0/clingo-5.4.0-linux-x86_64.tar.gz
    URL_MD5 d8e5767d1f482ddfc98d010191422af8
    DOWNLOAD_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}
    SOURCE_DIR  ${CUSTOM_EXT_INSTALL_PREFIX}/clingo/linux
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "" # ./b2 install
)

list(APPEND DEPENDENCIES 
    external_clingo_darwin
)
ExternalProject_Add( external_clingo_darwin
    URL https://github.com/potassco/clingo/releases/download/v5.4.0/clingo-5.4.0-macos-x86_64.tar.gz
    URL_MD5 64b46fde3a75e02368c25cd9f2d37029
    DOWNLOAD_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}
    SOURCE_DIR  ${CUSTOM_EXT_INSTALL_PREFIX}/clingo/darwin
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "" # ./b2 install
)

list(APPEND DEPENDENCIES 
    external_clingo_win32 
)
ExternalProject_Add( external_clingo_win32
    URL https://github.com/potassco/clingo/releases/download/v5.4.0/clingo-5.4.0-win64.zip
    URL_MD5 61815445476e20d4ce4f00060626d2da
    DOWNLOAD_DIR ${CUSTOM_EXT_DOWNLOAD_DIR}
    SOURCE_DIR  ${CUSTOM_EXT_INSTALL_PREFIX}/clingo/win32
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "" # ./b2 install
)


#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#
#xxxx SECTION 3 - CALL THE MAIN SCRIPT TO BUILD LAPKT
    
list(APPEND EXTRA_CMAKE_ARGS
    -DUSE_SUPERBUILD=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

get_cmake_property(vars CACHE_VARIABLES)
foreach(var ${vars})
  get_property(currentHelpString CACHE "${var}" PROPERTY HELPSTRING)
    if("${currentHelpString}" MATCHES "No help, variable specified on the command line." OR "${currentHelpString}" STREQUAL "")
        # message("${var} = [${${var}}]  --  ${currentHelpString}") # uncomment to see the variables being processed
        list(APPEND EXTRA_CMAKE_ARGS "-D${var}=${${var}}")
    endif()
endforeach()

ExternalProject_Add (external_lapkt
  DEPENDS ${DEPENDENCIES}
  SOURCE_DIR ${PROJECT_SOURCE_DIR}
  CMAKE_ARGS  ${EXTRA_CMAKE_ARGS}
  INSTALL_COMMAND ""
  BINARY_DIR ${PROJECT_BINARY_DIR})
