#ifndef DUMMY_H
#define DUMMY_H

#ifdef CODECOV

#include <stdio.h>
#include <math.h>
#include <string>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define A3 3
#define A2 2
#define EXTERNAL -1
#define INPUT 0

using namespace std;
typedef u_int8_t uint8_t;
typedef uint8_t byte;
typedef string String;

extern char Bar[];
extern char L[];
extern char R[];
extern char EndMark[];
extern char EmptyBar[];
extern char peakHoldChar[];
extern time_t startTime;

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
        size_t println();
        void begin(unsigned long baud);
};

extern DummySerial Serial;

extern long millis();
extern void analogReference(uint8_t mode);
extern void pinMode(uint8_t pin, uint8_t mode);
extern int analogRead(uint8_t pin);
extern void delay(unsigned long ms);
extern void setup();
extern void loop();

#endif // CODECOV

#endif // DUMMY_H