#include <conio.h>
#include "KeyboardManager.h"
#include "Ball.h"

// registers a listener to the list 
void KeyboardManager::registerKbListener(EventHandler* newKbListener) {
	std::string chars = newKbListener->getKbChars();
	int charsToRegister = chars.length();
	for (int i = 0; i < charsToRegister; ++i) {
		int index = getIndex(chars[i]);
		if (index != -1) {
			kbListeners[index].push_back(newKbListener);
		}
	}
}
// envokes the handler
void KeyboardManager::handleKeyboard() {
	if (_kbhit()) {
		char ch = (_getch());
		if(ch != ESC && ch != UP_BUTTON && ch !=  DOWN_BUTTON && ch != ENTER_BUTTON
			&& ch != LEFT_BUTTON&& ch != RIGHT_BUTTON){ 
		ch = tolower(ch);
		}
		int index = getIndex(ch); 
		if (index != -1) {
			for (EventHandler* KbListener : kbListeners[index]) {
				KbListener->handleKey(ch);
			}
		}
	}
}
