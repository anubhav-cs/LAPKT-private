# #
# target_include_directories(lapkt PRIVATE ${Python_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} )
# target_link_libraries( lapkt PRIVATE
#     lapkt 
#     ${Boost_LIBRARIES}
#     )

add_subdirectory(pybinding)


add_subdirectory(tarski)

add_subdirectory(fd)



# file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/__init__.py "from .libpddl_py_interface import *")
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/lapkt/interface
#     COMPONENT Runtime
#     )
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/lapkt/interface
#     COMPONENT Development EXCLUDE_FROM_ALL
#     )
