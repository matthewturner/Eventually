#include "EvtListener.h"

EvtListener::~EvtListener()
{
}

void EvtListener::setupListener()
{
}

bool EvtListener::isEventTriggered()
{
  return _enabled;
}

bool EvtListener::performTriggerAction(EvtContext *ctx)
{
  return (*_triggerAction)(this, ctx);
}

void EvtListener::disable()
{
  this->_enabled = false;
}

void EvtListener::enable()
{
  this->_enabled = true;
  this->setupListener();
}