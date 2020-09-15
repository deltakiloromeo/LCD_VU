#include "dummy.h"

#ifdef CODECOV
LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t address, uint8_t col, uint8_t row) { 
    printf("Instantiate LiquidCrystal_I2C(%0x, %u, %u\n", address, col, row);
}

void LiquidCrystal_I2C::init() {
    printf("LiquidCrystal_I2C.init()\n");
}

void LiquidCrystal_I2C::backlight() {
    printf("LiquidCrystal_I2C.backlight()\n");
}

void LiquidCrystal_I2C::createChar(uint8_t location, const char* charmap) {
    printf("LiquidCrystal_I2C.createChar(%u, %s\n", location, charmap);
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row) {
    printf("LiquidCrystal_I2C.setCursor(%u, %u)\n", col, row);
}

size_t LiquidCrystal_I2C::write(uint8_t c) {
    printf("%u\n", c);
    return sizeof c;
}

size_t LiquidCrystal_I2C::print(const String& str) {
    printf("%s\n", str);
    return sizeof str;
}
size_t LiquidCrystal_I2C::print(int n) {
    printf("%d\n", n);
    return n;
}

void LiquidCrystal_I2C::clear() {}

DummySerial::DummySerial() { printf("Instantiate DummySerial\n"); }

size_t DummySerial::print(const char * str) {
    printf("%s\n", str);
    return sizeof str;
}

size_t DummySerial::print(int n) {
    printf("%d\n", n);
    return sizeof n;
} 

void DummySerial::begin(unsigned long baud) {
    printf("DummySerial.begin(%lu\n", baud);
}

size_t DummySerial::println(const char * str) {
    return print(str);
}

size_t DummySerial::println(int n) { 
    return print(n);
}

long millis() {
    long ret = 2000;
    printf("millis() returns %l\n", ret);
    return ret;
}

void analogReference(uint8_t mode) {
    printf("analogReference()\n");
}

void pinMode(uint8_t pin, uint8_t mode) {
    printf("pinMode(%u, %u\n", pin, mode);
}

int analogRead(uint8_t pin) {
    int ret = 950;
    printf("analogRead(%u) returns %d\n", pin, ret);
    return ret;
}

void delay(unsigned long ms) {
    printf("delay(%lu\n", ms);
}
#endif