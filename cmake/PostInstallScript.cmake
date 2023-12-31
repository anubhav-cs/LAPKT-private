message(STATUS "\n# x-x-x-x POST-INSTALL THINGS BEGIN HERE x-x-x-x #\n")

find_package(Python3 COMPONENTS Interpreter Development)
if(${Python3_VERSION} VERSION_LESS 3.8.0)
    message(SEND_ERROR 
        "INCOMPATIBLE PYTHON VERSION, expected >=3.8.x but found - " 
        ${Python3_VERSION})
endif()

# Install the pip package
# execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install .
#     WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/_pip_installable_pkg
#     RESULT_VARIABLE out
# )

message(STATUS "\n# x-x-x-x POST-INSTALL THINGS END HERE x-x-x-x #\n")
