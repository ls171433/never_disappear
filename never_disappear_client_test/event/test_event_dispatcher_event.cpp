#include <gtest/gtest.h>

#include <thread>

#include "event/event.hpp"

using namespace never_disappear_client;
using namespace std;
using namespace std::chrono;

class event_dispatcher_event : public testing::Test
{
protected:
    event_dispatcher m_dispatcher;
    simple_event m_event;
};
