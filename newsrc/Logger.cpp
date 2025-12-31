#include "Logger.h"

Logger::Logger(long baudRate) {
    _baudRate = baudRate;
    _level = LOG_LEVEL_NONE;
}

void Logger::begin() {
    Serial.begin(_baudRate);
}

void Logger::setLevel(int level) {
    _level = level;
}

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
        Serial.print("[WARN] ");
        Serial.println(msg);
    }
}

void Logger::info(const char* msg) {
    if (_level >= LOG_LEVEL_INFO)
    {
        Serial.print("[INFO] ");
        Serial.println(msg);
    }
}

void Logger::info(const char* msg, int value) {
    if (_level >= LOG_LEVEL_INFO)
    {
        Serial.print("[INFO] ");
        Serial.print(msg);
        Serial.print(": ");
        Serial.println(value);
    }
}

void Logger::debug(const char* msg) {
    if (_level >= LOG_LEVEL_DEBUG)
    {
        Serial.print("[DEBUG] ");
        Serial.println(msg);
    }
}