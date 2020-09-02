# LCD_VU
This is a library for displaying audio level (dBu) using 16x2 LCD, controlled using LiquidCrystal_I2C library. VU level is represented by 14 bars segment, the default audio level range are between -25dBu to 2dBu. As this is only intended for a simple display unit, and not for measurement unit, the result may be less acurrate compared to a professional measurement tool.

## Requirement
You need to download LiquidCrystal_I2C library to use this library. I'm using LCD with I2C driver from https://github.com/marcoschwartz/LiquidCrystal_I2C.git

## Attribution
- The basic concept for this library is based on the KT Audio VU Meter by ThomAce (https://create.arduino.cc/projecthub/ThomAce/ktaudio-vu-meter-1402b1).
- Liquid Crystal Display with I2C backpack library (https://github.com/marcoschwartz/LiquidCrystal_I2C.git)

## References
- http://www.sengpielaudio.com/calculator-db.htm for dBu formula
- https://www.arduino.cc/en/Reference/MathHeader for math header and calculation functions
- https://create.arduino.cc/projecthub/damar/lcd-vu-meter-for-audio-signal-0cef6d for project schematic and hardware components

## History
- v1.1.0 Adding support for 20x4 LCD with I2C backpack (DFRobot I2C 20x2 LCD Display)
- v1.0.0 First release, only support 16x2 LCD
