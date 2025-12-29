/**
 * @file RobotisTools.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of RobotisTools library classes.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "RobotisTools.h"
#include <string.h>

// =============================================================================
// CLASS: BUTTON IMPLEMENTATION
// =============================================================================

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

// =============================================================================
// CLASS: LED IMPLEMENTATION
// =============================================================================

Led::Led(int pin) {
  _pin = pin;
  _state = 1; // Default state (Assuming Active Low for OpenCM)
  _previousMillis = 0;
  digitalWrite(_pin, _state);
}

void Led::begin() {
    pinMode(_pin, OUTPUT);
}

void Led::turnOn() {
  _state = 0; // Active Low
  digitalWrite(_pin, _state);
}

void Led::turnOff() {
  _state = 1;
  digitalWrite(_pin, _state);
}

void Led::toggle() {
  _state = !_state;
  digitalWrite(_pin, _state);
}

/**
 * @brief Non-blocking blink function based on millis().
 */
void Led::blink(int interval) {
  if (millis() - _previousMillis >= interval)
  {
    _previousMillis = millis();
    toggle();
  }
}

// =============================================================================
// CLASS: SIMPLE TIMER IMPLEMENTATION
// =============================================================================

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

// =============================================================================
// CLASS: SIGNAL FILTER IMPLEMENTATION
// =============================================================================

SignalFilter::SignalFilter(int size) {
  _size = size;
  _readings = NULL;
  _index = 0;
  _total = 0;
  _average = 0;
}

/**
 * @brief Destructor to clean up dynamic memory.
 * REQUIRED to prevent memory leaks in C++.
 */
SignalFilter::~SignalFilter() {
  if (_readings != NULL) {
    delete[] _readings;
  }
}

void SignalFilter::begin() {
  // Allocate memory for the filter buffer
  _readings = new int[_size];
  int i;

  // Initialize buffer with 0
  i = 0;
  while (i < _size)
    _readings[i++] = 0;
}

/**
 * @brief Adds a new value and calculates the Moving Average.
 */
int SignalFilter::filter(int input) {
  _total = _total - _readings[_index];
  _readings[_index] = input;
  _total = _total + _readings[_index];
  _index = _index + 1;
  
  // Wrap around index (Circular Buffer)
  if (_index >= _size)
    _index = 0;
  
  _average = _total / _size;
  return _average;
}

// =============================================================================
// CLASS: TASK MANAGER IMPLEMENTATION
// =============================================================================

TaskManager::TaskManager() {
  _taskCount = 0;
}

void TaskManager::addTask(VoidFunction callback, unsigned long interval) {
  if (_taskCount < MAX_TASKS) 
  {
    _tasks[_taskCount].func = callback;
    _tasks[_taskCount].interval = interval;
    _tasks[_taskCount].lastRun = 0;
    _tasks[_taskCount].active = true;
    _taskCount++;
  }
}

/**
 * @brief Main scheduler loop. Checks all tasks and runs them if due.
 */
void TaskManager::run() {
  unsigned long currentMillis = millis();
  int i;

  i = 0;
  while (i < _taskCount)
  {
    if (_tasks[i].active)
    {
      if (currentMillis - _tasks[i].lastRun >= _tasks[i].interval)
      {
        _tasks[i].lastRun = currentMillis;
        _tasks[i].func();
      }
    }
    i++;
  }
}

// =============================================================================
// CLASS: SERIAL COMMANDER IMPLEMENTATION
// =============================================================================

SerialCommander::SerialCommander() {
  _cmdCount = 0;
  _bufIndex = 0;
  _buffer[0] = '\0';
}

void SerialCommander::begin(long baudRate) {
  Serial.begin(baudRate);
}

void SerialCommander::addCommand(const char* name, VoidFunction callback) {
  if (_cmdCount < MAX_COMMANDS)
  {
    _commands[_cmdCount].name = name;
    _commands[_cmdCount].callback = callback;
    _cmdCount++;
  }
}

/**
 * @brief Process incoming Serial data and execute matching commands.
 */
void SerialCommander::check() {
  int i;
  while (Serial.available() > 0)
  {
    char c = (char)Serial.read();

    // Handle Line Feed (Enter key)
    if (c == '\n')
    {
      if (_bufIndex > 0)
      {
        _buffer[_bufIndex] = '\0'; // Null-terminate string

        bool found = false;
        i = 0;
        
        // Scan for matching command
        while (i < _cmdCount)
        {
          if (strcmp(_buffer, _commands[i].name) == 0)
          {
            _commands[i].callback();
            Serial.println("OK");
            found = true;
            break;
          }
          i++;
        }

        if (!found)
        {
          Serial.print("ERROR: ");
          Serial.println(_buffer);
        }

        // Reset buffer
        _bufIndex = 0;
        memset(_buffer, 0, CMD_BUFFER_SIZE);
      }
    }
    else
    {
      // Buffer overflow protection & ASCII check
      if (_bufIndex < CMD_BUFFER_SIZE - 1 && c >= 32 && c <= 126)
      {
        _buffer[_bufIndex] = c;
        _bufIndex++;
      }
    }
  }
}