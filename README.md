# Eventually

[![PlatformIO CI](https://github.com/matthewturner/Eventually/actions/workflows/platformio.yml/badge.svg)](https://github.com/matthewturner/Eventually/actions/workflows/platformio.yml)

## An Arduino Event-based Programming Library

Based on the excellent [Eventually](https://github.com/johnnyb/Eventually) library, the goal is to make a more event-oriented environment for Arduino programming. To make it *actually* easy to use to build worthwhile projects.

See the extension libraries for more capabilities:

* [State machine](https://github.com/matthewturner/EventuallyStateMachine)
* [Command Processor](https://github.com/matthewturner/EventuallyCommand)

### Writing a Simple Eventually Program

To show the program in action, we will write a program that blinks a light, when a button is pushed.

To use Eventually, you need to download the library and then include it in your code (Sketch -> Include Library).  That should put the following line at the top of your program:

```c++
#include <Eventually.h>
```

Next, you need to include a global variable for the event manager. eg `mgr`:

```c++
EvtManager mgr;
```

Eventually works seamlessly with other code in your sketches. Call the `mgr.loopIteration();` on each loop:

```c++
void loop()
{
  // other code
  mgr.loopIteration();
}
```

Now, during our setup() function, instead of just doing pinModes, you also need to setup one or more listeners. The two primary types of listeners for Eventually are EvtPinListener and EvtTimeListener. We are going to use both. We will use the pin listener to tell us when the button is pushed and the time listener to blink the light. Therefore, our setup function will look like this:

```c++
#define LIGHT_PIN 5
#define BUTTON_PIN 3

void setup() {
  /* Set the pin modes */
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  /* Add a button listener */
  mgr.addListener(new EvtPinListener(BUTTON_PIN, (EvtAction)start_blinking));
}
```

Alternatively, if our BUTTON_PIN uses INPUT_PULLUP:

```c++
void setup() {
  // ...

  /* Button is LOW when pushed, so use INPUT_PULLUP */
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  /* Add a button listener, listening for LOW */
  /* (To use this constructor, we also have to specify the debounce delay) */
  mgr.addListener(new EvtPinListener(BUTTON_PIN, 40, LOW, (EvtAction)start_blinking));
}
```

This creates a listener for the given button pin, and will call start_blinking when the button is pushed. Note that by default, EvtPinListeners will automatically debounce the pin, and also make sure that it starts in the opposite state before beginning listening (though both of these are configurable).

Also note that we put (EvtAction) in front of our function name. This makes sure the compiler knows that this will be used as an event action. It may not compile without this marking.

Now, when the button is pushed, we need start_blinking to install a new time-based listener to blink the light, and another button listener to stop the blinking. So the code will look like this:

```c++
bool start_blinking()
{
  mgr.resetContext(); 
  mgr.addListener(new EvtTimeListener(500, true, (EvtAction)blink_pin));
  mgr.addListener(new EvtPinListener(BUTTON_PIN, (EvtAction)stop_blinking));
  return true;
}
```

This starts by calling resetContext(), which will uninstall all current listeners to prepare for a new set. Then, it adds a time listener. The first parameter to the EvtTimeListener constructor is the number of milliseconds to wait until firing. In this case, 500 (half a second). The second parameter is whether or not to continually fire.  If it is set to false, it will fire once and then be done. The last parameter is the function to call.

Then it adds a pin listener to call the stop_blinking function when pushed. All triggered actions need to return true or false. "true" stops the current action chain and is usually what you want.

Now, let's look at the blink_pin function:

```c++
bool blink_state = LOW;
bool blink_pin()
{
  blink_state = !blink_state;
  digitalWrite(LIGHT_PIN, blink_state);
  return false;
}
```

This creates a global variable that tells us the blink state, and whenever this is called, it alternates the blink state and writes that to the pin. This one returns false because, since the blinking doesn't affect the action of other pins, the event chain should continue.

Finally, we need a stop_blinking() function. All this will do is create a new listener to wait for it to start again:

```c++
bool stop_blinking()
{
  mgr.resetContext();
  mgr.addListener(new EvtPinListener(BUTTON_PIN, (EvtAction)start_blinking));
  return true;
}
```

Now you are ready to go!

### C++ Issues

One of the goals of this library was to make it use the flexibility of C++ without the user having to know a lot of C++. If you don't know C++, just use the listeners in the basic way mentioned. However, if you want to do more advanced things, this section covers the C++ issues.  

One main goal is to take advantage of the flexibility available with C++ pointers but without exposing the user to them. Therefore, listeners are always created with the "new" keyword, but they are immediately added to the manager (technically, the context) which then manages it. Once the listener is added to the manager/context, then the responsibility for its memory management goes to the manager/context. Note that at this time, there is no ability for user code to detect when a listener gets destroyed, so if you add data to a listener (see section below), then it should not rely on the listener to destroy the data at the right time.

### Writing Your Own Listeners

If you need a more advanced listener, you can write your own fairly easily:

* Implement the IEvtListener interface or create a subclass of EvtListener
* Add a constructor
* Add a `reset()` method
* Add an `isEventTriggered()` method

The constructor simply takes whatever arguments control the listener's behavior. The reset() method gets called when the listener is added to the chain. This should handle doing things such as sampling the current time or pin states that you will need to determine if the event is triggered.

The `isEventTriggered()` method returns true if the event is triggered.

Below is a simple class that simply always fires:

```c++
class EvtAlwaysFiresListener : public EvtListener
{
  public:
  EvtAlwaysFiresListener();
  void reset();
  bool isEventTriggered();
}

EvtAlwaysFiresListener::EvtAlwaysFiresListener()
{
  // Nothing to construct
}

void EvtAlwaysFiresListener::reset()
{
  // Nothing to setup
}

bool EvtAlwaysFiresListener::isEventTriggered()
{
  return true;
}
```

## Differences with the original

Some of the differences are down to personal preference and others were to help with memory management in the memory-constrained environment of the Arduino Nano.

* Favour explicitly calling the `mgr.loopIteration()`
* Reduce reliance on heap allocation
* Unit tests
* Extract interfaces
