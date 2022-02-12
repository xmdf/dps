/**
 * @file dps_tests_main.hpp
 * @author xmdf
 * @date 12 February 2022
 * @brief
 */

//#include ""

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
    // turn off logging for tests
    spdlog::set_level(spdlog::level::off);
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

