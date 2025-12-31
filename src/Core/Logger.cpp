/**
 * @file Logger.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of Logger class.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "Logger.h"

Logger::Logger(long baudRate) {
  _baudRate = baudRate;
  _level = LOG_LEVEL_INFO; // Default level is INFO
}

void Logger::begin() {
  // Start Serial only if not already started (Safe check)
  if (!Serial) 
  {
    Serial.begin(_baudRate);
    // Add small delay for OpenCM/STM32 USB stability
    delay(100); 
  }
}

void Logger::setLevel(int level) {
  _level = level;
}

// =============================================================================
// TEXT ONLY IMPLEMENTATIONS
// =============================================================================

void Logger::error(const char* msg) {
  if (_level >= LOG_LEVEL_ERROR) 
  {
    Serial.print("[ERROR] ");
    Serial.println(msg);
  }
}

void Logger::warn(const char* msg) {
  if (_level >= LOG_LEVEL_WARN) 
  {
    Serial.print("[WARN]  ");
    Serial.println(msg);
  }
}

void Logger::info(const char* msg) {
  if (_level >= LOG_LEVEL_INFO) 
  {
    Serial.print("[INFO]  ");
    Serial.println(msg);
  }
}

void Logger::debug(const char* msg) {
  if (_level >= LOG_LEVEL_DEBUG) 
  {
    Serial.print("[DEBUG] ");
    Serial.println(msg);
  }
}

// =============================================================================
// TEXT + VALUE IMPLEMENTATIONS
// =============================================================================

void Logger::error(const char* msg, int value) {
  if (_level >= LOG_LEVEL_ERROR) 
  {
    Serial.print("[ERROR] ");
    Serial.print(msg);
    Serial.print(": ");
    Serial.println(value);
  }
}

void Logger::warn(const char* msg, int value) {
  if (_level >= LOG_LEVEL_WARN)
  {
    Serial.print("[WARN]  ");
    Serial.print(msg);
    Serial.print(": ");
    Serial.println(value);
  }
}

void Logger::info(const char* msg, int value) {
  if (_level >= LOG_LEVEL_INFO)
  {
    Serial.print("[INFO]  ");
    Serial.print(msg);
    Serial.print(": ");
    Serial.println(value);
  }
}

void Logger::debug(const char* msg, int value) {
  if (_level >= LOG_LEVEL_DEBUG)
  {
    Serial.print("[DEBUG] ");
    Serial.print(msg);
    Serial.print(": ");
    Serial.println(value);
  }
}