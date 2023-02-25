/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).
 * Be sure to check out my books at www.bplearning.net!
 */

#ifndef EvtManager_h
#define EvtManager_h

#include "EvtContext.h"
#include "EvtListener.h"
#include <Arduino.h>

class EvtManager
{
public:
  EvtManager();
  void loopIteration();
  EvtContext *pushContext();
  EvtContext *resetContext();
  EvtContext *popContext();
  EvtContext *currentContext();
  void addListener(EvtListener *lstn);
  void removeListener(EvtListener *lstn);

private:
  EvtContext *_contextStack = 0;
  byte _contextOffset = 0;
  byte _contextDepth = 0;
};

#endif