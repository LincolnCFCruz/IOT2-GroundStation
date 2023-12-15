#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <usbhid.h>

#include "../data_structures.h"

#define RPT_GAMEPAD_LEN	sizeof(GamePadEventData)/sizeof(uint8_t)

//------------------------------------------------------------------

class JoystickEvents
{
public:
	virtual DataJoystick OnGamePadChanged(const GamePadEventData *evt);
};

//------------------------------------------------------------------

class JoystickReportParser : public HIDReportParser
{
	JoystickEvents		*joyEvents;

  uint8_t oldPad[RPT_GAMEPAD_LEN];

public:
  DataJoystick data_joystick;

	JoystickReportParser(JoystickEvents *evt);

	virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__