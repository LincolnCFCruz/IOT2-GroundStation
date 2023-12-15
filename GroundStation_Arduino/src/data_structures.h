#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <Arduino.h>

struct GamePadEventData
{
  union { //axes and hut switch
    uint32_t axes;
    struct {
      uint32_t x : 10;
      uint32_t y : 10;
      uint32_t hat : 4;
      uint32_t twist : 8;      
    };
  };
  uint8_t buttons_a;
  uint8_t slider;
  uint8_t buttons_b;
};

struct DataJoystick
{
    double x_axle = 9999999.0;
    double y_axle = 9999999.0;
    double z_axle = 9999999.0;
    double t_axle = 9999999.0;
};

#endif