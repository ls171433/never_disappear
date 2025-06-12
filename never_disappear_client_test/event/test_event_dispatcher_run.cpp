#include <gtest/gtest.h>

#include <thread>

#include "event/event.hpp"

using namespace never_disappear_client;
using namespace std;
using namespace std::chrono;

class event_dispatcher_run : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        EXPECT_FALSE(m_dispatcher.running());
    }

    virtual void test_run_stop()
    {
        thread run_thread{[this]
        {
            EXPECT_TRUE(m_dispatcher.run());
        }};

        this_thread::sleep_for(1s);
        EXPECT_TRUE(m_dispatcher.running());

        test_stop();

        EXPECT_TRUE(run_thread.joinable());
        run_thread.join();
    }

    virtual void test_stop()
    {
        m_dispatcher.stop();

        std::this_thread::sleep_for(1s);
        EXPECT_FALSE(m_dispatcher.running());
    }

    event_dispatcher m_dispatcher;
};

TEST_F(event_dispatcher_run, empty)
{
}

TEST_F(event_dispatcher_run, stop)
{
    test_stop();
}

TEST_F(event_dispatcher_run, run_stop)
{
    test_run_stop();
}

TEST_F(event_dispatcher_run, multiple_run_stop)
{
    for (size_t i = 0; i < 10; ++i)
    {
        test_run_stop();
    }
}

TEST_F(event_dispatcher_run, stop_run_stop)
{
    test_stop();
    test_run_stop();
}

TEST_F(event_dispatcher_run, stop_multiple_run_stop)
{
    test_stop();
    for (size_t i = 0; i < 10; ++i)
    {
        test_run_stop();
    }
}
