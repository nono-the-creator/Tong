#pragma once


#include <list>
#include "Pedal.h"
#include "Ball.h"

class KeyboardManager {
	enum { NUM_CHARS = 32 };
	// an array of 'char' => list of kbListener
	std::list<EventHandler*> kbListeners[NUM_CHARS];

	// helper method - get index in array per a given char
	int getIndex(char c) {
		switch (c) {
		case ESC:
			return 26;
			break;
		case UP_BUTTON:
			return 27;
			break;
		case DOWN_BUTTON:
			return 28;
			break;
		case LEFT_BUTTON:
			return 29;
			break;
		case RIGHT_BUTTON:
			return 30;
			break;
		case ENTER_BUTTON:
			return 31;
			break;
		}
		c = towlower(c);
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS) {
			return -1;
		}
		return index;
	}
public:
	enum Asciis {
		ESC = 27, UP_BUTTON = 72, DOWN_BUTTON = 80, ENTER_BUTTON = 13,
		LEFT_BUTTON = 75, RIGHT_BUTTON = 77
	};
	void registerKbListener(EventHandler* pKbListener);
	void handleKeyboard();
};
