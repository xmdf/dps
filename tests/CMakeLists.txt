
#ADD_LIBRARY(dps_tests)

ADD_EXECUTABLE(test_dps dps_tests_main.cpp)
TARGET_LINK_LIBRARIES(test_dps
        dps
        gtest
        )