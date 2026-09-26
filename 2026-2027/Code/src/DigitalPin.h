#include <stdint.h>
#include "CrcLib.h"

class DigitalPin {
	private:
		uint8_t _pin;
	public:
		// mode: INPUT | OUTPUT
		DigitalPin(uint8_t pin, unsigned char mode) : _pin(pin) {
			CrcLib::SetDigitalPinMode(pin, mode);
		};
		// return HIGH | LOW
		unsigned char get() {
			return CrcLib::GetDigitalInput(_pin);
		}
		// state: HIGH | LOW
		void set(unsigned char state) {
			CrcLib::SetDigitalOutput(_pin, state);
		}
};


