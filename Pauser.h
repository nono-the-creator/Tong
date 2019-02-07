#pragma once
#include <iostream>
#include "EventHandler.h"
#include "KeyboardManager.h"
class Pauser : public EventHandler {
private:
	std::string kbChars;
	bool toPause;
	bool toEnter;

public:
	Pauser(std::string kbChars) {
		this->kbChars = kbChars;
		this->toPause = false;
		this->toEnter = false;
	}
	void handleKey(char ch) override {
		if (ch == KeyboardManager::ESC) {
			this->toPause = true;
		}
		if (ch == KeyboardManager::ENTER_BUTTON) {
			this->toEnter = true;
		}
	}
	std::string getKbChars() override {
		return this->kbChars;
	}
	bool isToPause() const {
		return this->toPause;
	}
	void setToPause(bool toPause) {
		this->toPause = toPause;
	}
	bool isToEnter() const {
		return this->toEnter;
	}
};