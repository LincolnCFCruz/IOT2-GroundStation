#include <Arduino.h>
#include <SPI.h>

#include <hid.h>
#include <usbhub.h>
#include <hiduniversal.h>

#include "joystick/joystick.h"
#include "radio/radio.h"

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

Radio comp_1;

int X;
int Y;
int T;

void setup() 
{
    Serial.begin(9600);

    comp_1.radio_setup();

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    delay( 200 );

    if (!Hid.SetReportParser(0, &Joy))
        ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1 );
}

void loop() 
{   
    Usb.Task();

    comp_1.dataToSend[0] = Joy.data_joystick.x_axle;
    comp_1.dataToSend[1] = Joy.data_joystick.y_axle;
    comp_1.dataToSend[2] = Joy.data_joystick.z_axle;
    comp_1.dataToSend[3] = Joy.data_joystick.t_axle;

    comp_1.radio_update();
}