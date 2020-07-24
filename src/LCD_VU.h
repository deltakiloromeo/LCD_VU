#ifndef LCD_VU_H
#define LCD_VU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define CENTER_LEFT		549 //630
#define CENTER_RIGHT	743 //773

class LCD_VU : LiquidCrystal_I2C {
	private:
		char blank = (char)260;
		char fill = (char)262;

		int left, right;                        //Variables to store and calculate the channel levels             
		const int numReadings = 0;              //Refresh rate. Lower value = higher rate. 5 is the defaul
		int indexL = 0;                         //Actual channel index
		int totalL = 0;                         //Total channel data
		int maxL = 0;                           //Maximal level
		int indexR = 0;                         
		int totalR = 0;                         
		int maxR = 0;
		//int inputPinL;                     //Input pin Analog 1 for LEFT channel
		//int inputPinR;                     //Input pin Analog 0 for RIGHT channel
		int volL = 0;
		int volR = 0;
		int rightAvg = 0;
		int leftAvg = 0;
		long peakHoldTime = 1500;               //peak hold time in miliseconds
		long peakHold = 0;
		int rightPeak = 0;
		int leftPeak = 0;
		long decayTime = 0;
		long actualMillis = 0;
		short *pvuLeft;
		short *pvuRight;
		short centerLeft;
		short centerRight;

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

		void drawBar(int data, int peakData, int row);
		
	public:
		//LCD_VU(uint8_t address, uint8_t col, uint8_t row, int pinLeftInput, int pinRightInput);
		LCD_VU(uint8_t address, uint8_t col, uint8_t row);
		void init();
		void loop();
		void setCursor(uint8_t col, uint8_t row);
		size_t print(const String& text);
		void clear();
		void setPointers(short *pvuLeftData, short *pvuRightData);
		String getVersion();
		void setReferences(short refLeft, short refRight);
};

#endif