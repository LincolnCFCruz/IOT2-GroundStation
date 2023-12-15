#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>

#include "../data_structures.h"

#define BMP180_ADDR 0x77 // 7-bit address
#define BMP180_REG_CONTROL 0xF4
#define BMP180_REG_RESULT 0xF6
#define BMP180_COMMAND_TEMPERATURE 0x2E
#define BMP180_COMMAND_PRESSURE 0x34 //0x34 0x74 0xB4 0xF4

class Barometer {
    public:
        uint16_t unSignedIntTempVar,AC4,AC5,AC6;
        int16_t signedIntTempVar,AC1,AC2,AC3,VB1,VB2,MB,MC,MD;

        double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
        char _error;
        
        float temperature;
        float pressure;
        float altitude;

        void barometer_init();

        DataBarometer barometer_update();

        char barometer_settings();

        char readCompData(char address);
        char writeBytes(unsigned char *values, char length);
        char measureParameters(double &P, double &T);
        double calculateTemperature(double ut);
        double calculatePressure(double up,double T);
};