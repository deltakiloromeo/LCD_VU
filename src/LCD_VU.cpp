#include "LCD_VU.h"

LCD_VU::LCD_VU(uint8_t address, uint8_t col, uint8_t row, byte audioPinLeft, byte audioPinRight) {
  this->address = address;
  this->col = col;
  this->row = row;
  this->pinLeft = audioPinLeft;
  this->pinRight = audioPinRight;
}

void LCD_VU::init() {
  pLCD = new LiquidCrystal_I2C(address, col, row);

  pLCD->init();
  pLCD->backlight();
  
  decayTime = millis();

  analogReference(EXTERNAL);    // use external voltage reference in pin AREF
  pinMode(pinLeft, INPUT);
  pinMode(pinRight, INPUT);

  mvCenter = VCENTER;
  mvOffset = VOFFSET;
  mvRef = VREF;
}

void LCD_VU::loop()
{    
  double data;

  /*********** Refresh display for basic elements *********/
  pLCD->createChar(1, Bar);
  pLCD->createChar(2, L);
  pLCD->createChar(3, R);
  pLCD->createChar(4, EmptyBar);
  pLCD->createChar(5, EndMark);
  pLCD->createChar(6, peakHoldChar);

  pLCD->setCursor(0, 0);        //L channel index
  pLCD->write(2);               //L symbol 
  pLCD->setCursor(0, 1);        //R channel index
  pLCD->write(3);               //R symbol
  pLCD->setCursor(col-1, 0);    //closing tag / end mark index 1
  pLCD->write(5);               //closing tag / end mark
  pLCD->setCursor(col-1, 1);    //closing tag / end mark index 2
  pLCD->write(5);               //closing tag / end mark

  actualMillis = millis();

  // Data reading on left channel
  data = analogRead(pinLeft);

  #ifdef DEBUG
  Serial.print("Read L: "); Serial.print(data);
  #endif

  data = volt(data);
  totalL = dBu(data);

  #ifdef DEBUG
  Serial.print(" Volt L: "); Serial.print(data); Serial.print("mV ");
  Serial.print("L data: "); Serial.print(totalL); Serial.print("dBu ");
  #endif

  totalL = mapdBuToVU(totalL);
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
  
  // Data reading on right channel
  data = analogRead(pinRight);

  #ifdef DEBUG
  Serial.print("Read R: "); Serial.print(data);
  #endif

  data = volt(data);
  totalR = dBu(data);
  
  #ifdef DEBUG
  Serial.print(" Volt R: "); Serial.print(data); Serial.print("mV ");
  Serial.print(" R data: "); Serial.print(totalR); Serial.print("dBu ");
  #endif
  
  totalR = mapdBuToVU(totalR);
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
    
  volR = right;
  if(volR > (col-2))
  {
    volR = col-2;
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

  if(col == 16)
  {
    drawBar16(volR, rightPeak, 1);
  }
  else
  {
    drawBar20(volR, rightPeak, 1);
  }

  #ifdef DEBUG
  Serial.print(" R: "); Serial.print(volR); Serial.print(", "); Serial.print(rightPeak);
  #endif
  
  volL = left;   
  if(volL > (col-2))
  {
    volL = col-2;
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

  if(col == 16)
  {
    drawBar16(volL, leftPeak, 0);
  }
  else
  {
    drawBar20(volL, leftPeak, 0);
  }
  
  #ifdef DEBUG
  Serial.print(" L: "); Serial.print(volL); Serial.print(", "); Serial.print(leftPeak);
  #endif

  if (decayTime < actualMillis)
    decayTime = (millis() + 50);

  if (peakHold < actualMillis)
  {
    peakHold = (millis() + peakHoldTime);
    rightPeak = -1;
    leftPeak = -1;
  }

  #ifdef DEBUG
  Serial.println();
  #endif
}

void LCD_VU::drawBar16(short data, short peakData, short row)
{
  // Use this line to skip VU meter display, otherwise just remark it
  //return;

  //If the previous peak data is 1 or 0, then not taking care of the value.
  if (peakData < 2)
  {
    peakData = -1;
  }

  pLCD->setCursor(1,row);
  
  if (data == 0)
  {
      char level0[] = {blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level0);
  }

  else if( data == 1)
  {
      char level1[] = {fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level1);
  }
    
  else if( data == 2)
  {
      char level2[] = {fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level2);
  }
    
  else if (data == 3)
  {
      char level3[] = {fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level3);
  }

  else if (data == 4)
  {
      char level4[] = {fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level4);
  }
    
  else if (data == 5)
  {
      char level5[] = {fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level5);
  }

  else if (data == 6)
  {
      char level6[] = {fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level6);
  }

  else if (data == 7)
  {
      char level7[] = {fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level7);
  }

  else if (data == 8)
  {
      char level8[] = {fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level8);
  }
  
  else if (data == 9)
  {
      char level9[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level9);
  }

  else if (data == 10)
  {
      char level10[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, '\0'};
      pLCD->print(level10);
  }

  else if (data == 11)
  {
      char level11[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, '\0'};
      pLCD->print(level11);
  }

  else if (data == 12)
  {
      char level12[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, '\0'};
      pLCD->print(level12);
  }

  else if (data == 13)
  {
      char level13[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, '\0'};
      pLCD->print(level13);
  }

  else if (data == 14)
  {
      char level14[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, '\0'};
      pLCD->print(level14);
  }

  else if (data == 15)
  {
      char level15[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, '\0'};
      pLCD->print(level15);
  }

  if (peakData == data)
  {
      pLCD->setCursor(data,row);
      pLCD->write(6); //write the peak marker
  }
  else if (peakData > 0)
  {
      pLCD->setCursor(peakData,row);
      pLCD->write(6); //write the peak marker
  }
}

void LCD_VU::setCursor(uint8_t col, uint8_t row) {
  pLCD->setCursor(col, row);
}

void LCD_VU::print(const String& text) {
  pLCD->print(text);
}

void LCD_VU::clear() {
  pLCD->clear();
}

String LCD_VU::getVersion() {
  return "LCD_VU v1.1.0";
}


int LCD_VU::mapdBuToVU(double dBuLevel) {
  int retVal = 0;
  int vuRange = DBHI - DBLO;

  if(dBuLevel >= DBLO) {
    retVal = ceil((dBuLevel - DBLO) / vuRange * (col-2));
  }

  return retVal;
}

#ifndef CODECOV
void LCD_VU::setReference(double mvRef = VREF, double mvCenter = VCENTER, double mvOffset = VOFFSET) {
#else
void LCD_VU::setReference(double mvRef, double mvCenter, double mvOffset) {
#endif
  this->mvCenter = mvCenter;
  this->mvOffset = mvOffset;
  this->mvRef = mvRef;
}

double LCD_VU::volt(double data) {
  return fabs((mvRef*data/1024) - mvCenter) - mvOffset;
}

double LCD_VU::dBu(double voltData) {
  return 20*log10(voltData / 774.6);	// conversion mV to dBu
}

void LCD_VU::drawBar20(short data, short peakData, short row)
{
  // Use this line to skip VU meter display, otherwise just remark it
  //return;

  //If the previous peak data is 1 or 0, then not taking care of the value.
  if (peakData < 2)
  {
    peakData = -1;
  }

  pLCD->setCursor(1,row);

  if (data == 0)
  {
      char level0[] = {blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level0);
  }

  else if( data == 1)
  {
      char level1[] = {fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level1);
  }
    
  else if( data == 2)
  {
      char level2[] = {fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level2);
  }
    
  else if (data == 3)
  {
      char level3[] = {fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level3);
  }

  else if (data == 4)
  {
      char level4[] = {fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level4);
  }
    
  else if (data == 5)
  {
      char level5[] = {fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level5);
  }

  else if (data == 6)
  {
      char level6[] = {fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level6);
  }

  else if (data == 7)
  {
      char level7[] = {fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level7);
  }

  else if (data == 8)
  {
      char level8[] = {fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level8);
  }
  
  else if (data == 9)
  {
      char level9[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level9);
  }

  else if (data == 10)
  {
      char level10[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level10);
  }

  else if (data == 11)
  {
      char level11[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level11);
  }

  else if (data == 12)
  {
      char level12[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level12);
  }

  else if (data == 13)
  {
      char level13[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, blank, '\0'};
      pLCD->print(level13);
  }

  else if (data == 14)
  {
      char level14[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, blank, '\0'};
      pLCD->print(level14);
  }

  else if (data == 15)
  {
      char level15[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, blank, '\0'};
      pLCD->print(level15);
  }

  else if (data == 16)
  {
      char level16[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, blank, '\0'};
      pLCD->print(level16);
  }

  else if (data == 17)
  {
      char level17[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, blank, '\0'};
      pLCD->print(level17);
  }

  else if (data == 18)
  {
      char level18[] = {fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, fill, '\0'};
      pLCD->print(level18);
  }

  if (peakData == data)
  {
      pLCD->setCursor(data,row);
      pLCD->write(6); //write the peak marker
  }
  else if (peakData > 0)
  {
      pLCD->setCursor(peakData,row);
      pLCD->write(6); //write the peak marker
  }
}