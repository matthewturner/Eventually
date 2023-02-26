/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).
 * Be sure to check out my books at www.bplearning.net!
 */

#ifndef IEvtListener_h
#define IEvtListener_h

#include "EvtAction.h"

class EvtContext;

class IEvtListener
{
public:
    IEvtListener();
    virtual void reset() = 0;
    virtual bool isEventTriggered() = 0;
    virtual bool performTriggerAction(EvtContext *) = 0; // return false to stop the current chain

    virtual void disable() = 0;
    virtual void enable() = 0;
    virtual ~IEvtListener() = 0;
};

#endif