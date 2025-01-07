# Project Microcontroller

## Description

This is an AVR ATmega64-based attendance management system with multiple features including temperature monitoring, RFID access control, and traffic monitoring. The system provides comprehensive management of student attendance with additional environmental monitoring capabilities.

## Features

- Student attendance tracking with EEPROM storage
- Real-time temperature monitoring
- RFID card access control system
- Ultrasonic traffic monitoring
- Real-time clock integration (DS1307)
- Graphical LCD display interface
- 4x4 keypad input
- Buzzer alerts
- Virtual terminal communication
- I2C communication support

## Hardware Components

- ATmega64 microcontroller
- GLCD display
- DS1307 RTC module
- RFID reader
- Ultrasonic sensor
- Temperature sensor
- 4x4 Matrix keypad
- Buzzer
- EEPROM

## Software Requirements

- AVR-GCC compiler
- Proteus for simulation
- AVR Programmer

## Building the Project

The project uses Make for building. To build:

```bash
make all       # Build the complete project
make clean     # Clean build files 
```

## Project Structure

- `src/` - Source code files
  - `main.c` - Main program entry
  - `attendance.c/h` - Attendance system logic
  - `buzzer.c/h` - Buzzer control
  - `ds1307.c/h` - RTC interface
  - `eeprom.c/h` - EEPROM operations
  - `glcd.c/h` - GLCD interface
  - `i2c.c/h` - I2C communication
  - `keypad.c/h` - Keypad interface
  - `rfid.c/h` - RFID reader interface
  - `temperature.c/h` - Temperature sensor
  - `ultrasonic.c/h` - Ultrasonic sensor
  - `Timer.c/h` - Timer utilities

## Contributors

- [Danial](https://github.com/danialmd81)
- [Behdad](https://github.com/Behdad203)

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Notes

- Make sure to set correct fuse bits for 8MHz clock operation
- UART is configured for 9600 baud rate, 8 data bits, no parity
- Refer to schematic diagram for hardware connections
