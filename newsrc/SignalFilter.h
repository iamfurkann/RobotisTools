#ifndef SIGNAL_FILTER_H
#define SIGNAL_FILTER_H

#include <Arduino.h>

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
#endif