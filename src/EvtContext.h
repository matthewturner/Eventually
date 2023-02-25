/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).
 * Be sure to check out my books at www.bplearning.net!
 */

#ifndef EvtContext_h
#define EvtContext_h

#ifndef EVENTUALLY_MAX_CONTEXTS
#define EVENTUALLY_MAX_CONTEXTS 1
#endif
#ifndef EVENTUALLY_MAX_LISTENERS
#define EVENTUALLY_MAX_LISTENERS 5
#endif

#include "EvtListener.h"
#include <Arduino.h>

class EvtContext
{
public:
  EvtContext();
  void setupContext();
  void loopIteration();
  void addListener(EvtListener *lstn);
  void removeListener(EvtListener *lstn);

private:
  EvtListener* _listeners[EVENTUALLY_MAX_LISTENERS];
  byte _listenerCount;
};

#endif