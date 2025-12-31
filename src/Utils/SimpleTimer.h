#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <Arduino.h>

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
#endif