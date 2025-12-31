/**
 * @file AsyncSonar.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of AsyncSonar class.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "AsyncSonar.h"

/**
 * @brief Constructor. Sets pins and default timeout (~400cm range).
 */
AsyncSonar::AsyncSonar(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
  _state = SONAR_STATE_IDLE;
  _distance = 0.0;
  _timeout = 24000; // ~4 meters max distance timeout in microseconds
}

void AsyncSonar::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_trigPin, LOW); // Ensure trigger is low initially
}

void AsyncSonar::startMeasure() {
  // Only start if we are idle to prevent overlapping measurements
  if (_state == SONAR_STATE_IDLE) 
  {
    _state = SONAR_STATE_TRIG_LOW;
    _timer = micros();
  }
}

/**
 * @brief State Machine logic.
 * 1. Ensure Low (2us) -> 2. Trigger High (10us) -> 3. Wait Echo
 */
void AsyncSonar::update() {
  unsigned long currentMicros = micros();

  switch (_state) {
    case SONAR_STATE_TRIG_LOW:
      // Step 1: Hold Trig LOW for at least 2us
      digitalWrite(_trigPin, LOW);
      if (currentMicros - _timer >= 2) 
      {
        digitalWrite(_trigPin, HIGH);
        _timer = currentMicros;
        _state = SONAR_STATE_TRIG_HIGH;
      }
      break;

    case SONAR_STATE_TRIG_HIGH:
      // Step 2: Hold Trig HIGH for at least 10us
      if (currentMicros - _timer >= 10) 
      {
        digitalWrite(_trigPin, LOW);
        _state = SONAR_STATE_WAIT_ECHO;
      }
      break;

    case SONAR_STATE_WAIT_ECHO:
      // Step 3: Read Echo Pulse
      // Note: pulseIn() is technically blocking, but we use a timeout.
      // For a purely non-blocking approach, pin change interrupts would be required,
      // which reduces portability across different Arduino boards.
      // This hybrid approach is safe for most loops.
      
      long duration = pulseIn(_echoPin, HIGH, _timeout);
      
      if (duration > 0) 
      {
        // Speed of sound: 343m/s or 0.0343 cm/us
        // Distance = (Time * Speed) / 2
        _distance = (float)duration * 0.0343 / 2.0;
      } 
      else 
      {
        // If 0, it means timeout (out of range or error)
        // We can keep the last valid distance or set to -1.
        // Keeping last valid distance is usually safer for robots.
      }
      
      _state = SONAR_STATE_IDLE; // Measurement done, go back to IDLE
      break;
  }
}

float AsyncSonar::getDistance() {
  return _distance;
}