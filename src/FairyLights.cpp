
#include "FairyLights.h"
#include "TwoWireStrip.h"
#include "ThreeWireStrip.h"

// warning: we don't currently do any validation that you're
// passing in sane inputs for the type specified... it'll
// just do weird - probably broken - stuff
FairyLights* FairyLightsFactory(fl_type lightType, pin pins[]) {
  switch(lightType) {
    case M1359L:
    case TwoWire:
      return new TwoWireStrip( pins[0] );
    case ThreeWire:
      return new ThreeWireStrip( pins[0], pins[1], pins[2] );
  }

  //cheating for now...
  return new TwoWireStrip( pins[0] );
}

void pinOff(pin p)
{
  digitalWrite(p, LOW);
  pinMode(p, INPUT);
}

void pinLow(pin p)
{
  pinMode(p, OUTPUT);
  digitalWrite(p, LOW);
}

void pinHigh(pin p)
{
  pinMode(p, OUTPUT);
  digitalWrite(p, HIGH);
}

void pinHigh(pin p, byte val)
{
  pinMode(p, OUTPUT);
  analogWrite(p, val);
}
  
  
