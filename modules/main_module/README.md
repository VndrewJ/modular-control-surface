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
    - Need to create a custom HID report ID for each peripheral type + submodule ID 
3. I2C drivers
    - Report IDs will have to be dynamically assigned as a user might want multiple of the same submodule. 
    - Needs a 5 pinned magnetic connector, only have 4 pin for now.




