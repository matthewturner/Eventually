#ifndef IEvtContext_h
#define IEvtContext_h

#include "IEvtListener.h"
#include <Arduino.h>

class IEvtContext
{
public:
  IEvtContext();
  virtual void reset() = 0;
  virtual void loopIteration() = 0;
  virtual void addListener(IEvtListener *lstn) = 0;
  virtual void removeListener(IEvtListener *lstn) = 0;
  virtual void manageListeners(bool manage) = 0;
  virtual byte listenerCount() = 0;
};

#endif