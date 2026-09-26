#include <Arduino.h>
#include "CrcLib.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
	CrcLib::Initialize();
};

void loop() {
	CrcLib::Update();
  
	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);

	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);

	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);
	uint8_t _x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);

	bool _x = CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::ARROW_LEFT);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::ARROW_RIGHT);

	bool _x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
	
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::HATL);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::HATR);
	
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::L1);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::R1);

	bool _x = CrcLib::ReadDigitalChannel(BUTTON::SELECT);
	bool _x = CrcLib::ReadDigitalChannel(BUTTON::START);

	bool _x = CrcLib::ReadDigitalChannel(BUTTON::LOGO);
};