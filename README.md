# SmartKeychain V2

**ESP32-C3 | Embedded Firmware | OLED UI | PlatformIO**

SmartKeychain V2 is a portable embedded-device project built around an ESP32-C3 board. It explores a compact OLED interface, physical-button navigation, time utilities, small games, and device settings.

> **Status:** Prototype documentation. Confirm the current firmware source and hardware revision before treating any optional feature as implemented or tested.

## Core Hardware

| Component | Role | Notes |
| --- | --- | --- |
| ESP32-C3 development board | Main controller | Repository target: esp32-c3-devkitm-1 |
| SSD1306-compatible I2C OLED | Display | A previous scan detected address 0x3C |
| Four push buttons | Previous, Next, Select, Back | Confirm GPIO assignments in the firmware |
| RGB LED | Status feedback | Use suitable current-limiting resistors |
| Buzzer | Audio feedback | Optional, verify driver requirements |
| 3.7 V Li-ion cell | Portable power | Confirm cell rating and protection |
| Charging module | Battery charging | Verify charging and protection specifications |

## Software Stack

- PlatformIO
- Arduino framework for ESP32
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Arduino Wire library
- ESP32 Preferences API, where used by the firmware

## Build and Upload

Install Visual Studio Code and the PlatformIO IDE extension. Connect the target board over USB.

Build:

    pio run

Upload:

    pio run --target upload

Serial monitor:

    pio device monitor -b 115200

Select the correct serial port if more than one device is connected.

## Hardware Setup Checklist

Before powering the assembled device:

1. Confirm the board model and GPIO assignments.
2. Verify OLED SDA/SCL wiring and I2C address.
3. Check button polarity and input configuration.
4. Verify RGB LED resistors and buzzer driver circuit.
5. Check battery polarity, charging module, and protection circuit.
6. Measure supply voltage with a multimeter.

Do not copy pin assignments from a different ESP32 family board without checking its pinout.

## Architecture and Hardware Notes

- [Firmware architecture](docs/architecture.md)
- [GPIO verification map](docs/gpio-map.md)
- [Power and battery notes](docs/power.md)

## Feature Verification

Use the checklist below to record actual hardware and firmware test results.

- [ ] Firmware builds successfully from the current commit.
- [ ] OLED starts and all implemented screens render correctly.
- [ ] Four buttons respond reliably and are debounced.
- [ ] Implemented clock and time utilities behave correctly.
- [ ] Implemented games run without blocking other UI behavior.
- [ ] Settings persist after reboot, if persistence is implemented.
- [ ] Battery measurement is calibrated, if supported by the hardware.
- [ ] Wireless features are tested, if enabled.
- [ ] Sleep, wake-up, and extended runtime are tested.

Do not mark a check as complete until it has been verified on the target hardware.

## Known Limitations

A software clock based only on uptime will not keep accurate time through complete power loss without an RTC or external time synchronization. Battery percentage also requires a suitable measurement circuit and calibration.

## Repository

[Source code](https://github.com/pojge2005/SmartKeychain-V2)

## License

Add a license before distributing the source for reuse.
