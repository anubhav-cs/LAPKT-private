target_include_directories(core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

add_subdirectory(lapkt)

if(BUILD_PYTHON_PKG)
    add_subdirectory(extensions)
    add_subdirectory(python_pkg)
endif()