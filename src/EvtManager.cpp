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

EvtContext *EvtManager::currentContext()
{
    return _contextStack[_contextOffset - 1];
}

void EvtManager::pushContext(EvtContext *context)
{
    context->setup();
    _contextStack[_contextOffset] = context;
    _contextOffset++;
}

void EvtManager::resetContext()
{
    EvtContext *current = currentContext();
    current->setup();
}

EvtContext *EvtManager::popContext()
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
    currentContext()->setup();
}

void EvtManager::manageListeners(bool manage)
{
    currentContext()->manageListeners(manage);
}