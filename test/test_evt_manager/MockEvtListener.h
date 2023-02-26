#ifndef MockEvtListener_h
#define MockEvtListener_h

#include "EvtAction.h"
#include "IEvtListener.h"

class EvtContext;

class MockEvtListener : public IEvtListener
{
public:
    virtual void setupListener() override;
    virtual bool isEventTriggered() override;
    virtual bool performTriggerAction(EvtContext *) override; // return false to stop the current chain
    bool hasBeenTriggered();

    virtual void disable() override;
    virtual void enable() override;
    virtual ~MockEvtListener() override;

protected:
    bool _triggered = false;
};

#endif