CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

PROJECT(DPS VERSION 0.0.1)

# Set C++ standard
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

LIST(APPEND CMAKE_MODULE_PATH "third-party/spdlog/cmake")

# Add Third-party directory
ADD_SUBDIRECTORY(third-party)

# Add src subdirectory
ADD_SUBDIRECTORY(src)

# Add tests
IF(DEFINED DPS_ENABLE_TESTS)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
