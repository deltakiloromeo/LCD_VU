#ifndef DUMMY_H
#define DUMMY_H

#ifdef CODECOV
#include <stdio.h>
#include <math.h>
#include <string>
#include <stddef.h>

#define A3 3
#define A2 2
#define EXTERNAL -1
#define INPUT 0

using namespace std;
typedef u_int8_t uint8_t;
typedef uint8_t byte;
typedef string String;

char Bar[8] = {
    0x11111,
    0x00000,
    0x11111,
    0x11111,
    0x11111,
    0x11111,
    0x00000,
    0x11111
};

char L[8] = {
    0x00111,
    0x01000,
    0x10100,
    0x10100,
    0x10100,
    0x10111,
    0x01000,
    0x00111
};

char R[8] = {
    0x00111,
    0x01000,
    0x10110,
    0x10101,
    0x10110,
    0x10101,
    0x01000,
    0x00111
};

char EndMark[8] = {
    0x10000,
    0x01000,
    0x00100,
    0x00100,
    0x00100,
    0x00100,
    0x01000,
    0x10000
};

char EmptyBar[8] = {
    0x1111,
    0x00000,
    0x00000,
    0x00000,
    0x00000,
    0x00000,
    0x00000,
    0x11111
};

char peakHoldChar[8] = {
    0x11111,
    0x00000,
    0x01110,
    0x01110,
    0x01110,
    0x01110,
    0x00000,
    0x11111
};

class LiquidCrystal_I2C {
    public:
        LiquidCrystal_I2C(uint8_t address, uint8_t col, uint8_t row);
        void init();
        void backlight();
        void createChar(uint8_t location, const char* charmap);
        void setCursor(uint8_t col, uint8_t row);
        size_t write(uint8_t c);
        size_t print(const String& str);
        size_t print(int n);
        void clear();       
};

class DummySerial {
    public:
        DummySerial();
        size_t print(const char * str);
        size_t print(int n);
        size_t println(const char * str);
        size_t println(int n);
        void begin(unsigned long baud);
};

DummySerial Serial;
long millis();
void analogReference(uint8_t mode);
void pinMode(uint8_t pin, uint8_t mode);
int analogRead(uint8_t pin);
void delay(unsigned long ms);
#endif

#endif