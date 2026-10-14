# SmartKeychain V2 Architecture

## System Overview

    User
      |
      v
    Four buttons --> Input and navigation logic --> OLED UI
                             |                       |
                             v                       v
                       Device settings         Applications
                             |                       |
                             v                       v
                      Persistent storage       GPIO/peripherals
                                                     |
                             +-----------------------+------------------+
                             |                       |                  |
                             v                       v                  v
                         SSD1306 OLED             RGB LED            Buzzer
                         (I2C interface)         (optional)          (optional)

    Battery --> Charging/protection circuit --> Board power input

## Hardware Baseline

- ESP32-C3 development board
- SSD1306-compatible I2C OLED
- Four physical navigation buttons
- Optional RGB LED and buzzer
- Li-ion cell with a compatible charging and protection circuit

Confirm the actual parts and wiring against the assembled board before treating this list as a bill of materials.

## Build Commands

    pio run
    pio run --target upload
    pio device monitor -b 115200

The repository uses PlatformIO, the ESP32-C3 DevKitM-1 board definition, and the Arduino framework.

## Validation

For each release, record the board revision, GPIO mapping, firmware commit, build result, and hardware test results. Do not mark a feature as verified based only on documentation.
