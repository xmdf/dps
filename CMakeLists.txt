CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

PROJECT(DPS VERSION 1.23.4)

# Set C++ standard
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Add submodules
INCLUDE(add_git_submodule)
add_submodule("third-party/spdlog/")

# Add src subdirectory
ADD_SUBDIRECTORY(src)

# Add tests
IF(DEFINED DPS_ENABLE_TESTS)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
