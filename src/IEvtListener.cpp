#include "IEvtListener.h"

IEvtListener::IEvtListener()
{
}

IEvtListener::~IEvtListener()
{
    // this might be dangerous if extraData keeps a heap pointer ...
    extraData = 0;
}