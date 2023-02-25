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
     When(Method(listenerMock, performTriggerAction)).AlwaysReturn();
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
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_default_to_one_context);
    UNITY_END();

    return 0;
}