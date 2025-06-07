#include <gtest/gtest.h>

#include <thread>

#include "os/os_looper.hpp"

using namespace never_disappear_client;
using namespace std;
using namespace std::chrono;

class basic : public testing::Test
{
protected:
    void run_looper_async()
    {
        ASSERT_FALSE(m_looper_thread.joinable());

        m_looper_thread = thread{[this]
        {
            m_test_looper.run();
            m_looper_stop_time = steady_clock::now();
        }};
    }

    void stop_looper()
    {
        m_call_stop_time = steady_clock::now();
        m_test_looper.stop();
    }

    void stop_looper_and_check_delay()
    {
        ASSERT_TRUE(m_looper_thread.joinable());

        stop_looper();
        m_looper_thread.join();

        steady_clock::duration stop_delay = m_looper_stop_time - m_call_stop_time;
        auto stop_delay_us = duration_cast<microseconds>(stop_delay).count();
        cout << "Looper stopped after " << stop_delay_us << " us." << endl;
        EXPECT_GE(stop_delay_us, 0) << "Looper did not stop in time.";
        EXPECT_LE(stop_delay_us, 10000) << "Looper did not stop in time.";
    }

    os_looper m_test_looper;

    thread m_looper_thread;

    steady_clock::time_point m_call_stop_time;
    steady_clock::time_point m_looper_stop_time;
};

TEST_F(basic, run_stop)
{
    run_looper_async();
    this_thread::sleep_for(seconds(1));
    stop_looper_and_check_delay();

    EXPECT_EQ(m_test_looper.m_test_update_event_count, 0);
}

TEST_F(basic, stop_run_stop)
{
    stop_looper();

    run_looper_async();
    this_thread::sleep_for(seconds(1));
    stop_looper_and_check_delay();

    EXPECT_EQ(m_test_looper.m_test_update_event_count, 0);
}

TEST_F(basic, multiple_run_stop)
{
    for (size_t i = 0; i < 10; ++i)
    {
        run_looper_async();
        this_thread::sleep_for(seconds(1));
        stop_looper_and_check_delay();
    }

    EXPECT_EQ(m_test_looper.m_test_update_event_count, 0);
}
