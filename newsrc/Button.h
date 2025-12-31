#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

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

#endif