/**
 * @file RobotisTools.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Professional utility library for Embedded Systems (Task Manager, CLI, Smart I/O)
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef ROBOTISTOOLS_H
#define ROBOTISTOOLS_H

#include <Arduino.h>

// =============================================================================
// CLASS: BUTTON
// =============================================================================
/**
 * @brief Handles physical button inputs with debouncing and hold detection.
 */
class Button 
{
  private:
    int _pin;
    int _lastState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;

  public:
    /**
     * @brief Construct a new Button object.
     * @param pin The digital pin connected to the button.
     */
    Button(int pin);

    /**
     * @brief Initializes the button pin (usually INPUT_PULLDOWN).
     */
    void begin();

    /**
     * @brief Checks if the button was pressed (Rising Edge).
     * @return true if a valid press is detected after debouncing.
     */
    bool isPressed();

    /**
     * @brief Checks if the button is currently held down.
     * @param duration The duration in milliseconds to consider as "held".
     * @return true if button is held longer than duration.
     */
    bool isHeld(int duration);
};

// =============================================================================
// CLASS: LED
// =============================================================================
/**
 * @brief Manages LED output with non-blocking blink and toggle features.
 */
class Led
{
  private:
    int _pin;
    bool _state;
    unsigned long _previousMillis;

  public:
    /**
     * @brief Construct a new Led object.
     * @param pin The digital pin connected to the LED.
     */
    Led(int pin);

    /**
     * @brief Initializes the LED pin as OUTPUT.
     */
    void begin();

    /**
     * @brief Turns the LED on (LOW for OpenCM, HIGH for others depending on wiring).
     */
    void turnOn();

    /**
     * @brief Turns the LED off.
     */
    void turnOff();

    /**
     * @brief Toggles the LED state (On -> Off, Off -> On).
     */
    void toggle();

    /**
     * @brief Blinks the LED without blocking code execution.
     * @param interval Blink interval in milliseconds.
     */
    void blink(int interval);
};

// =============================================================================
// CLASS: SIMPLE TIMER
// =============================================================================
/**
 * @brief A non-blocking timer helper to replace manual millis() calculations.
 */
class SimpleTimer
{
  private:
    unsigned long _interval;
    unsigned long _previousMillis;

  public:
    /**
     * @brief Construct a new Simple Timer object.
     * @param interval Time interval in milliseconds.
     */
    SimpleTimer(unsigned long interval);

    /**
     * @brief Updates the timer interval.
     * @param interval New interval in milliseconds.
     */
    void setInterval(unsigned long interval);

    /**
     * @brief Checks if the timer interval has passed.
     * @return true if time is up (automatically resets the timer).
     */
    bool isReady();

    /**
     * @brief Manually resets the timer counter.
     */
    void reset();
};

// =============================================================================
// CLASS: SIGNAL FILTER
// =============================================================================
/**
 * @brief Implements a Moving Average Filter to smooth noisy sensor data.
 */
class SignalFilter
{
  private:
    int _size;
    int* _readings; // Dynamic array
    int _index;
    long _total;
    int _average;

  public:
    /**
     * @brief Construct a new Signal Filter object.
     * @param size Number of samples to average (Window Size).
     */
    SignalFilter(int size);

    /**
     * @brief Destructor to clean up dynamic memory.
     */
    ~SignalFilter();
    
    /**
     * @brief Allocates memory and initializes filter buffer.
     */
    void begin();

    /**
     * @brief Adds a new value and returns the filtered average.
     * @param input Raw sensor value.
     * @return int Smoothed (averaged) value.
     */
    int filter(int input);
};

// =============================================================================
// CLASS: TASK MANAGER
// =============================================================================

// Function pointer type for tasks
typedef void (*VoidFunction)();

#define MAX_TASKS 10

/**
 * @brief Structure representing a single task.
 */
struct Task {
  VoidFunction func;
  unsigned long interval;
  unsigned long lastRun;
  bool active;
};

/**
 * @brief A cooperative scheduler to run multiple functions periodically.
 */
class TaskManager
{
  private:
    Task _tasks[MAX_TASKS];
    int _taskCount;

  public:
    TaskManager();

    /**
     * @brief Adds a function to the scheduler.
     * @param callback The void function to call.
     * @param interval How often to call it (in milliseconds).
     */
    void addTask(VoidFunction callback, unsigned long interval);

    /**
     * @brief Main loop runner. Must be called inside loop().
     */
    void run();
};

// =============================================================================
// CLASS: SERIAL COMMANDER
// =============================================================================

#define MAX_COMMANDS 10
#define CMD_BUFFER_SIZE 32

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