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

#include "Common.h"
#include "IEvtListener.h"
#include "IEvtContext.h"

class EvtContext : public IEvtContext
{
public:
  EvtContext();
  virtual void reset() override;
  virtual void loopIteration() override;
  virtual void addListener(IEvtListener *lstn) override;
  virtual void removeListener(IEvtListener *lstn) override;

  /// @brief Determines whether to free memory allocated
  /// to listener or leave to consumer
  /// @param manage
  virtual void manageListeners(bool manage) override;
  virtual byte listenerCount() override;

private:
  IEvtListener *_listeners[EVENTUALLY_MAX_LISTENERS];
  byte _listenerCount = 0;
  bool _managesListeners = true;
};

#endif