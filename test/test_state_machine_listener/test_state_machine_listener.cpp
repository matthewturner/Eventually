#include <unity.h>
#include <ArduinoFake.h>

#include "EvtContext.h"
#include "StateMachineListener.h"

using namespace fakeit;

bool triggered = false;
byte triggerCount = 0;

bool trigger()
{
    triggered = true;
    triggerCount++;
    return true;
}

bool failedTrigger()
{
    return false;
}

StateMachineListener target;
EvtContext ctx;

void setUp(void)
{
    triggered = false;
    triggerCount = 0;
    target.enable();
    target.transition(3);
    target.setTransitionTime(0);
    // target.setSystemTime(10);
    target.when(3, (EvtAction)trigger, 4, 9, 5);
    target.when(4, (EvtAction)trigger, 5, 9, 5);
    target.when(5, (EvtAction)trigger, 6, 9, 5);
    When(Method(ArduinoFake(), millis)).Return(10);
}

void test_does_not_trigger_when_disabled(void)
{
    target.disable();
    TEST_ASSERT_FALSE(target.isEventTriggered());
}

void test_triggers_when_enabled(void)
{
    TEST_ASSERT_TRUE(target.isEventTriggered());
}

void test_does_not_trigger_when_failed(void)
{
    target.transition(STATE_FAILED);
    TEST_ASSERT_FALSE(target.isEventTriggered());
}

void test_does_not_transition(void)
{
    target.when(3, (EvtAction)trigger);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(3, target.currentState());
}

void test_triggers_when_state(void)
{
    target.when(3, (EvtAction)trigger, 4);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_TRUE(triggered);
}

void test_sets_next_state(void)
{
    target.when(3, (EvtAction)trigger, 4);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(4, target.currentState());
}

void test_sets_default_failed_state(void)
{
    target.when(3, (EvtAction)failedTrigger, 4);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(STATE_FAILED, target.currentState());
}

void test_sets_next_failed_state(void)
{
    target.when(3, (EvtAction)failedTrigger, 4, 5);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(5, target.currentState());
}

void test_interrupt_does_not_transition_when_not_guard_state(void)
{
    target.whenInterrupted(5, 6);
    target.onInterrupt();
    TEST_ASSERT_EQUAL(3, target.currentState());
}

void test_interrupt_transitions_when_guard_state(void)
{
    target.whenInterrupted(3, 6);
    target.onInterrupt();
    TEST_ASSERT_EQUAL(6, target.currentState());
}

void test_does_not_transition_before_timeout(void)
{
    target.when(3, (EvtAction)trigger, 4, 5, 10);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(3, target.currentState());
}

void test_transitions_after_timeout(void)
{
    target.setTransitionTime(5);
    target.when(3, (EvtAction)trigger, 4, 5, 3);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(4, target.currentState());
}

void test_state_transition_updates_time(void)
{
    target.transition(4);
    TEST_ASSERT_EQUAL(10, target.transitionTime());
}

void test_state_transition_does_not_update_time_if_same_state(void)
{
    target.setTransitionTime(2);
    target.transition(4);
    target.setTransitionTime(5);
    target.transition(4);
    TEST_ASSERT_EQUAL(5, target.transitionTime());
}

void test_executes_only_once_within_state(void)
{
    target.transition(2);
    target.when(3, (EvtAction)trigger, 4, 9, 5);
    // target.setSystemTime(1);
    When(Method(ArduinoFake(), millis)).Return(1);
    target.transition(3);

    // target.setSystemTime(5);
    When(Method(ArduinoFake(), millis)).Return(5);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(3, target.currentState());
    TEST_ASSERT_EQUAL(1, triggerCount);

    // not reached delay
    // target.setSystemTime(6);
    When(Method(ArduinoFake(), millis)).Return(6);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(3, target.currentState());
    TEST_ASSERT_EQUAL(1, triggerCount);

    // passed transition delay
    // target.setSystemTime(7);
    When(Method(ArduinoFake(), millis)).Return(7);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(4, target.currentState());
    TEST_ASSERT_EQUAL(1, triggerCount);

    // invoke in next state
    // target.setSystemTime(8);
    When(Method(ArduinoFake(), millis)).Return(8);
    target.performTriggerAction(&ctx);
    TEST_ASSERT_EQUAL(4, target.currentState());
    TEST_ASSERT_EQUAL(2, triggerCount);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_does_not_trigger_when_disabled);
    RUN_TEST(test_triggers_when_enabled);
    RUN_TEST(test_does_not_trigger_when_failed);
    RUN_TEST(test_does_not_transition);
    RUN_TEST(test_triggers_when_state);
    RUN_TEST(test_sets_next_state);
    RUN_TEST(test_sets_default_failed_state);
    RUN_TEST(test_sets_next_failed_state);
    RUN_TEST(test_interrupt_does_not_transition_when_not_guard_state);
    RUN_TEST(test_interrupt_transitions_when_guard_state);
    RUN_TEST(test_does_not_transition_before_timeout);
    RUN_TEST(test_transitions_after_timeout);
    RUN_TEST(test_state_transition_updates_time);
    RUN_TEST(test_state_transition_does_not_update_time_if_same_state);
    RUN_TEST(test_executes_only_once_within_state);
    UNITY_END();

    return 0;
}