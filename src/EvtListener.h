/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).
 * Be sure to check out my books at www.bplearning.net!
 */

#ifndef EvtListener_h
#define EvtListener_h

#include "EvtAction.h"

class EvtContext;

class EvtListener
{
public:
    void *_extraData = 0;
    EvtAction _triggerAction;
    bool _enabled = true;

    virtual void setupListener();
    virtual bool isEventTriggered();
    virtual bool performTriggerAction(EvtContext *); // return false to stop the current chain

    virtual void disable();
    virtual void enable();

protected:
};

#endif