/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Arduino Mega with RAMPS v1.4 (or v1.3) pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_14_EFB (Hotend, Fan, Bed)
 *  RAMPS_14_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_14_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_14_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_14_SF  (Spindle, Controller Fan)
 *
 *  RAMPS_13_EFB (Hotend, Fan, Bed)
 *  RAMPS_13_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_13_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_13_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_13_SF  (Spindle, Controller Fan)
 *
 *  Other pins_MYBOARD.h files may override these defaults
 *
 *  Differences between
 *  RAMPS_13 | RAMPS_14
 *         7 | 11
 */

#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu."
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME "TRIGORILLA"
#endif

//
// Servos
//
#ifdef IS_RAMPS_13
  //#define SERVO0_PIN        7   // RAMPS_13 // Will conflict with BTN_EN2 on LCD_I2C_VIKI
#else
  //#define SERVO0_PIN       11
#endif
#define SERVO1_PIN          6
#define SERVO2_PIN          5
#ifndef SERVO3_PIN
  #define SERVO3_PIN        4
#endif

//
// Limit Switches
//
#define X_MIN_PIN           3
#define X_MAX_PIN         43
#define Y_MIN_PIN          42
#define Y_MAX_PIN          -1
#define Z_MIN_PIN          18
#define Z_MAX_PIN          11 // Set to 11 to use ABL Sensor

//
// Z Probe (when not Z_MIN_PIN)
//
#define Z_MIN_PROBE_PIN  11

//
// Steppers
//
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Y2_STEP_PIN        36
#define Y2_DIR_PIN         34
#define Y2_ENABLE_PIN      30

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define Z2_STEP_PIN        36
#define Z2_DIR_PIN         34
#define Z2_ENABLE_PIN      30

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24



//
// Temperature Sensors
//
#define TEMP_0_PIN         13   // Analog Input
#define TEMP_1_PIN         15   // Analog Input
#define TEMP_2_PIN         12   // Analog Input
#define TEMP_BED_PIN       14   // Analog Input


#define HEATER_0_PIN     10
#define HEATER_1_PIN   45
#define FAN_PIN        9
#define HEATER_BED_PIN 8
#define FAN2_PIN       44


//
// Misc. Functions
//
#define SDSS               53
#define LED_PIN            13
//OK UP TO HERE


// define digital pin 4 for the filament runout sensor. Use the RAMPS 1.4 digital input 4 on the servos connector
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    19
#endif

/*
#ifndef PS_ON_PIN
  #define PS_ON_PIN        12
#endif
*/


//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ENABLED(ANYCUBIC_TFT_MODEL)
	#define KILL_PIN        41
	#define BEEPER_PIN       31
  #define SD_DETECT_PIN    49
  #define CONTROLLER_FAN_PIN  7
#endif

//////////////////////////
// Power loss recovery  //
//////////////////////////

#if defined(POWER_LOSS_RECOVERY)
   #define OUTAGETEST_PIN       79
   #define OUTAGECON_PIN        58
#endif
