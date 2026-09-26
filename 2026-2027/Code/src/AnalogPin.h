#include <stdint.h>
#include "CrcLib.h"

class AnalogPin {
	private:
		uint8_t _pin;
	public:
		// mode: INPUT | OUTPUT
		AnalogPin(uint8_t pin, unsigned char mode) : _pin(pin) {
			CrcLib::SetDigitalPinMode(pin, mode);
		};
		// value: 0..=255
		void set(unsigned char value) {
			CrcLib::SetPwmOutput(_pin, value);
		}
};