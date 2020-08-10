# LCD_VU
This is a library for displaying audio level using LCD. In this library, LCD that is being used is 16x2 which is controlled using LiquidCrystal_I2C library. The VU display is using 14 bars to dispay audio level segment displayed in dBu, the default audio level range are between -25 to 2 dBu.
As this is only intended for a simple display unit, and not for measurement unit, the result may be less acurrate compared to a professional measurement tool. 

Atrribute
-
The basic concept for this library is based on the KT Audio VU Meter by ThomAce (https://create.arduino.cc/projecthub/ThomAce/ktaudio-vu-meter-1402b1).

References
-
- http://www.sengpielaudio.com/calculator-db.htm for dBu formula
- https://www.arduino.cc/en/Reference/MathHeader for math header and calculation functions
- https://create.arduino.cc/projecthub/damar/lcd-vu-meter-for-audio-signal-0cef6d for project schematic and hardware components
