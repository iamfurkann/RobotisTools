/**
 * @file FastPID.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief High-Performance PID Controller Implementation.
 * Features: Integral Windup Guard, Derivative on Measurement, Output Limiting.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef FAST_PID_H
#define FAST_PID_H

#include <Arduino.h>

/**
 * @brief A standard PID controller optimized for microcontrollers.
 * Uses floating point math to calculate control signals based on error.
 */
class FastPID {
  private:
    float _kp;             // Proportional Gain
    float _ki;             // Integral Gain
    float _kd;             // Derivative Gain
    
    float _lastInput;      // Last sensor reading (for Derivative calc)
    float _integral;       // Accumulated error
    
    float _outputMin;      // Lower limit of output (e.g. -255)
    float _outputMax;      // Upper limit of output (e.g. 255)
    
    unsigned long _lastTime;
    unsigned long _sampleTime; // Calculation interval in ms
    float _lastOutput;     // Stores result if called before sample time

  public:
    /**
     * @brief Construct a new FastPID object.
     * @param kp Proportional Term (Reaction speed).
     * @param ki Integral Term (Steady-state error correction).
     * @param kd Derivative Term (Damping/Prediction).
     * @param sampleTime How often to calculate PID in ms (default: 20ms).
     */
    FastPID(float kp, float ki, float kd, int sampleTime = 20);

    /**
     * @brief Sets the output limits to prevent saturation.
     * @param min Minimum output (e.g., -255 for reverse motor).
     * @param max Maximum output (e.g., 255 for forward motor).
     */
    void setOutputLimits(float min, float max);

    /**
     * @brief Updates PID tunings dynamically.
     */
    void setTunings(float kp, float ki, float kd);

    /**
     * @brief Calculates the PID output.
     * Should be called frequently in the loop. It will only calculate
     * if the sample time has passed.
     * * @param setpoint The target value (Where we want to be).
     * @param input The actual sensor value (Where we are now).
     * @return float The control output (Power to apply to motors).
     */
    float compute(float setpoint, float input);

    /**
     * @brief Resets the integral term and history.
     * Call this when starting a new motion to avoid old accumulated errors.
     */
    void reset();
};

#endif