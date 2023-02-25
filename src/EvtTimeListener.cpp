#include "EvtTimeListener.h"

EvtTimeListener::EvtTimeListener()
{
}

EvtTimeListener::EvtTimeListener(unsigned long time, bool multiFire, EvtAction t)
{
    this->_millis = time;
    this->_triggerAction = t;
    this->_multiFire = multiFire;
}

void EvtTimeListener::setupListener()
{
    _startMillis = ::millis();
    _hasExecuted = false;
}

bool EvtTimeListener::isEventTriggered()
{
    if (!EvtListener::isEventTriggered())
    {
        return false;
    }

    if (!_multiFire && _hasExecuted)
    {
        return false;
    }

    unsigned long curTime = ::millis();
    bool shouldFire = false;
    if (curTime >= _startMillis)
    {
        /* Normal */
        if (curTime - _startMillis > _millis)
        {
            shouldFire = true;
        }
    }
    else
    {
        /* Wrap-Around! */
        if (((ULONG_MAX - _startMillis) + curTime) > _millis)
        {
            shouldFire = true;
        }
    }

    return shouldFire;
}

bool EvtTimeListener::performTriggerAction(EvtContext *c)
{
    bool returnval = (*_triggerAction)(this, c);
    if (_multiFire)
    {
        // On multifire, setup to receive the event again
        setupListener();
        // On multifire, we shouldn't stop the event chain no matter what, since we are just restarting in this context
        return false;
    }
    else
    {
        _hasExecuted = true;
        return returnval;
    }
}
