/*
 * Button.h
 *
 * Created: 17.02.2020 20:44:51
 *  Author: domin
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "GlobalDefs.h"
#include "ExecuteDelay.h"

class Button : public ExecuteDelay {
	
public:
	enum KeyStates {
		WAIT_FOR_PRESS,
		PRESSED,
		TO_HANDLE,
		WAIT_FOR_RELEASE_1,
		WAIT_FOR_RELEASE_2
	};
	
	Button() : ExecuteDelay(5) {}
	void init(volatile uint8_t *pin, uint8_t bit) {
		pin_ = pin;
		bit_ = bit;
	}
	void run();
	uint8_t isPressed();
	uint8_t isRelesed();
	void setHandled();
private:
	KeyStates keyState = WAIT_FOR_PRESS;
	volatile uint8_t *pin_;
	uint8_t bit_;
};

inline void Button::run() {
	
	if(skipThisTime()) return;
		
	uint8_t newKeyCode = (*pin_ & (1 << bit_));
	
	if (keyState == KeyStates::WAIT_FOR_PRESS && newKeyCode == BTN_ACTIVE) {
		keyState = KeyStates::PRESSED;
		return;
	}
	if (keyState == KeyStates::PRESSED) {
		keyState = newKeyCode == BTN_ACTIVE ? KeyStates::TO_HANDLE : KeyStates::WAIT_FOR_PRESS;
	}
	if (keyState == KeyStates::TO_HANDLE) {
		return;
	}
	if (keyState == KeyStates::WAIT_FOR_RELEASE_1 && newKeyCode != BTN_ACTIVE) {
		keyState = KeyStates::WAIT_FOR_RELEASE_2;
		return;
	}
	if (keyState == KeyStates::WAIT_FOR_RELEASE_2 && newKeyCode != BTN_ACTIVE) {
		keyState = KeyStates::WAIT_FOR_PRESS;
	}
}

inline uint8_t Button::isPressed() {
	return (keyState == KeyStates::TO_HANDLE);
}

inline uint8_t Button::isRelesed() {
	return (keyState == KeyStates::WAIT_FOR_PRESS);
}

inline void Button::setHandled() {
	keyState = WAIT_FOR_RELEASE_1;
}


#endif /* BUTTON_H_ */