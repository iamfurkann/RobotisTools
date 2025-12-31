#include "SerialCommander.h"

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