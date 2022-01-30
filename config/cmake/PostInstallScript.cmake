message("\n# x-x-x-x POST-INSTALL THINGS BEGIN HERE x-x-x-x #\n")


find_package(Python3 COMPONENTS Interpreter Development)
if(${Python3_VERSION} LESS 3.7)
    message(SEND_ERROR 
        "INCOMPATIBLE PYTHON VERSION, expected >3.7.x but found - " 
        ${Python3_VERSION})
endif()

# Install the pip package
execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install .
WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
RESULT_VARIABLE out
)

message("\n# x-x-x-x POST-INSTALL THINGS END HERE x-x-x-x #\n")