/*******************************************
 *  This wrapper library for LiquidCrystal_I2C
 *	that also has functionality to measure 
 *	audio signal as VU meter.
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
 ******************************************/
#ifndef LCD_VU_H
#define LCD_VU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define MAX_VU		14 // number of VU segment
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

		LiquidCrystal_I2C *pLCD;

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

		void drawBar(short data, short peakData, short row);
		int mapdBuToVU(double dBuLevel);
		double volt(double data); // conversion analog reading to audio voltage in mV
		double dBu(double voltData); // conversion mV to dBu

	public:
		LCD_VU(uint8_t address, uint8_t col, uint8_t row, byte audioPinLef, byte audioPinRight);
		void init();
		void loop();
		void setCursor(uint8_t col, uint8_t row);
		void print(const String& text);
		void clear();
		void setReference(double mvRef, double mvCenter, double mvOffset);
		String getVersion();
};

#endif