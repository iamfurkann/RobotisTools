#ifndef LED_H
#define LED_H

#include <Arduino.h>

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

#endif