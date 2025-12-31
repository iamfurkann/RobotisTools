/**
 * @file BatteryMonitor.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of BatteryMonitor class.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "BatteryMonitor.h"

/**
 * @brief Constructor. Allocates memory for the noise filter.
 */
BatteryMonitor::BatteryMonitor(int pin, float ratio, float refVoltage) {
  _pin = pin;
  _voltageDividerRatio = ratio;
  _refVoltage = refVoltage;
  
  // OpenCM9.04 (STM32) has 12-bit ADC (0-4095). 
  // Standard Arduino has 10-bit (0-1023).
  // Detecting architecture for resolution:
  #if defined(__STM32F1__) || defined(ARDUINO_ARCH_STM32)
    _adcResolution = 4095;
  #else
    _adcResolution = 1023;
  #endif

  // Create a filter with window size 20 (Smooth readings)
  _filter = new SignalFilter(20);
}

/**
 * @brief Destructor. Prevents memory leaks.
 */
BatteryMonitor::~BatteryMonitor() {
  if (_filter != NULL)
    delete _filter;
}

void BatteryMonitor::begin(float minV, float maxV) {
  pinMode(_pin, INPUT_ANALOG);
  _minVoltage = minV;
  _maxVoltage = maxV;
  
  if (_filter != NULL) 
    _filter->begin();
}

float BatteryMonitor::getVoltage() {
  int raw = analogRead(_pin);
  
  // Use SignalFilter to remove noise
  int smoothRaw = 0;
  if (_filter != NULL) 
    smoothRaw = _filter->filter(raw);
  else
    smoothRaw = raw; // Fallback if filter fails
  
  // Calculate Pin Voltage: (ADC / Resolution) * Vref
  float pinVoltage = ((float)smoothRaw / (float)_adcResolution) * _refVoltage;
  
  // Calculate Real Battery Voltage: PinVoltage * DividerRatio
  return pinVoltage * _voltageDividerRatio;
}

int BatteryMonitor::getPercentage() {
  float voltage = getVoltage();
  
  // Linear mapping calculation
  // (Current - Min) * 100 / (Max - Min)
  int pct = (int)((voltage - _minVoltage) * 100.0 / (_maxVoltage - _minVoltage));
  
  // Clamp results between 0 and 100
  if (pct > 100) 
    return 100;
  if (pct < 0) 
    return 0;
  
  return pct;
}

bool BatteryMonitor::isLow() {
  // Returns true if battery is below 10%
  return getPercentage() < 10;
}