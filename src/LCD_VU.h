/*******************************************
 *  This wrapper library for LiquidCrystal_I2C
 *	that also has functionality to measure 
 *	audio signal as VU meter.
 *
 * 	Attribution:
 *  - KTAudio VU Meter by ThomAce 
 * 	(https://create.arduino.cc/projecthub/ThomAce/ktaudio-vu-meter-1402b1)
 *  --------------------------
 *  August 6th, 2020 v0.0.3
 *  - Finished revision for linear VU meter
 *  - Need to find out for logarithmic measurement 
 * 
 *  August 7th, 2020 v0.0.4
 * 	- Uses direct reading at analog pins, 
 * 	  instead of using mux, to eliminate noises
 * 
 * 	August 9th, 2020 v0.0.5
 * 	- Implement logarithmic measurement using dBU
 * 	- dBU range from -25dBU to 2 dBU with 14 segments VU meter 
 * 	  on 16x2 LCD or 18 segments on 20x4 LCD 
 * 
 * 	August 11th, 2020 v1.0.0
 * 	- First release
 * 
 * 	August 17th, 2020 v1.1.0
 * 	- Adding support for 20x4 LCD with LiquidCrystal_I2C
 ******************************************/
#ifndef LCD_VU_H
#define LCD_VU_H

#ifndef CODECOV
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#else
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
using namespace std;
#define uint8_t u_int8_t
#endif

#define VREF		1500 // reference voltage in mV, measured at AREF pin
#define VCENTER		450 // center voltage in mV, measured at voltage divider resistor 100K
#define VOFFSET		315 // offset voltage in mV, reads by analog pins when input is connected to ground
#define	DBLO		-25 // lowest dBu range to be dsplayed in VU meter
#define	DBHI		2 // highest dBu range to be displayed in VU meter

class LCD_VU {
	private:
		char blank = (char)260;
		char fill = (char)262;

		int left, right;                        //Variables to store and calculate the channel levels             
		const byte numReadings = 5;              //Refresh rate. Lower value = higher rate. 5 is the defaul
		short indexL = 0;                         //Actual channel index
		double totalL = 0;                         //Total channel data
		int maxL = 0;                           //Maximal level
		short indexR = 0;                         
		double totalR = 0;                         
		int maxR = 0;
		byte pinLeft;	//Input analog pin for LEFT channel
		byte pinRight;	//Input analog pin for RIGHT channel
		short volL = 0;
		short volR = 0;
		int rightAvg = 0;
		int leftAvg = 0;
		long peakHoldTime = 1500;               //peak hold time in miliseconds
		long peakHold = 0;
		short rightPeak = 0;
		short leftPeak = 0;
		long decayTime = 0;
		long actualMillis = 0;
		uint8_t address;
		uint8_t col; 
		uint8_t row;
		double mvRef;
		double mvCenter;
		double mvOffset;

		#ifndef CODECOV
		LiquidCrystal_I2C *pLCD;
		#endif

		byte Bar[8] = {
			B11111,
			B00000,
			B11111,
			B11111,
			B11111,
			B11111,
			B00000,
			B11111
		};

		byte L[8] = {
			B00111,
			B01000,
			B10100,
			B10100,
			B10100,
			B10111,
			B01000,
			B00111
		};

		byte R[8] = {
			B00111,
			B01000,
			B10110,
			B10101,
			B10110,
			B10101,
			B01000,
			B00111
		};

		byte EndMark[8] = {
			B10000,
			B01000,
			B00100,
			B00100,
			B00100,
			B00100,
			B01000,
			B10000
		};

		byte EmptyBar[8] = {
			B11111,
			B00000,
			B00000,
			B00000,
			B00000,
			B00000,
			B00000,
			B11111
		};

		byte peakHoldChar[8] = {
			B11111,
			B00000,
			B01110,
			B01110,
			B01110,
			B01110,
			B00000,
			B11111
		};

		void drawBar16(short data, short peakData, short row);
		int mapdBuToVU(double dBuLevel);
		double volt(double data); // conversion analog reading to audio voltage in mV
		double dBu(double voltData); // conversion mV to dBu
		void drawBar20(short data, short peakData, short row);

	public:
		LCD_VU(uint8_t address, uint8_t col, uint8_t row, byte audioPinLeft, byte audioPinRight);
		void init();
		void loop();
		void setCursor(uint8_t col, uint8_t row);
		void print(const String& text);
		void clear();
		void setReference(double mvRef = VREF, double mvCenter = VCENTER, double mvOffset = VOFFSET);
		String getVersion();
};

#endif