#ifndef SERIAL_COMMANDER_H
#define SERIAL_COMMANDER_H

#include <Arduino.h>

#define MAX_COMMANDS 10
#define CMD_BUFFER_SIZE 32

// Function pointer type for command callbacks
typedef void (*VoidFunction)();

/**
 * @brief Structure for mapping command strings to functions.
 */
struct Command {
  const char* name;
  VoidFunction callback;
};

/**
 * @brief Handles text-based commands via Serial port.
 */
class SerialCommander 
{
  private:
    Command _commands[MAX_COMMANDS];
    int _cmdCount;
    char _buffer[CMD_BUFFER_SIZE];
    int _bufIndex;

  public:
    SerialCommander();
    
    /**
     * @brief Starts the Serial communication.
     * @param baudRate Baud rate (e.g., 9600, 115200).
     */
    void begin(long baudRate);

    /**
     * @brief Registers a new command.
     * @param name Command string (e.g., "led_on"). Case-sensitive.
     * @param callback Function to execute when command is received.
     */
    void addCommand(const char* name, VoidFunction callback);

    /**
     * @brief Checks Serial buffer for new commands. Must be called in loop().
     */
    void check();
};

#endif