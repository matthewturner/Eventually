#include "EvtContext.h"

EvtContext::EvtContext()
{
}

void EvtContext::loopIteration()
{
    for (int i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i])
        {
            if (_listeners[i]->isEventTriggered())
            {
                if (_listeners[i]->performTriggerAction(this))
                {
                    return;
                }
            }
        }
    }
}

void EvtContext::setupContext()
{
    if (data)
    {
        delete data;
    }
    if (_listeners)
    {
        for (int i = 0; i < _listenerCount; i++)
        {
            if (_listeners[i])
            {
                delete _listeners[i];
            }
        }
        delete _listeners;
    }

    _listeners = new EvtListener *[EVENTUALLY_MAX_LISTENERS];
    _listenerCount = 0;
}

void EvtContext::addListener(EvtListener *lstn)
{
    for (int i = 0; i < _listenerCount; i++)
    { // Try to add in empty slot
        if (_listeners[_listenerCount] == 0)
        {
            _listeners[_listenerCount] = lstn;
            return;
        }
    }

    // No empty slot, just add it
    _listeners[_listenerCount] = lstn;
    lstn->setupListener();
    listenerCount++;
}

void EvtContext::removeListener(EvtListener *lstn)
{
    for (int i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i] == lstn)
        {
            delete lstn;
            _listeners[i] = 0;
        }
    }
}