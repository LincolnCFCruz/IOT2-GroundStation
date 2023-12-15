#include "joystick.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) : joyEvents(evt)
{
	
}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
	}
	// Calling Game Pad event handler
	if (!match && joyEvents) {
		data_joystick = joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

DataJoystick JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
	DataJoystick event_data;

	uint16_t myX = evt->x;
	uint16_t myY = evt->y;
	uint16_t myZ = evt->twist;
	uint16_t myT = evt->slider;

	int angle1 = map(myX, 0, 1023, 0, 180);
	int angle2 = map(myY, 0, 1023, 0, 180);
	int angle3 = map(myZ, 0, 1023, 0, 180);
	int angle4 = map(myT, 0, 1023, 0, 180);

	event_data.x_axle = (double)angle1;
	event_data.y_axle = (double)angle2;
	event_data.z_axle = (double)angle3;
	event_data.t_axle = (double)angle4;

	/*
	Serial.print("X: ");
	PrintHex<uint16_t>(evt->x, 0x80);
	Serial.print(" Y: ");
	PrintHex<uint16_t>(evt->y, 0x80);
	Serial.print(" Hat Switch: ");
	PrintHex<uint8_t>(evt->hat, 0x80);
	Serial.print(" Twist: ");
	PrintHex<uint8_t>(evt->twist, 0x80);
	Serial.print(" Slider: ");
	PrintHex<uint8_t>(evt->slider, 0x80);
  	Serial.print(" Buttons A: ");
	PrintHex<uint8_t>(evt->buttons_a, 0x80);
	Serial.print(" Buttons B: ");
	PrintHex<uint8_t>(evt->buttons_b, 0x80);
	Serial.println("");
	*/

	return event_data;
}