/***************************************************
 * This is an example on using LCD_VU.
 * This example has been created using Arduino Uno 
 * 
 * You will need LiquidCrystal_I2C library in your system
 * 
 * Aug 10th, 2020
 * *************************************************/

#include <LCD_VU.h>

/****************** Definition for audio input pins *******************/
#define pinAudioLeft    A3
#define pinAudioRight   A2

/******************* LCD declaration **********************
 * 1st argument: address of LCD with I2C backpack, this address may vary between LCD device
 * 2nd argument: number of columns
 * 3rd argument: number of rows
 * 4th argument: analog pin for audio input left channel
 * 5th argument: analog pin for audio input right channel
 * ********************************************************/
LCD_VU lcd (0x27, 16, 2, pinAudioLeft, pinAudioRight);

void setup() {
    // Activate Serial if you want to debug or calibrate
    Serial.begin(9600);

    // You need to call this method to initialize LCD_VU
    lcd.init();
    
    /****** The introduction block ******/
    lcd.setCursor(0,0);
    lcd.print("* dBu VU meter *");

    lcd.setCursor(0,1);
    lcd.print("--");
    lcd.print(lcd.getVersion());
    lcd.print("--");

    delay(2000);
    lcd.clear();
    /****** End of The introduction block ******/

    /**** call this method to calibrate the VU meter ****
    * No need to call this method if with using standard values,
    * display has been displayed properly.
    * Default value are (as measured in my test environment)
    * - vRef = 1500mV
    * - vCenter = 450mV
    * - vOffset = 315mV
    * 
    * The values below are only for an example, you need to
    * do measurement using voltmeter on the points mentioned below 
    * to get better accuracy. 
    * 
    * 1st argument: reference voltage (in millivolt/mV) at pin AREF
    * 2nd argument: center voltage at voltage divider (in mV)
    * 3rd argument: offset voltage, check voltage at Serial printout 
    *               when audio input is connected to ground. Use 
    *               absolute value only (remove negative sign).
    *               You need to activate Serial for this purpose. 
    * ***************************************************/
    // Unremark the following codes if you need it
    
    // use this if necessary, values are only for sample
    //lcd.setReference(1800, 800, 200); 
    
    // or if you need only to set offset value, and keep the rest the same
    //lcd.setReference(VREF, VCENTER, 200);
}

void loop() {
    // call this method to refresh data readings and display VU meter
    lcd.loop();
}