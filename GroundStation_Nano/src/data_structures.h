#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <Arduino.h>

struct DataAccelerometer
{
    double pitch_value;
    double roll_value;
    double yaw_value;
};

struct DataBarometer 
{
    double temperature_value;
    double pressure_value;
    double altitude_value;
};

struct DataJoystick
{
    double axis_1_value;
    double axis_2_value;
    double axis_3_value;
    double axis_4_value;
};

struct DataBus
{
    double pitch_value;
    double roll_value;
    double yaw_value;
    double temperature_value;
    double pressure_value;
    double altitude_value;
};

#endif