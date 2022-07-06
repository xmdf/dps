/**
 * @file dps_tests_main.hpp
 * @author xmdf
 * @date 05 July 2022
 * @brief Main driver for DPS tests
 */

//#include ""

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    // turn off logging for tests
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

