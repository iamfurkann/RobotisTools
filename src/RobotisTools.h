/**
 * @file RobotisTools.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Master Include File for RobotisTools Framework.
 *
 * This single header includes the entire ecosystem:
 * - Core Kernel (App, TaskManager, CLI, Logger)
 * - Hardware Drivers (Button, LED, Sonar, Battery, SmartAnalog)
 * - Utilities (PID, Filters, Timers, DiffDrive, ConfigStore)
 *
 * @version 6.0.0 (Control Systems Edition)
 * @date 2025-12-31
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef ROBOTIS_TOOLS_H
#define ROBOTIS_TOOLS_H

// =============================================================
// ROBOTIS TOOLS FRAMEWORK v6.0
// =============================================================

#include <Arduino.h>

// -------------------------------------------------------------
// 1. UTILITIES & MATH (Bağımsız Modüller)
// -------------------------------------------------------------
// Bu modüller donanımdan bağımsız matematiksel işlemler yapar.
// Diğer modüller (örn. BatteryMonitor) bunları kullanacağı için önce eklenir.

#include "Utils/SimpleTimer.h"   // Zamanlama
#include "Utils/SignalFilter.h"  // Gürültü Filtreleme
#include "Utils/FastPID.h"       // Kontrol Teorisi
#include "Utils/DiffDrive.h"     // Robot Sürüş Matematiği
#include "Utils/ConfigStore.h"   // EEPROM Hafıza Yönetimi (Template)

// -------------------------------------------------------------
// 2. HARDWARE DRIVERS (Donanım Sürücüleri)
// -------------------------------------------------------------
// Fiziksel bileşenleri kontrol eden sınıflar.

#include "Hardware/Button.h"         // Akıllı Buton
#include "Hardware/Led.h"            // Akıllı LED
#include "Hardware/SmartAnalog.h"    // Histerezisli Sensör
#include "Hardware/BatteryMonitor.h" // Pil Takibi
#include "Hardware/AsyncSonar.h"     // Bloklamayan Ultrasonik

// -------------------------------------------------------------
// 3. CORE SYSTEM (İşletim Sistemi Çekirdeği)
// -------------------------------------------------------------
// Sistemin beyni. En son eklenir.

#include "Core/TaskManager.h"     // Görev Yöneticisi
#include "Core/SerialCommander.h" // Seri Komut İşleyici
#include "Core/Logger.h"          // Loglama Sistemi
#include "Core/RobotisApp.h"      // [PATRON] Tüm sistemi yöneten Kernel

#endif // ROBOTIS_TOOLS_H