#include "ThreeWireStripHalf.h"

ThreeWireStripHalf::ThreeWireStripHalf(pin left, pin center, pin right, bool reversed)
{
  _reversed = reversed;

  _left_pin = left;
  _center_pin = center;
  _right_pin = right;

  _brightness = 255;  

  // set all to white
  _color = White;
  _red = 255;
  _green = 255;
  _blue = 255;
}

// overrides
void ThreeWireStripHalf::setBlack()
{
  _red = 0;
  _green = 0;
  _blue = 0;
}

void ThreeWireStripHalf::nextColor()
{
  fl_color color = (fl_color)((_color+1) % fl_color::ColorCount);
  if (color == Black) color = Red;
  setColor(color);
}

void ThreeWireStripHalf::setColor(fl_color value)
{
  if (value != ColorCount) {
    _color = value;
  }
  switch (value) {
    case Black:   setRGB(  0,   0,   0); break;
    case Red:     setRGB(255,   0,   0); break;
    case Green:   setRGB(  0, 255,   0); break;
    case Yellow:  setRGB(255, 255,   0); break;
    case Blue:    setRGB(  0,   0, 255); break;
    case Magenta: setRGB(255,   0, 255); break;
    case Cyan:    setRGB(  0, 255, 255); break;
    case White:   setRGB(255, 255, 255); break;
  }
}

void ThreeWireStripHalf::setRGB(byte red, byte green, byte blue)
{
  _red = red; _green = green; _blue = blue;
}

void ThreeWireStripHalf::setBrightness(byte value)
{
  _brightness = value;
}

void ThreeWireStripHalf::display()
{
  if (_red>0) {
    displayRed();
    delayMicroseconds(pwm_value(_red));
  }
  if (_green>0) {
    displayGreen();
    delayMicroseconds(pwm_value(_green));
  }
  if (_blue>0) {
    displayBlue();
    delayMicroseconds(pwm_value(_blue));
  }
}

void ThreeWireStripHalf::display(int approxMs)
{
  unsigned long time = millis();

  while (millis()-time < approxMs) {
    display();
  }
}

void ThreeWireStripHalf::displayBlack()
{
  _reversed ? pinLow(_left_pin) : pinHigh(_left_pin);
  _reversed ? pinHigh(_center_pin) : pinLow(_center_pin);
  pinOff(_right_pin);
}

void ThreeWireStripHalf::displayRed()
{
  _reversed ? pinHigh(_left_pin, _red*_brightness/255) : pinLow(_left_pin);
  _reversed ? pinLow(_center_pin) : pinHigh(_center_pin, _red*_brightness/255);
  pinOff(_right_pin);
}

void ThreeWireStripHalf::displayGreen()
{
  _reversed ? pinHigh(_left_pin, _green*_brightness/255) : pinLow(_left_pin);
  pinOff(_center_pin);
  _reversed ? pinLow(_right_pin) : pinHigh(_right_pin, _green*_brightness/255);
}

void ThreeWireStripHalf::displayBlue()
{
  pinOff(_left_pin);
  _reversed ? pinHigh(_center_pin, _blue*_brightness/255) : pinLow(_center_pin);
  _reversed ? pinLow(_right_pin) : pinHigh(_right_pin, _blue*_brightness/255);
}

void ThreeWireStripHalf::fade(fl_color fromColor, fl_color toColor) {

}