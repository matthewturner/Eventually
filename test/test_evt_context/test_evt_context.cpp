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

void test_add_listener_resets_listener(void)
{
    IEvtListener &listener = listenerMock.get();
    target.addListener(&listener);
    Verify(Method(listenerMock, reset)).Once();
}

void test_add_listener_in_middle_slot_resets_listener(void)
{
    MockEvtListener *listenerToRemove = new MockEvtListener();
    target.addListener(listenerToRemove);
    target.addListener(new MockEvtListener());
    target.removeListener(listenerToRemove);

    IEvtListener &listener = listenerMock.get();
    // add in the newly vacated slot
    target.addListener(&listener);

    Verify(Method(listenerMock, reset)).Once();
}

void test_listener_count_does_not_include_empty_slots(void)
{
    MockEvtListener *listenerToRemove = new MockEvtListener();
    target.addListener(listenerToRemove);
    target.addListener(new MockEvtListener());
    target.removeListener(listenerToRemove);

    TEST_ASSERT_EQUAL(1, target.listenerCount());
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
    RUN_TEST(test_add_listener_resets_listener);
    RUN_TEST(test_add_listener_in_middle_slot_resets_listener);
    RUN_TEST(test_listener_count_does_not_include_empty_slots);
    RUN_TEST(test_loop_iteration_calls_listener);
    RUN_TEST(test_reset_clears_listeners);
    UNITY_END();

    return 0;
}