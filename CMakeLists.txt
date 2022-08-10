# DPS_HEADER

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

PROJECT(DPS
        VERSION 0.0.1
        DESCRIPTION "Distributed pub-sub network"
        )

# Set C++ standard
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

###############################################################
# For development only
LIST(APPEND CMAKE_PREFIX_PATH "/Users/mattfalcone/home/root")
###############################################################

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Check for tests enabled
IF(NOT DEFINED DPS_ENABLE_TESTS)
    SET(DPS_ENABLE_TESTS 0)
ELSE()
    SET(DPS_ENABLE_TESTS 1)
ENDIF()

# Add src subdirectory
ADD_SUBDIRECTORY(src)

# Add tests
IF(${DPS_ENABLE_TESTS} EQUAL 1)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()


