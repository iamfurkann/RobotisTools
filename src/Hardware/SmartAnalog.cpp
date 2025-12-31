/**
 * @file SmartAnalog.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of SmartAnalog class.
 * @version 1.0.0
 * @date 2025-12-31
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "SmartAnalog.h"

SmartAnalog::SmartAnalog(int pin, int filterSize) {
  _pin = pin;
  _threshold = 512;   // Default mid-point
  _hysteresis = 20;   // Default buffer
  _invert = false;
  _state = false;
  
  // Create Filter Dynamically
  _filter = new SignalFilter(filterSize);

  // AUTO-DETECT ADC RESOLUTION
  // Robotis OpenCM / STM32 uses 12-bit (0-4095)
  // Standard Arduino uses 10-bit (0-1023)
  #if defined(__STM32F1__) || defined(ARDUINO_ARCH_STM32) || defined(OPENCM904)
    _adcResolution = 4095;
  #else
    _adcResolution = 1023;
  #endif
}

SmartAnalog::~SmartAnalog() {
  if (_filter != NULL)
    delete _filter;
}

void SmartAnalog::begin() {
  // DYNAMIC PIN MODE SELECTION
  // The compiler checks if "INPUT_ANALOG" is defined in the board package.
  // If yes (OpenCM/STM32), it uses it. If no (Arduino Uno), it uses INPUT.
  
  #ifdef INPUT_ANALOG
    pinMode(_pin, INPUT_ANALOG);
  #else
    pinMode(_pin, INPUT);
  #endif

  _filter->begin();
}

void SmartAnalog::setThreshold(int threshold, int hysteresis) {
  _threshold = threshold;
  _hysteresis = hysteresis;
}

void SmartAnalog::setInvert(bool invert) {
  _invert = invert;
}

int SmartAnalog::readRaw() {
  return analogRead(_pin);
}

int SmartAnalog::readSmooth() {
  int raw = analogRead(_pin);
  if (_filter != NULL)
    return _filter->filter(raw);
  return raw;
}

int SmartAnalog::readPercentage() {
  int val = readSmooth();
  // Map 0..MaxADC to 0..100
  long pct = map(val, 0, _adcResolution, 0, 100);
  
  if (pct > 100)
    return 100;
  if (pct < 0)
    return 0;
  return (int)pct;
}

// Schmitt Trigger Logic implementation
bool SmartAnalog::isActive() {
  int val = readSmooth();
  
  if (!_invert) {
    // Normal Mode: Active if value goes UP
    // Turn ON if value > (Threshold + Hysteresis)
    if (val > (_threshold + _hysteresis))
      _state = true;
    // Turn OFF only if value drops below (Threshold - Hysteresis)
    else if (val < (_threshold - _hysteresis))
      _state = false;
    // If in between, keep previous state (No flickering!)
  } 
  else {
    // Inverted Mode: Active if value goes DOWN (e.g. LDR getting dark)
    if (val < (_threshold - _hysteresis))
      _state = true;
    else if (val > (_threshold + _hysteresis))
      _state = false;
  }
  
  return _state;
}