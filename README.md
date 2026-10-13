# SmartKeychain V2

**ESP32-C3 Smart Keychain — Embedded Firmware Project**

SmartKeychain V2 is a compact embedded device designed around the ESP32-C3 microcontroller. It combines an OLED user interface, physical button controls, device settings, time utilities, games, sound alerts, and power-management features in a portable keychain form factor.

> **Development status:** Feature-complete status must be confirmed against the final firmware build and hardware test results before release.

## Features

- **OLED interface:** Screen-based navigation and device information.
- **Button controls:** Physical input for menus and applications.
- **Digital clock:** Time display and clock-format settings.
- **Time utilities:** Alarm, timer, and stopwatch applications.
- **Games:** Snake, Reaction, Dodge, and Memory.
- **Device settings:** Configurable user-interface and system preferences.
- **Battery monitoring:** Battery-status display when voltage measurement is configured and calibrated.
- **Sound feedback:** Buzzer alerts and user-interface feedback when supported by the hardware.
- **Connectivity:** Optional Wi-Fi and BLE functionality, subject to firmware configuration.
- **Diagnostics:** Device information and troubleshooting support.
- **Power management:** Display timeout and power-saving behavior where implemented.
- **Persistent settings:** Preferences storage using the ESP32 Arduino framework.

## Hardware

| Component | Purpose |
| --- | --- |
| ESP32-C3 Super Mini | Main microcontroller |
| 0.96-inch I2C OLED | Display and user interface |
| Four physical buttons | Navigation and user input |
| RGB LED | Visual status indication |
| Buzzer | Audio feedback |
| 3.7 V Li-ion battery | Portable power |
| Charging and protection module | Battery charging and protection |

Hardware availability and wiring depend on the assembled revision.

## Software and Tools

- PlatformIO
- Visual Studio Code
- Arduino framework for ESP32
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Arduino `Wire` library
- ESP32 `Preferences` API

## Firmware Architecture

The firmware is organized into functional modules to simplify development and testing.

- `config` — Hardware configuration and shared settings
- `hardware` — Peripheral drivers and hardware interfaces
- `core` — System logic and event handling
- `ui` — Display rendering and navigation
- `apps` — Clock, timer, stopwatch, and games
- `storage` — Persistent settings
- `power` — Power-management functionality

The exact module names and responsibilities should match the current source tree.

## Build Instructions

### Requirements

Install Visual Studio Code and the PlatformIO IDE extension. Connect a compatible ESP32-C3 development board over USB.

### Build

``` bash
pio run
```

### Upload firmware

``` bash
pio run --target upload
```

### Open the serial monitor

``` bash
pio device monitor -b 115200
```

Select the appropriate serial port if multiple devices are connected.

## Hardware Configuration

Before uploading, verify the following in the firmware configuration:

- OLED I2C address and SDA/SCL pins
- Button GPIO assignments and active levels
- RGB LED pin assignments
- Buzzer output configuration
- Battery ADC input and voltage-divider calibration
- Charging-module behavior
- Sleep and wake-up configuration

Do not assume GPIO assignments are interchangeable between ESP32-C3 board revisions.

## Testing

The final release should pass the following checks:

- [x] Firmware compiles successfully.
- [x] Firmware fits within the configured flash partition.
- [x] OLED initializes and renders all screens correctly.
- [x] All four buttons work with reliable debouncing.
- [x] Clock, alarm, timer, and stopwatch behave correctly.
- [x] All four games operate correctly.
- [x] Settings persist after reboot.
- [ ] Battery readings are calibrated against a multimeter.
- [ ] Buzzer and RGB LED outputs operate safely.
- [ ] Sleep and wake-up behavior is verified.
- [x] Wi-Fi and BLE features work if enabled.
- [ ] Extended runtime and recovery tests pass.

## Safety Notes

Use a compatible Li-ion charging and protection circuit. Verify battery voltage limits and all wiring before powering the device. Never drive a motor or other high-current load directly from an ESP32 GPIO.

## Limitations

Without an RTC or external time synchronization, the software clock cannot retain accurate time through complete power loss.

Battery percentage requires calibration. Wireless features, power management, and peripheral behavior depend on the final hardware and firmware configuration.

## Project Repository

[SmartKeychain V2 on GitHub](<https://github.com/pojge2005/SmartKeychain-V2>)

## License

Specify a license before distributing the project for reuse.# SmartKeychain-V2
