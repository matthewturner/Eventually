#include <ArduinoFake.h>
#include <unity.h>

#include "EvtManager.h"

using namespace fakeit;

EvtManager target;
Mock<EvtListener> listenerMock;

void setUp(void)
{
    When(Method(listenerMock, setupListener)).AlwaysReturn();
    When(Method(listenerMock, isEventTriggered)).AlwaysReturn(true);
    When(Method(listenerMock, performTriggerAction)).AlwaysReturn(true);
}

void tearDown(void)
{
    listenerMock.Reset();
}

void test_default_to_one_context(void)
{
    EvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    target.loopIteration();
    Verify(Method(listenerMock, performTriggerAction)).Once();
}

void test_push_sets_new_context(void)
{
    EvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    EvtContext context;
    target.pushContext(&context);
    target.loopIteration();
    Verify(Method(listenerMock, performTriggerAction)).Never();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_default_to_one_context);
    RUN_TEST(test_push_sets_new_context);
    UNITY_END();

    return 0;
}