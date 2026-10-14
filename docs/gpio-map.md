# SmartKeychain V2 GPIO Map

The PlatformIO configuration targets esp32-c3-devkitm-1. Confirm every pin against the actual board and firmware source before wiring hardware.

## Interfaces to Verify

| Device | Signal | Required verification |
| --- | --- | --- |
| SSD1306 OLED | SDA | Match the configured I2C SDA pin |
| SSD1306 OLED | SCL | Match the configured I2C SCL pin |
| Button 1 | Previous | Confirm GPIO and active level |
| Button 2 | Next | Confirm GPIO and active level |
| Button 3 | Select | Confirm GPIO and active level |
| Button 4 | Back | Confirm GPIO and active level |
| RGB LED | R/G/B | Confirm pin assignments and current limiting |
| Buzzer | Signal | Confirm output pin and driver circuit |
| Battery monitor | ADC | Confirm divider ratio and ADC calibration |

## I2C Note

A previous hardware check detected an I2C device at address 0x3C, consistent with a common SSD1306 OLED configuration. Re-run an I2C scan on the current board if the display does not initialize.

Do not copy ESP32 or ESP32-S3 pin mappings onto an ESP32-C3 without checking the board pinout.
