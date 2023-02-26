#include "EvtManager.h"

EvtManager::EvtManager()
{
    pushContext(&_defaultContext);
}

void EvtManager::addListener(IEvtListener *lstn)
{
    currentContext()->addListener(lstn);
}

void EvtManager::removeListener(IEvtListener *lstn)
{
    currentContext()->removeListener(lstn);
}

IEvtContext *EvtManager::currentContext()
{
    return _contextStack[_contextOffset - 1];
}

void EvtManager::pushContext(IEvtContext *context)
{
    context->reset();
    _contextStack[_contextOffset] = context;
    _contextOffset++;
}

void EvtManager::resetContext()
{
    IEvtContext *current = currentContext();
    current->reset();
}

IEvtContext *EvtManager::popContext()
{
    _contextOffset--;
    return currentContext();
}

void EvtManager::loopIteration()
{
    currentContext()->loopIteration();
}

void EvtManager::reset()
{
    _contextOffset = 1;
    currentContext()->reset();
}

void EvtManager::manageListeners(bool manage)
{
    currentContext()->manageListeners(manage);
}

byte EvtManager::listenerCount()
{
    return currentContext()->listenerCount();
}