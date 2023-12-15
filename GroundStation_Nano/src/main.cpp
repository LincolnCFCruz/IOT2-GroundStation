#include <Arduino.h>
#include <Wire.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "radio/radio.h"
#include "barometer/barometer.h"
#include "accelerometer/accelerometer.h"

#include "data_structures.h"

#define I2C_ADDRESS 0x3C

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 4

const int leftButtonPin = 2;
const int rightButtonPin = 3;

int leftButtonState = 0;
int rightButtonState = 0;

int currentScreen = 1;

Radio comp_1;
Barometer comp_2;
Accelerometer comp_3;

SSD1306AsciiWire comp_4;

DataBarometer comp_2_data;
DataAccelerometer comp_3_data;

DataBus data_buffer;

void changeScreen(int direction) {
  currentScreen += direction;

  if (currentScreen < 1) 
  {
    currentScreen = 1;
  } 
  else if (currentScreen > 3) 
  {
    currentScreen = 3;
  }
}

void updateScreen()
{
  comp_4.clear();
  
  if (currentScreen == 1)
  {
    comp_4.println("Baro Data");
    comp_4.println("------------------");
    comp_4.print("Altitude: ");
    comp_4.println(comp_2_data.altitude_value);
    comp_4.print("Pressure: ");
    comp_4.println(comp_2_data.pressure_value);
    comp_4.print("Temperature: ");
    comp_4.println(comp_2_data.temperature_value);
    comp_4.println("------------------");
  }
  else if (currentScreen == 2)
  {
    comp_4.println("Accelerometer Data");
    comp_4.println("------------------");
    comp_4.print("Pitch: ");
    comp_4.println(comp_3_data.pitch_value);
    comp_4.print("Roll: ");
    comp_4.println(comp_3_data.roll_value);
    comp_4.print("Yaw: ");
    comp_4.println(comp_3_data.yaw_value);
    comp_4.println("------------------");
  }
  else if (currentScreen == 3)
  {
    comp_4.println("Flight Control Data");
    comp_4.println("------------------");
    comp_4.print("Axis 1: ");
    comp_4.println(comp_1.data_joystick.axis_1_value);
    comp_4.print("Axis 2: ");
    comp_4.println(comp_1.data_joystick.axis_2_value);
    comp_4.print("Axis 3: ");
    comp_4.println(comp_1.data_joystick.axis_3_value);
    comp_4.print("Axis 4: ");
    comp_4.println(comp_1.data_joystick.axis_4_value);
    comp_4.println("------------------");
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  comp_4.begin(&Adafruit128x64, I2C_ADDRESS);

  comp_4.setFont(Adafruit5x7);

  comp_4.clear();
  comp_4.println("Ground Station");
  comp_4.println("Loading data...");

  comp_1.radio_setup();
  comp_2.barometer_init();
  comp_3.accelerometer_init();

  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
}

void loop() 
{
  leftButtonState = digitalRead(BUTTON_PIN_1);
  rightButtonState = digitalRead(BUTTON_PIN_2);

  if (leftButtonState == HIGH) {
    // Left button is pressed, change the screen to the left
    changeScreen(-1);
    delay(50); // Debouncing delay
  }

  if (rightButtonState == HIGH) {
    // Right button is pressed, change the screen to the right
    changeScreen(1);
    delay(50); // Debouncing delay
  }

  updateScreen();

  comp_2_data = comp_2.barometer_update();
  comp_3_data = comp_3.accelerometer_update();

  data_buffer.altitude_value = comp_2_data.altitude_value;
  data_buffer.pressure_value = comp_2_data.pressure_value;
  data_buffer.temperature_value = comp_2_data.temperature_value;

  data_buffer.pitch_value = comp_3_data.pitch_value;
  data_buffer.roll_value = comp_3_data.roll_value;
  data_buffer.yaw_value = comp_3_data.yaw_value;

  comp_1.radio_update(data_buffer);
}