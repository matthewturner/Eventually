#include <ArduinoFake.h>
#include <unity.h>

#include "EvtContext.h"
#include "MockEvtListener.h"

using namespace fakeit;

EvtContext target;
Mock<IEvtListener> listenerMock;

void setUp(void)
{
    target.manageListeners(false);
    When(Method(listenerMock, reset)).AlwaysReturn();
    When(Method(listenerMock, isEventTriggered)).AlwaysReturn(true);
    When(Method(listenerMock, performTriggerAction)).AlwaysReturn(true);
    Fake(Dtor(listenerMock));
}

void tearDown(void)
{
    listenerMock.Reset();
    target.reset();
}

void test_loop_iteration_calls_listener(void)
{
    IEvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    target.loopIteration();
    Verify(Method(listenerMock, performTriggerAction)).Once();
}

void test_reset_clears_listeners(void)
{
    target.manageListeners(true);
    IEvtListener *listener = new MockEvtListener();
    target.addListener(listener);
    target.reset();

    TEST_ASSERT_EQUAL(0, target.listenerCount());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_loop_iteration_calls_listener);
    RUN_TEST(test_reset_clears_listeners);
    UNITY_END();

    return 0;
}