#include "dummy.h"

#ifdef CODECOV
LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t address, uint8_t col, uint8_t row) {}
void LiquidCrystal_I2C::init() {}
void LiquidCrystal_I2C::backlight() {}
void LiquidCrystal_I2C::createChar(uint8_t location, const char* charmap) {}
void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row) {}
size_t LiquidCrystal_I2C::write(uint8_t c) {return sizeof c;}
size_t LiquidCrystal_I2C::print(const char * str) {return sizeof str;}
size_t LiquidCrystal_I2C::print(int n) {return n;} 

Serial::Serial() {}
static size_t Serial::print(const char * str) {return sizeof str;}
static size_t Serial::print(int n) {return n;} 
static void Seriall::begin(unsigned long baud);

long millis() {return 2000;}
void analogReference(uint8_t mode) {}
void pinMode(uint8_t pin, uint8_t mode) {}
int analogRead(uint8_t pin) {return 950;}
void delay(unsigned long ms) {}
#endif