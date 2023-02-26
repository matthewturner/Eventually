#include "MockEvtListener.h"

MockEvtListener::~MockEvtListener()
{
}

void MockEvtListener::reset()
{
}

bool MockEvtListener::isEventTriggered()
{
  return true;
}

bool MockEvtListener::performTriggerAction(EvtContext *ctx)
{
  _triggered = true;
  return true;
}

void MockEvtListener::disable()
{
}

void MockEvtListener::enable()
{
}

bool MockEvtListener::hasBeenTriggered()
{
    return _triggered;
}