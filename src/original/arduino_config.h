/* SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ARDUINO_CONFIG_H
#define ARDUINO_CONFIG_H

//Configuration parameters
#define CONFIG_ADC_BUTTON_MAX_BUTTON_PER_CHANNEL 8       //range 1 10
#define CONFIG_ADC_BUTTON_MAX_CHANNEL 3                 // range 1 5
#define CONFIG_ADC_BUTTON_SAMPLE_TIMES 1                // range 1 4
#define CONFIG_BUTTON_DEBOUNCE_TICKS 2                  //range  1 8
#define CONFIG_BUTTON_SHORT_PRESS_TIME_MS 180           //range  50-800
#define CONFIG_BUTTON_LONG_PRESS_TIME_MS 1500           //range  500-5000
#define CONFIG_BUTTON_PERIOD_TIME_MS 5                  // range  2-20
#define CONFIG_BUTTON_SERIAL_TIME_MS 20                 //range  2-1000
#define CONFIG_BUTTON_LONG_PRESS_TOLERANCE_MS 20

#define BUTTON_VER_MINOR  (1)   // ignore this
#define BUTTON_VER_PATCH  (1)   // ignore this
#define BUTTON_VER_MAJOR  (1)   //ignore this

#endif  // BUTTON_CONFIG_H
