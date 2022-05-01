#include "EvtPinListener.h"

EvtPinListener::EvtPinListener()
{
}

EvtPinListener::EvtPinListener(int pin, int debounce, bool targetValue, EvtAction action)
{
  this->pin = pin;
  this->debounce = debounce;
  this->targetValue = targetValue;
  this->triggerAction = action;
}

EvtPinListener::EvtPinListener(int pin, int debounce, EvtAction action)
{
  this->pin = pin;
  this->debounce = debounce;
  this->triggerAction = action;
}

EvtPinListener::EvtPinListener(int pin, EvtAction action)
{
  this->pin = pin;
  this->triggerAction = action;
}

void EvtPinListener::setupListener()
{
  startState = digitalRead(pin);
}

bool EvtPinListener::isEventTriggered()
{
  if (!EvtListener::isEventTriggered())
  {
    return false;
  }

  std::cout << "Target: " << targetValue << std::endl;
  std::cout << "Start State: " << startState << std::endl;

  bool val = digitalRead(pin);
  std::cout << "Value: " << val << std::endl;
  std::cout << "First noticed: " << firstNoticed << std::endl;

  // Debounce check if we were triggered earlier
  if (firstNoticed)
  {
    std::cout << "First noticed" << std::endl;
    unsigned long curMillis = millis();
    if (curMillis > firstNoticed + debounce)
    {
      // Debounce time expired, check again
      std::cout << "Debounce time expired" << std::endl;

      // Reset Watcher
      firstNoticed = 0;

      // Check
      if (val == targetValue)
      {
        std::cout << "Target == value" << std::endl;
        return true;
      }
    }

    // Waiting for debouncer to finish
    std::cout << "Waiting for debouncer to finish" << std::endl;
    return false;
  }

  if (mustStartOpposite && (startState == targetValue))
  {
    std::cout << "Must start opposite" << std::endl;
    /* This is a waiting loop to wait for the pin to change to the opposite state before sensing */
    /* Q - do I need to debounce mustStartOpposite? */
    if (val == startState)
    {
      // Do nothing
      std::cout << "Value == Start State" << std::endl;
    }
    else
    {
      std::cout << "Updating start state to: " << val << std::endl;
      startState = val;
    }

    return false;
  }

  /* This is the real deal */
  if (val == targetValue)
  {
    if (debounce == 0)
    {
      return true;
    }

    std::cout << "Updating first noticed" << std::endl;
    firstNoticed = millis();
  }

  std::cout << "Reached end" << std::endl;
  return false;
}