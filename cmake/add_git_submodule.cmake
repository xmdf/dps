
# https://www.scivision.dev/cmake-git-submodule/

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

FUNCTION(add_submodule dir)
    # add a Git submodule directory to CMake, assuming the
    # Git submodule directory is a CMake project.
    #
    # Usage: in CMakeLists.txt
    #
    # INCLUDE(add_git_submodule.cmake)
    # add_submodule(dir)

    FIND_PACKAGE(Git REQUIRED)

    IF(NOT EXISTS ${dir}/CMakeLists.txt)
        EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${dir}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                COMMAND_ERROR_IS_FATAL ANY)
    ENDIF()

    ADD_SUBDIRECTORY(${dir})

ENDFUNCTION(add_submodule)