#include <iostream>
#include "Game.h"
#include "utils.h"
#include "MainMenu.h"

int main() {
	sndPlaySound("BG_Music.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
 	MainMenu menu;
	KeyboardManager kbManager;
	menu.printButtons();
	setCursorOff();
	kbManager.registerKbListener(&menu);
	while (true) {
		kbManager.handleKeyboard();
	}
}