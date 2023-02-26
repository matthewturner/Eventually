#include <ArduinoFake.h>
#include <unity.h>

#include "EvtManager.h"
#include "MockEvtListener.h"

using namespace fakeit;

EvtManager target;
Mock<IEvtListener> listenerMock;

void setUp(void)
{
    target.manageListeners(false);
    When(Method(listenerMock, setupListener)).AlwaysReturn();
    When(Method(listenerMock, isEventTriggered)).AlwaysReturn(true);
    When(Method(listenerMock, performTriggerAction)).AlwaysReturn(true);
    Fake(Dtor(listenerMock));
}

void tearDown(void)
{
    listenerMock.Reset();
    target.reset();
}

void test_default_to_one_context(void)
{
    IEvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    target.loopIteration();
    Verify(Method(listenerMock, performTriggerAction)).Once();
}

void test_push_sets_new_context(void)
{
    IEvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    EvtContext context;
    target.pushContext(&context);
    target.loopIteration();
    Verify(Method(listenerMock, performTriggerAction)).Never();
}

void test_reset_context_clears_listeners(void)
{
    target.manageListeners(true);
    IEvtListener *listener = new MockEvtListener();
    target.addListener(listener);
    target.resetContext();

    TEST_ASSERT_EQUAL(0, target.currentContext()->listenerCount());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_default_to_one_context);
    RUN_TEST(test_push_sets_new_context);
    RUN_TEST(test_reset_context_clears_listeners);
    UNITY_END();

    return 0;
}