#include <Arduino.h>
#include <Wire.h>

#include <MPU6050.h>

#include "../data_structures.h"

class Accelerometer {
    public:
        MPU6050 mpu;

        int pitch = 0;
        int roll = 0;
        float yaw = 0;

        void accelerometer_init();
        DataAccelerometer accelerometer_update();
        void accelerometer_settings();
};