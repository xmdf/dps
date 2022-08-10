# DPS_HEADER

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

FUNCTION(fetch_gtest)

    INCLUDE(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

ENDFUNCTION(fetch_gtest)
