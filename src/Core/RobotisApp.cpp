/**
 * @file RobotisApp.cpp
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Implementation of RobotisApp Kernel.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "RobotisApp.h"

/**
 * @brief Constructor. Initializes the Logger with the specified baud rate.
 */
RobotisApp::RobotisApp(long baudRate) : _logger(baudRate) {
  _baudRate = baudRate;
  // Note: TaskManager and SerialCommander are initialized automatically
  // by their default constructors.
}

/**
 * @brief Starts the system.
 */
void RobotisApp::begin() {
  // Start Logger (which starts Serial)
  _logger.begin();
  
  // Note: SerialCommander uses the same Serial, so we don't need to begin it twice
  // unless it handles different hardware serials. Here we assume standard Serial.
  
  // Print Boot Message
  _logger.info("-----------------------------");
  _logger.info("RobotisApp Kernel v6.0 Init");
  _logger.info("System Ready.");
  _logger.info("-----------------------------");
}

/**
 * @brief The Heartbeat of the system.
 */
void RobotisApp::update() {
  _scheduler.run(); // Process scheduled tasks
  _cli.check();     // Check for incoming serial commands
}

// =============================================================================
// API PROXIES IMPLEMENTATION
// =============================================================================

void RobotisApp::addTask(VoidFunction callback, unsigned long interval) {
  _scheduler.addTask(callback, interval);
}

void RobotisApp::addCommand(const char* name, VoidFunction callback) {
  _cli.addCommand(name, callback);
}

void RobotisApp::log(const char* msg) {
  _logger.info(msg);
}

void RobotisApp::log(const char* msg, int val) {
  _logger.info(msg, val);
}

Logger& RobotisApp::getLogger() {
  return _logger;
}