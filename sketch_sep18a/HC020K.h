#pragma once
#include "Arduino.h"

/**
 *	For use by Rutgers IEEE
 *
 *	This class is used with the HC020K Encoder module.
 *	
 *	It is initialized with the pin the encoder is plugged into
 *	You also need to initialize it with a 'counter' function
 *	Just wrap around the existing countTicks() function and 
 *		pass that on in the init method. Something like:
 *			void counter() {
 *				enc.countTicks();
 * 			}
 *			...
 *			enc.init(&counter);
 *
 *	setDirection changes whether each tick adds or subtracts from 
 *		the current value.
 *	getTicks() returns the number of ticks that have been counted, 
 *	and resetTicks() allows the user to 'reset' the count to 0.
 *
 *	Note: the data pin MUST be connected to an interrupt port.
 */

class HC020K {

	private: 
		int ticks;
		int pin;
		bool forward = FORWARD;

	public:
		HC020K(int dataPin);
		const static bool FORWARD = true;
		const static bool BACKWARD = false;
		// Sets up pins as output pins, call this in setup
		void init(void (*handler)());
		void countTicks();
		void setDirection(bool forw);
		int getTicks();
		void resetTicks();

};

/**	
 *	09/17/17 - Rupesh Chinta: Created Library
 */