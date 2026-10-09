#pragma once

#define FW_NAME "SmartKeychain"
#define FW_VERSION "2.1.0"
#define HW_VERSION "B3"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define OLED_SDA 4
#define OLED_SCL 5

#define BUTTON_1_PIN 0
#define BUTTON_2_PIN 1
#define BUTTON_3_PIN 3
#define BUTTON_4_PIN 10

#define RGB_RED_PIN 6
#define RGB_GREEN_PIN 7
#define RGB_BLUE_PIN 8
#define RGB_COMMON_ANODE false

#define BATTERY_ADC_PIN 2

#define DEFAULT_SCREEN_TIMEOUT_MS 30000UL
#define DEFAULT_SLEEP_TIMEOUT_MS 120000UL

#define BATTERY_LOW_PERCENT 20
#define BATTERY_CRITICAL_PERCENT 5