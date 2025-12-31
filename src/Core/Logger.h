/**
 * @file Logger.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Professional Logging System with Levels (Error, Warn, Info, Debug).
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// =============================================================================
// LOG LEVELS
// =============================================================================
#define LOG_LEVEL_NONE  0  // No output (Silent Mode)
#define LOG_LEVEL_ERROR 1  // Only critical errors
#define LOG_LEVEL_WARN  2  // Errors + Warnings
#define LOG_LEVEL_INFO  3  // Standard messages (Default)
#define LOG_LEVEL_DEBUG 4  // Verbose output for debugging

/**
 * @brief Handles system-wide logging via Serial port.
 * Allows filtering messages based on importance (Level).
 */
class Logger {
  private:
    int _level;
    long _baudRate;

  public:
    /**
     * @brief Construct a new Logger object.
     * @param baudRate Serial communication speed (default: 9600).
     */
    Logger(long baudRate = 9600);
    
    /**
     * @brief Starts the Serial connection.
     */
    void begin();

    /**
     * @brief Sets the verbosity level of the logger.
     * @param level One of LOG_LEVEL_XXX constants.
     */
    void setLevel(int level);
    
    // =========================================================================
    // LOGGING METHODS (TEXT ONLY)
    // =========================================================================
    
    /**
     * @brief Logs a critical error. Always shows unless level is NONE.
     */
    void error(const char* msg);

    /**
     * @brief Logs a warning message.
     */
    void warn(const char* msg);

    /**
     * @brief Logs a standard information message.
     */
    void info(const char* msg);

    /**
     * @brief Logs detailed debug information.
     */
    void debug(const char* msg);
    
    // =========================================================================
    // LOGGING METHODS (TEXT + VALUE)
    // =========================================================================

    void error(const char* msg, int value);
    void warn(const char* msg, int value);
    void info(const char* msg, int value);
    void debug(const char* msg, int value);
};

#endif