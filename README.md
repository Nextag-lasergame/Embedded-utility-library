# Nextag-Lasergame Embedded utility library
Utility library to be used in all embedded applications from Nextag Lasergame
### Supported microcontrollers:
- ATmega328P
### Future microcontroller:
- ATtiny85
### Supported features:
- I2C
    - Slave with custom address
    - Single master system
    - Fully Asynchronous with callbacks
- USART
    - 5, 6, 7, or 8 data bits
    - No, even or odd parity
    - 1 or 2 stop bits
    - Variable baud rate
- Basic logging functionality
    - Premade loggers for uart with baud rate of 9600 and 115200
    - Ability to create your own custom loggers
- Digital IO
### Future features:
- ADC
- SPI
- File IO
- PWM
- Timers

## Running in CLion
If you want to run this application in CLion, be sure to use MinGW on windows instead of the Microsoft Visual Studio compiler.
