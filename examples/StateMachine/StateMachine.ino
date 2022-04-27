#include "Eventually.h"

#include <Arduino.h>

const byte IDLE = 0;
const byte PENDING = 1;
const byte IN_PROGRESS = 2;

void wakeUp()
{
    stateMachine.onInterrupt();
}

bool idle()
{
    Serial.println("Idling...");
    digitalWrite(13, LOW);
    delay(500);
    return true;
}

bool pending()
{
    Serial.println("Pending...");
    return true;
}

bool inProgress()
{
    Serial.println("In progress...");
    digitalWrite(13, HIGH);
    delay(500);
    return true;
}

EvtManager mgr;
StateMachineListener stateMachine;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    pinMode(13, OUTPUT);

    stateMachine.transition(IDLE);

    stateMachine.when(IDLE, (EvtAction)idle), PENDING);
    stateMachine.when(PENDING, (EvtAction)pending), IN_PROGRESS);
    stateMachine.when(IN_PROGRESS, (EvtAction)inProgress), IDLE);
    stateMachine.whenInterrupted(IDLE, PENDING);

    mgr.addListener(&stateMachine);

    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, LOW);

    Serial.println("Setup complete, continuing...");
}

USE_EVENTUALLY_LOOP(mgr)