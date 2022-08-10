# DPS_HEADER

# fetch gtest
INCLUDE(fetch_gtest)
fetch_gtest()

# Create test library
ADD_LIBRARY(dps_tests SHARED
        test_socket_t.hpp
        test_loop_thread_t.hpp
        )

SET_TARGET_PROPERTIES(dps_tests
        PROPERTIES
        LINKER_LANGUAGE CXX)

TARGET_INCLUDE_DIRECTORIES(dps
        PUBLIC
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

TARGET_LINK_LIBRARIES(dps_tests
        dps)

ADD_EXECUTABLE(test_dps dps_tests_main.cpp)
TARGET_LINK_LIBRARIES(test_dps
        dps_tests
        gtest
        )