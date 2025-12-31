/**
 * @file FastPID.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of FastPID Controller.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "FastPID.h"

/**
 * @brief Constructor. Initializes parameters and resets history.
 */
FastPID::FastPID(float kp, float ki, float kd, int sampleTime) {
  _kp = kp;
  _ki = ki;
  _kd = kd;
  _sampleTime = sampleTime;
  
  // Default PWM limits for Arduino/OpenCM
  _outputMin = -255.0;
  _outputMax = 255.0;
  
  _lastTime = millis() - _sampleTime; // Force immediate first calculation
  _lastOutput = 0.0;
  reset();
}

void FastPID::reset() {
  _integral = 0.0;
  _lastInput = 0.0;
  _lastOutput = 0.0;
}

void FastPID::setOutputLimits(float min, float max) {
  if (min >= max) return; // Error check
  _outputMin = min;
  _outputMax = max;

  // Clamp existing integral to new limits
  if (_integral > _outputMax) 
    _integral = _outputMax;
  else if (_integral < _outputMin) 
    _integral = _outputMin;
}

void FastPID::setTunings(float kp, float ki, float kd) {
  if (kp < 0 || ki < 0 || kd < 0) 
    return;
  _kp = kp;
  _ki = ki;
  _kd = kd;
}

float FastPID::compute(float setpoint, float input) {
  unsigned long now = millis();
  unsigned long timeChange = (now - _lastTime);

  // Only calculate if sample time has passed
  if (timeChange >= _sampleTime) {
    // 1. Calculate Error
    float error = setpoint - input;

    // 2. Calculate Integral (Accumulated Error)
    // Integral = Integral + (Ki * Error)
    _integral += (_ki * error);

    // [Integral Windup Guard]
    // Prevent integral from growing infinitely if actuator is saturated
    if (_integral > _outputMax) 
      _integral = _outputMax;
    else if (_integral < _outputMin)
      _integral = _outputMin;

    // 3. Calculate Derivative (Rate of Change)
    // Technique: "Derivative on Measurement" (dInput instead of dError)
    // This prevents "Derivative Kick" when setpoint changes abruptly.
    float dInput = (input - _lastInput);

    // 4. Compute Final Output
    // Output = P + I - D
    float output = (_kp * error) + _integral - (_kd * dInput);

    // 5. Limit Output
    if (output > _outputMax) 
      output = _outputMax;
    else if (output < _outputMin)
      output = _outputMin;

    // 6. Save State variables for next loop
    _lastInput = input;
    _lastTime = now;
    _lastOutput = output;
  }

  return _lastOutput;
}