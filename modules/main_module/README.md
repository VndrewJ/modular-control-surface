### README for the Main Module

## Hardware + Peripherals
- RP2040
- USB-C Connector
- EC-11 Rotary Encoder + Push Button
- I2C over Magnetic Pogo Pins

## Firmware Architecture
- Encoder uses PIO so doesn't need to worry about aliasing. PIO catches all changes. 

## TO DO
1. Encoder drivers
    - Firmware DONE
    - Need to add cap for filtering (PCB), 1 cap for each pin
2. USB C drivers
3. I2C drivers




