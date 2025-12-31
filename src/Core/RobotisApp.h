/**
 * @file RobotisApp.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Main Application Kernel for RobotisTools Framework.
 * Acts as a Facade to manage TaskManager, SerialCommander, and Logger.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef ROBOTIS_APP_H
#define ROBOTIS_APP_H

#include <Arduino.h>

// Aynı klasörde (src/Core) oldukları için doğrudan çağırıyoruz
#include "TaskManager.h"
#include "SerialCommander.h"
#include "Logger.h"

/**
 * @brief The Kernel class that orchestrates the entire system.
 * Usage: Instantiate one global object, configure in setup(), run update() in loop().
 */
class RobotisApp {
  private:
    TaskManager _scheduler;       // Manages periodic tasks
    SerialCommander _cli;         // Manages Serial commands
    Logger _logger;               // Manages logging output
    long _baudRate;               // Serial communication speed

  public:
    /**
     * @brief Construct a new Robotis App object.
     * @param baudRate Serial baud rate (default: 9600).
     */
    RobotisApp(long baudRate = 9600);

    // =========================================================================
    // SYSTEM LIFECYCLE
    // =========================================================================

    /**
     * @brief Initializes the core systems (Serial, Logger, etc.).
     * Must be called in setup().
     */
    void begin();

    /**
     * @brief Main system loop. Handles multitasking and CLI.
     * Must be called in loop().
     */
    void update();

    // =========================================================================
    // API PROXIES (Kullanıcı Kolaylığı İçin Yönlendiriciler)
    // =========================================================================

    /**
     * @brief Schedules a task to run repeatedly.
     * @param callback Function to call.
     * @param interval Time in ms between calls.
     */
    void addTask(VoidFunction callback, unsigned long interval);

    /**
     * @brief Registers a new Serial text command.
     * @param name Command string (e.g., "stop").
     * @param callback Function to execute.
     */
    void addCommand(const char* name, VoidFunction callback);

    /**
     * @brief Logs a message via the Logger module.
     * @param msg The message to print.
     */
    void log(const char* msg);

    /**
     * @brief Logs a message and a value via the Logger module.
     * @param msg The label message.
     * @param val The integer value.
     */
    void log(const char* msg, int val);

    // =========================================================================
    // ACCESSORS (Gelişmiş ayarlar için alt modüllere doğrudan erişim)
    // =========================================================================
    
    /**
     * @brief Get reference to the internal Logger.
     * Allows user to change log level: app.getLogger().setLevel(...)
     */
    Logger& getLogger();
};

#endif