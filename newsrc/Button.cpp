#include "Button.h"

Button::Button(int pin) {
  _pin = pin;
  _lastState = 0;
  _lastDebounceTime = 0;
  _debounceDelay = 50;
}

void Button::begin() {
  pinMode(_pin, INPUT_PULLDOWN);
}

/**
 * @brief Checks for a valid button press (Rising Edge) with debounce.
 */
bool Button::isPressed() {
  int currentState = digitalRead(_pin);
  bool result = false;

  // Logic: Check for rising edge (0 -> 1) and debounce delay
  if (currentState == 1 && _lastState == 0 && (millis() - _lastDebounceTime > _debounceDelay))
  {
    _lastDebounceTime = millis();
    result = true;
  }
  _lastState = currentState;
  return result;
}

/**
 * @brief Checks if the button is held down for a specific duration.
 */
bool Button::isHeld(int duration) {
  if (digitalRead(_pin) == 1 && (millis() - _lastDebounceTime > duration))
    return true;
  return false;
}