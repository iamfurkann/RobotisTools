#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4

class Logger {
    private:
        int _level;
        long _baudRate;
    
    public:
        Logger(long baudRate = 9600);

        void begin();
        void setLevel(int level);

        void error(const char* msg);
        void warn(const char* msg);
        void info(const char* msg);
        void debug(const char* msg);

        void info(const char* msg, int value);
};

#endif