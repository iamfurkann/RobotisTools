/**
 * @file AsyncSonar.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Non-blocking Ultrasonic Sensor Driver (HC-SR04).
 * Uses a State Machine to handle trigger pulses without delay().
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef ASYNC_SONAR_H
#define ASYNC_SONAR_H

#include <Arduino.h>

// =============================================================================
// STATE DEFINITIONS
// =============================================================================
#define SONAR_STATE_IDLE       0
#define SONAR_STATE_TRIG_LOW   1
#define SONAR_STATE_TRIG_HIGH  2
#define SONAR_STATE_WAIT_ECHO  3

/**
 * @brief Driver class for HC-SR04 Ultrasonic Sensors.
 * Implements a non-blocking state machine for the Trigger phase.
 */
class AsyncSonar {
  private:
    int _trigPin;
    int _echoPin;
    int _state;             // Current state of the machine
    unsigned long _timer;   // To track microsecond timings
    float _distance;        // Last calculated distance in cm
    unsigned long _timeout; // Max wait time for echo

  public:
    /**
     * @brief Construct a new Async Sonar object.
     * @param trigPin Digital pin connected to Trig.
     * @param echoPin Digital pin connected to Echo.
     */
    AsyncSonar(int trigPin, int echoPin);

    /**
     * @brief Initializes the pins.
     */
    void begin();
    
    /**
     * @brief Manually starts a new measurement sequence.
     * Call this when you want to refresh the distance.
     */
    void startMeasure();
    
    /**
     * @brief Main state machine updater.
     * Must be called frequently in the loop() or via TaskManager.
     * Handles the microsecond timing logic.
     */
    void update();
    
    /**
     * @brief Returns the last measured distance.
     * @return float Distance in centimeters (cm).
     */
    float getDistance();
};

#endif