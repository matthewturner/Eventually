#include "EvtContext.h"

EvtContext::EvtContext()
{
}

void EvtContext::loopIteration()
{
    printf("111111111\n");
    for (byte i = 0; i < _listenerCount; i++)
    {
        printf("111111111\n");
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
    if (_listeners)
    {
        for (byte i = 0; i < _listenerCount; i++)
        {
            if (_listeners[i])
            {
                delete _listeners[i];
            }
        }
    }
}

void EvtContext::addListener(EvtListener *lstn)
{
    for (int i = 0; i < _listenerCount; i++)
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
    for (int i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i] == lstn)
        {
            delete lstn;
            _listeners[i] = 0;
        }
    }
}