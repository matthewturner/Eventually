#include "EvtContext.h"

EvtContext::EvtContext()
{
}

void EvtContext::manageListeners(bool manage)
{
    _managesListeners = manage;
}

byte EvtContext::listenerCount()
{
    return _listenerCount;
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
            if (_managesListeners)
            {
                delete _listeners[i];
            }
            _listeners[i] = 0;
        }
    }

    _listenerCount = 0;
}

void EvtContext::addListener(IEvtListener *lstn)
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

void EvtContext::removeListener(IEvtListener *lstn)
{
    for (byte i = 0; i < _listenerCount; i++)
    {
        if (_listeners[i] == lstn)
        {
            if (_managesListeners)
            {
                delete lstn;
            }
            _listeners[i] = 0;

            if (i == _listenerCount - 1)
            {
                _listenerCount--;
            }
        }
    }
}