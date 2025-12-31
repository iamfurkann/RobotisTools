/**
 * @file DiffDrive.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of DiffDrive kinematics.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "DiffDrive.h"

/**
 * @brief Constructor.
 */
DiffDrive::DiffDrive(int maxPWM) {
  _maxPWM = maxPWM;
  _deadband = 0; // Default: No deadband
  _leftSpeed = 0;
  _rightSpeed = 0;
}

void DiffDrive::setDeadband(int limit) {
  _deadband = limit;
}

/**
 * @brief Main mixing logic (Arcade Drive).
 * Formula: 
 * Left  = Y + X
 * Right = Y - X
 * Then scaled to MaxPWM.
 */
void DiffDrive::compute(int x, int y) {
  // 1. Apply Deadband (Ignore small joystick drift)
  if (abs(x) < _deadband) 
    x = 0;
  if (abs(y) < _deadband) 
    y = 0;

  // 2. Raw Mixing
  // X and Y are expected to be roughly in percentage range (-100 to 100)
  int rawLeft = y + x;
  int rawRight = y - x;

  // 3. Scale and Clip to Max PWM
  // Input range is roughly -200 to 200 (100+100)
  // Output range is -_maxPWM to _maxPWM
  
  _leftSpeed = map(rawLeft, -200, 200, -_maxPWM, _maxPWM);
  _rightSpeed = map(rawRight, -200, 200, -_maxPWM, _maxPWM);

  // 4. Hard Limit Safeguard (Constrain)
  // map() does not constrain values out of range by default
  if (_leftSpeed > _maxPWM) 
    _leftSpeed = _maxPWM;
  if (_leftSpeed < -_maxPWM) 
    _leftSpeed = -_maxPWM;
  
  if (_rightSpeed > _maxPWM) 
    _rightSpeed = _maxPWM;
  if (_rightSpeed < -_maxPWM)
    _rightSpeed = -_maxPWM;
}

int DiffDrive::getLeft() {
  return _leftSpeed;
}

int DiffDrive::getRight() {
  return _rightSpeed;
}