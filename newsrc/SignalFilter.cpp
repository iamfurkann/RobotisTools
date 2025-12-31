#include "SignalFilter.h"

SignalFilter::SignalFilter(int size) {
  _size = size;
  _readings = NULL;
  _index = 0;
  _total = 0;
  _average = 0;
}

/**
 * @brief Destructor to clean up dynamic memory.
 * REQUIRED to prevent memory leaks in C++.
 */
SignalFilter::~SignalFilter() {
  if (_readings != NULL) {
    delete[] _readings;
  }
}

void SignalFilter::begin() {
  // Allocate memory for the filter buffer
  _readings = new int[_size];
  int i;

  // Initialize buffer with 0
  i = 0;
  while (i < _size)
    _readings[i++] = 0;
}

/**
 * @brief Adds a new value and calculates the Moving Average.
 */
int SignalFilter::filter(int input) {
  _total = _total - _readings[_index];
  _readings[_index] = input;
  _total = _total + _readings[_index];
  _index = _index + 1;
  
  // Wrap around index (Circular Buffer)
  if (_index >= _size)
    _index = 0;
  
  _average = _total / _size;
  return _average;
}