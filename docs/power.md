# SmartKeychain V2 Power Notes

## Battery

The prototype has used a nominal 3.7 V, 1000 mAh Li-ion cell. Confirm the actual cell rating and condition before use.

## Charging and Protection

- Use a charger designed for the specific Li-ion cell chemistry and configuration.
- Verify the charging module current limit and protection features.
- Never connect the cell directly to a GPIO.
- Check polarity and voltage with a multimeter before connecting the ESP32 board.
- Do not assume a charging module provides all required battery protection.

## Battery Measurement

Battery percentage is meaningful only when the circuit includes a suitable voltage-sensing path and the firmware is calibrated against measured voltages. Do not publish a percentage as accurate without calibration.

## Runtime and Clock Limitations

Runtime depends on display brightness, radio use, firmware activity, battery condition, and regulator efficiency. Measure actual current draw to estimate runtime.

Without a dedicated RTC or external time synchronization, a software clock based on uptime will not preserve accurate time through complete power loss.

## Test Record

Record battery voltage, current draw, charging behavior, sleep current, wake-up behavior, and test duration for each hardware revision.
