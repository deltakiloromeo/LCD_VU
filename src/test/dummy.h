#ifndef DUMMY_H
#define DUMMY_H

#ifdef CODECOV
#include <stdio.h>
#include <math.h>
#include <string>
#include <stddef.h>

#define A3 3
#define A2 2

using namespace std;
typedef u_int8_t uint8_t;
typedef uint8_t byte;
typedef string String;

class LiquidCrystal_I2C {
    public:
        LiquidCrystal_I2C(uint8_t address, uint8_t col, uint8_t row);
        void init();
        void backlight();
        void createChar(uint8_t location, const char* charmap);
        void setCursor(uint8_t col, uint8_t row);
        size_t write(uint8_t c);        
};

class Serial {
    public:
        static size_t print(const char * str);
        static size_t print(int n);
        static void begin(unsigned long baud);
    
    private:
        Serial();
};

long millis();
void analogReference(uint8_t mode);
void pinMode(uint8_t pin, uint8_t mode);
int analogRead(uint8_t pin);
void delay(unsigned long ms);
#endif

#endif