CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

PROJECT(DPS VERSION 0.0.1)

# Set C++ standard
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Add submodules
INCLUDE(add_git_submodule)
# get spdlog
add_submodule("${CMAKE_SOURCE_DIR}/third-party/spdlog/")

# Add src subdirectory
ADD_SUBDIRECTORY(src)

# Add tests
IF(DEFINED DPS_ENABLE_TESTS)
    # add gtest
    add_submodule("${CMAKE_SOURCE_DIR}/third-party/googletest/")
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
