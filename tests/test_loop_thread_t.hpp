/**
 * @file thread_t_TESTER.hpp 
 * @author xmdf
 * @date 02 August 2022
 * @brief
 */

#ifndef __DPS_TESTER_thread_t_HPP__
#define __DPS_TESTER_thread_t_HPP__

#include <atomic>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include "macros.hpp"
#include "loop_thread_t.hpp"


class loop_thread_t_TESTER
    : public dps::loop_thread_t
    , public testing::Test
{
public:
    loop_thread_t_TESTER()
    : dps::loop_thread_t{loop_thread_t_TESTER::thread_function}
    , testing::Test{}
    {
    }

    static void thread_function(
        std::atomic<bool> &should_run)
    {
        while (should_run.load()) {}
    }
};


TEST_F(loop_thread_t_TESTER, Construction)
{
    EXPECT_FALSE(this->has_started());
    EXPECT_FALSE(this->is_complete());
}

TEST_F(loop_thread_t_TESTER, Start)
{
    this->start();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    EXPECT_TRUE(this->has_started());
    this->start();
    EXPECT_TRUE(this->has_started());
}

TEST_F(loop_thread_t_TESTER, RequestStop)
{
    this->start();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    EXPECT_TRUE(this->has_started());
    this->request_stop();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    EXPECT_TRUE(this->is_complete());
}

TEST_F(loop_thread_t_TESTER, Stop)
{
    this->start();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    EXPECT_TRUE(this->has_started());
    this->stop();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    EXPECT_TRUE(this->is_complete());
}

#endif // __DPS_TESTER_thread_t_HPP__
