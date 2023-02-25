#include "EvtManager.h"

EvtManager::EvtManager()
{
    _contextStack = new EvtContext[EVENTUALLY_MAX_CONTEXTS];
    _contextStack[_contextOffset].setupContext();
}

void EvtManager::addListener(EvtListener *lstn)
{
    _contextStack[_contextOffset].addListener(lstn);
}

void EvtManager::removeListener(EvtListener *lstn)
{
    _contextStack[_contextOffset].removeListener(lstn);
}

EvtContext *EvtManager::currentContext()
{
    return &_contextStack[_contextOffset];
}

EvtContext *EvtManager::pushContext()
{
    _contextOffset++;
    _contextStack[_contextOffset].setupContext();
    return &_contextStack[_contextOffset];
}

EvtContext *EvtManager::resetContext()
{
    _contextStack[_contextOffset].setupContext();
    return &_contextStack[_contextOffset];
}

EvtContext *EvtManager::popContext()
{
    _contextOffset--;
    return &_contextStack[_contextOffset];
}

void EvtManager::loopIteration()
{
    _contextStack[_contextOffset].loopIteration();
}