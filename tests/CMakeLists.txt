
# fetch gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)
FetchContent_MakeAvailable(googletest)


#ADD_LIBRARY(dps_tests)

ADD_EXECUTABLE(test_dps dps_tests_main.cpp)
TARGET_LINK_LIBRARIES(test_dps
        dps
        gtest
        )