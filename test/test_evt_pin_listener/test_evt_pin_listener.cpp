#include <ArduinoFake.h>
#include <unity.h>

#include "EvtPinListener.h"

using namespace fakeit;

bool triggered = false;
bool trigger()
{
    triggered = true;
    return true;
}

EvtPinListener target(2, 200, (EvtAction)trigger);

void setUp(void)
{
    triggered = false;
    ArduinoFakeReset();
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10);
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(HIGH);
    target.enable();
}

void test_does_not_trigger_when_disabled(void)
{
    target.disable();
    TEST_ASSERT_FALSE(target.isEventTriggered());
}

void test_triggers_when_enabled(void)
{
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(LOW);
    TEST_ASSERT_TRUE(target.isEventTriggered());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_does_not_trigger_when_disabled);
    RUN_TEST(test_triggers_when_enabled);
    UNITY_END();

    return 0;
}