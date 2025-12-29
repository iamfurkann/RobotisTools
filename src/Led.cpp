#include "Led.h"

Led::Led(int pin) {
  _pin = pin;
  _state = 1; // Default state (Assuming Active Low for OpenCM)
  _previousMillis = 0;
  digitalWrite(_pin, _state);
}

void Led::begin() {
    pinMode(_pin, OUTPUT);
}

void Led::turnOn() {
  _state = 0; // Active Low
  digitalWrite(_pin, _state);
}

void Led::turnOff() {
  _state = 1;
  digitalWrite(_pin, _state);
}

void Led::toggle() {
  _state = !_state;
  digitalWrite(_pin, _state);
}

/**
 * @brief Non-blocking blink function based on millis().
 */
void Led::blink(int interval) {
  if (millis() - _previousMillis >= interval)
  {
    _previousMillis = millis();
    toggle();
  }
}