/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).
 * Be sure to check out my books at www.bplearning.net!
 */

#ifndef EvtPinListener_h
#define EvtPinListener_h

#include <Arduino.h>
#include "EvtListener.h"

class EvtPinListener : public EvtListener
{
public:
  EvtPinListener();
  EvtPinListener(int pin, EvtAction trigger);
  EvtPinListener(int pin, int debounce, EvtAction action);
  EvtPinListener(int pin, int debounce, bool targetValue, EvtAction action);
  void setupListener();
  bool isEventTriggered();

private:
  int _pin = 0;
  int _debounce = 40;
  bool _targetValue = HIGH;
  bool _mustStartOpposite = true;
  bool _startState;
  unsigned long _firstNoticed = 0;
};

#endif