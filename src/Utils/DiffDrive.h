/**
 * @file DiffDrive.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Differential Drive Kinematics Solver (Arcade Drive).
 * Converts Joystick (X, Y) inputs into Left/Right Motor speeds.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

#include <Arduino.h>

/**
 * @brief Handles mixing logic for tank-style or 2WD robots.
 * Implements "Arcade Drive" mixing algorithm.
 */
class DiffDrive {
  private:
    int _maxPWM;      // Maximum motor speed limit (e.g., 255 or 1023)
    int _deadband;    // Joystick center tolerance to ignore noise
    int _leftSpeed;   // Calculated Result for Left Motor
    int _rightSpeed;  // Calculated Result for Right Motor

  public:
    /**
     * @brief Construct a new Diff Drive object.
     * @param maxPWM Maximum PWM value your motor driver accepts (Default: 255).
     * For Robotis OpenCM, this is usually 1023. For Arduino PWM, 255.
     */
    DiffDrive(int maxPWM = 255);
    
    /**
     * @brief Sets the deadband threshold.
     * Inputs smaller than this value will be treated as 0.
     * @param limit Deadband value (e.g., 5 or 10).
     */
    void setDeadband(int limit);

    /**
     * @brief Performs the mixing calculation.
     * @param x Turn Input (-100 to 100). Positive = Right.
     * @param y Throttle Input (-100 to 100). Positive = Forward.
     */
    void compute(int x, int y);
    
    /**
     * @brief Gets the calculated speed for the Left Motor.
     * @return int PWM value (-maxPWM to +maxPWM).
     */
    int getLeft();

    /**
     * @brief Gets the calculated speed for the Right Motor.
     * @return int PWM value (-maxPWM to +maxPWM).
     */
    int getRight();
};

#endif