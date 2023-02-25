#include "EvtContext.h"

EvtContext::EvtContext()
{
}

void EvtContext::loopIteration()
{
    for (byte i = 0; i < _listenerCount; i++)
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

void EvtContext::setup()
{
    for (byte i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i])
        {
            delete _listeners[i];
            _listeners[i] = 0;
        }
    }
}

void EvtContext::addListener(EvtListener *lstn)
{
    for (byte i = 0; i < _listenerCount; i++)
    {
        if (_listeners[_listenerCount] == 0)
        {
            _listeners[_listenerCount] = lstn;
            return;
        }
    }

    _listeners[_listenerCount] = lstn;
    lstn->setupListener();
    _listenerCount++;
}

void EvtContext::removeListener(EvtListener *lstn)
{
    for (byte i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i] == lstn)
        {
            delete lstn;
            _listeners[i] = 0;
        }
    }
}