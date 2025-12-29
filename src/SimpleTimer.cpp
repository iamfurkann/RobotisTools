#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(unsigned long interval) {
  _interval = interval;
  _previousMillis = 0;
}

void SimpleTimer::setInterval(unsigned long interval) {
  _interval = interval;
}

/**
 * @brief Checks if the time interval has elapsed. Automatically resets.
 */
bool SimpleTimer::isReady() {
  if (millis() - _previousMillis >= _interval) {
    _previousMillis = millis();
    return true;
  }
  return false;
}

void SimpleTimer::reset() {
  _previousMillis = millis();
}