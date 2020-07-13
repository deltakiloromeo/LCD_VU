#include "LCD_VU.h"

//LCD_VU::LCD_VU(uint8_t address, uint8_t col, uint8_t row, int pinLeftInput, int pinRightInput) : LiquidCrystal_I2C::LiquidCrystal_I2C(address, col, row) {
LCD_VU::LCD_VU(uint8_t address, uint8_t col, uint8_t row) : LiquidCrystal_I2C::LiquidCrystal_I2C(address, col, row) {
}

void LCD_VU::init() {
  LiquidCrystal_I2C::init();
  this->backlight();
    
  this->createChar(1, Bar);
  this->createChar(2, L);
  this->createChar(3, R);
  this->createChar(4, EmptyBar);
  this->createChar(5, EndMark);
  this->createChar(6, peakHoldChar);

  decayTime = millis();

  this->setCursor(0, 0);        //L channel index
  this->write(2);               //L symbol 
  this->setCursor(0, 1);        //R channel index
  this->write(3);               //R symbol
  this->setCursor(15, 0);       //closing tag / end mark index 1
  this->write(5);               //closing tag / end mark
  this->setCursor(15, 1);       //closing tag / end mark index 2
  this->write(5);               //closing tag / end mark

  this->centerLeft = CENTER_LEFT;
  this->centerRight = CENTER_RIGHT;
}

void LCD_VU::loop()
{    
  short data;

  actualMillis = millis();

  //totalL = analogRead(inputPinL) / 4 - 128; //reducing the detected hum and noise
  data = (*pvuLeft-centerLeft);
  if(data < 0)
    totalL = -data;
  else
    totalL = data;// / 4 - 128; //reducing the detected hum and noise
  Serial.print("L data: "); Serial.print(*pvuLeft);
    
  if(totalL > maxL)
  {
    maxL = totalL;
  }
   
  indexL++;
   
  if (indexL >= numReadings)
  {             
    indexL = 0;                         
    left = maxL;
    maxL = 0;
  }   
  
  data = (*pvuRight-centerRight);
  if(data < 0)
    totalR = -data;
  else
    totalR = data;

  //totalR = analogRead(inputPinR) / 4 - 128; //reducing the detected hum and noise
  //totalR = (*pvuRight-CENTER_RIGHT);// / 4 - 128; //reducing the detected hum and noise
  Serial.print(" R data: "); Serial.print(*pvuRight);
    
  if(totalR > maxR)
  {
    maxR = totalR;
  }
   
  indexR++;
   
  if (indexR >= numReadings)
  {             
    indexR = 0;                         
    right = maxR;
    maxR = 0;
  } 
    
  volR = right / 3;
    
  if(volR > 14)
  {
    volR = 14;
  }

  if (volR < (rightAvg - 2))
  {
    if (decayTime < actualMillis)
      rightAvg--;
      
    volR = rightAvg;
  }    
  else if (volR > (rightAvg + 2))
  {
    volR = (rightAvg + 2);
    rightAvg = volR;
  }
  else
  {
    rightAvg = volR;
  }

  if (volR > rightPeak)
  {
    rightPeak = volR;    
  }

  drawBar(volR, rightPeak, 1);
  Serial.print(" R: "); Serial.print(volR); Serial.print(", "); Serial.print(rightPeak);

  volL = left / 3;
   
  if(volL > 14)
  {
    volL = 14;
  }

  if (volL < (leftAvg - 2))
  {
    if (decayTime < actualMillis)
      leftAvg--;   
         
    volL = leftAvg;
  }
  else if (volL > (leftAvg + 2))
  {
    volL = (leftAvg + 2);
    leftAvg = volL;
  }
  else
  {
    leftAvg = volL;
  }

  if (volL > leftPeak)
  {
    leftPeak = volL;
  }

  drawBar(volL, leftPeak, 0);
  Serial.print(" L: "); Serial.print(volL); Serial.print(", "); Serial.print(leftPeak);

  if (decayTime < actualMillis)
    decayTime = (millis() + 50);

  if (peakHold < actualMillis)
  {
    peakHold = (millis() + peakHoldTime);
    rightPeak = -1;
    leftPeak = -1;
  }

  Serial.println();
}

void LCD_VU::drawBar(int data, int peakData, int row)
{
  //If the previous peak data is 1 or 0, then not taking care of the value.
  if (peakData < 2)
  {
    peakData = -1;
  }

  this->setCursor(1,row);
  if (data == 0)
  {
      char level0[] = {blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level0);
  }

  else if( data == 1)
  {
      char level1[] = {fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level1);
  }
    
  else if( data == 2)
  {
      char level2[] = {fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level2);
  }
    
  else if (data == 3)
  {
      char level3[] = {fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level3);
  }

  else if (data == 4)
  {
      char level4[] = {fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level4);
  }
    
  else if (data == 5)
  {
      char level5[] = {fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level5);
  }

  else if (data == 6)
  {
      char level6[] = {fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level6);
  }

  else if (data == 7)
  {
      char level7[] = {fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level7);
  }

  else if (data == 8)
  {
      char level8[] = {fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, '\0'};
      this->print(level8);
  }
  
  else if (data == 9)
  {
      char level9[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, '\0'};
      this->print(level9);
  }

  else if (data == 10)
  {
      char level10[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, '\0'};
      this->print(level10);
  }

  else if (data == 11)
  {
      char level11[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, '\0'};
      this->print(level11);
  }

  else if (data == 12)
  {
      char level12[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, '\0'};
      this->print(level12);
  }

  else if (data == 13)
  {
      char level13[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, '\0'};
      this->print(level13);
  }

  else if (data == 14)
  {
      char level14[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, '\0'};
      this->print(level14);
  }

  else if (data == 15)
  {
      char level15[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, '\0'};
      this->print(level15);
  }


  if (peakData == data)
  {
      this->setCursor(data,row);
      this->write(6); //write the peak marker
  }
  else if (peakData > 0)
  {
      this->setCursor(peakData,row);
      this->write(6); //write the peak marker
  }
}

void LCD_VU::setCursor(uint8_t col, uint8_t row) {
  LiquidCrystal_I2C::setCursor(col, row);
}
size_t LCD_VU::print(const String& text) {
  LiquidCrystal_I2C::print(text);
}
void LCD_VU::clear() {
  LiquidCrystal_I2C::clear();
}

void LCD_VU::setPointers(short *pvuLeftData, short *pvuRightData) {
    this->pvuLeft = pvuLeftData;
    this->pvuRight = pvuRightData;
}

String LCD_VU::getVersion() {
    return "LCD_VU v0.02";
}

void LCD_VU::setReferences(short refLeft = CENTER_LEFT, short refRight = CENTER_RIGHT) {
    this->centerLeft = refLeft;
    this->centerRight = refRight;
    setCursor(0,0);
    print("refLeft: "); print(String(centerLeft));
    setCursor(0,1);
    print("refRight: "); print(String(centerRight));
    delay(2000);
}