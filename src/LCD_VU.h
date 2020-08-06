/*******************************************
 *  This wrapper library for LiquidCrystal_I2C
 *	that also has functionality to measure 
 *	audio signal as VU meter.
 *  --------------------------
 *  August 6th, 2020 v0.0.3
 *  - Finished revision for linear VU meter
 *  - Need to find out for logarithmic measurement 
 ******************************************/
#ifndef LCD_VU_H
#define LCD_VU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define CENTER_LEFT		512 //814 //630
#define CENTER_RIGHT	679	//814 //773
#define MAX_VU			14
#define QUANTIZE		4
#define NOISE_OFFSET	0 // 128

class LCD_VU {// : LiquidCrystal_I2C {
	private:
		char blank = (char)260;
		char fill = (char)262;

		int left, right;                        //Variables to store and calculate the channel levels             
		const byte numReadings = 0;              //Refresh rate. Lower value = higher rate. 5 is the defaul
		short indexL = 0;                         //Actual channel index
		int totalL = 0;                         //Total channel data
		int maxL = 0;                           //Maximal level
		short indexR = 0;                         
		int totalR = 0;                         
		int maxR = 0;
		//int inputPinL;                     //Input pin Analog 1 for LEFT channel
		//int inputPinR;                     //Input pin Analog 0 for RIGHT channel
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
		int *pvuLeft;
		int *pvuRight;
		int centerLeft;
		int centerRight;
		uint8_t address;
		uint8_t col; 
		uint8_t row;

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
		
	public:
		LCD_VU(uint8_t address, uint8_t col, uint8_t row);
		void init();
		void loop();
		void setCursor(uint8_t col, uint8_t row);
		void print(const String& text);
		void clear();
		void setPointers(int *pvuLeftData, int *pvuRightData);
		String getVersion();
		void setReferences(int refLeft, int refRight);
};

#endif