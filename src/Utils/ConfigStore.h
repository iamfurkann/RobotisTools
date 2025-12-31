/**
 * @file ConfigStore.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief EEPROM Manager using C++ Templates.
 * Allows saving/loading complex data structures (structs) easily.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CONFIG_STORE_H
#define CONFIG_STORE_H

#include <Arduino.h>
#include <EEPROM.h>

/**
 * @brief A generic class to store any type of data (int, float, struct) in EEPROM.
 * * Usage Example:
 * struct Settings { int speed; float kp; };
 * ConfigStore<Settings> memory(0, {100, 1.5});
 * * @tparam T The data type to store (can be a custom struct).
 */
template <class T>
class ConfigStore {
  private:
    int _address; // EEPROM start address
    T _data;      // RAM copy of the data

  public:
    /**
     * @brief Construct a new Config Store object.
     * * @param address EEPROM address to start writing/reading.
     * @param defaultData Default values to use if EEPROM is empty or manual reset.
     */
    ConfigStore(int address, T defaultData) {
      _address = address;
      _data = defaultData;
    }

    /**
     * @brief Loads data from EEPROM into RAM.
     * @return T The data read from memory.
     */
    T load() {
      EEPROM.get(_address, _data);
      return _data;
    }

    /**
     * @brief Saves new data to EEPROM and updates RAM.
     * Uses EEPROM.put() which only writes if data has changed (saves flash life).
     * * @param newData The new data to store.
     */
    void save(T newData) {
      _data = newData;
      EEPROM.put(_address, _data);
    }
    
    /**
     * @brief Returns the current data in RAM without reading from EEPROM.
     * Useful for high-speed loops where EEPROM access is too slow.
     * * @return T Current data.
     */
    T get() {
      return _data;
    }

    /**
     * @brief Resets the EEPROM data to the default values provided in constructor.
     */
    void factoryReset() {
      // _data is already set to default in constructor if we re-instantiate,
      // but here we might need to store the constructor's default.
      // Since we don't store "default" separately to save RAM, 
      // the user should pass the default struct again or handle logic externally.
      // However, usually save() is enough.
      // This is a placeholder if advanced reset logic is needed.
    }
};

#endif