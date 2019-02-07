#pragma once
#include "Pedal.h"
#include "EventHandler.h"
class HumanPedal : public Pedal, public EventHandler {
private:
	std::string kbChars;//keyboard bottons that interacts with the pedals.
	char nextMovementY;
	bool isMenuPedal;
public:
	HumanPedal(const Position& upperPosition, std::string kbChars, bool isMenuPedal = false) : 
												Pedal(upperPosition), kbChars(kbChars) {
		this->isMenuPedal = isMenuPedal;
	}
	std::string getKbChars() override {
		return this->kbChars;
	}
	void handleKey(char ch) override {
		nextMovementY = ch;
	}
	void movemenHandler() override {
		if (!this->isMenuPedal) {
			if (nextMovementY == kbChars[KB_RIGHT]) {
				this->movePedalY(1);
			}
			if (nextMovementY == kbChars[KB_LEFT]) {
				this->movePedalY(-1);
			}
		}
		else {
			int yPedal = this->getBody().front().getPosition().getY();
			if (nextMovementY == kbChars[KB_RIGHT]) {
				if (yPedal < Arena::MAX_Y - 6) {
					for (int i = 0; i < (Arena::MAX_Y - 1) / 5; ++i) {
						this->movePedalY(1);
					}
				}
			}
			if (nextMovementY == kbChars[KB_LEFT]) {
				if (yPedal > Arena::MIN_Y + 6) {
					for (int i = 0; i < (Arena::MAX_Y - 1) / 5; ++i) {
						this->movePedalY(-1);
					}
				}
			}
		}
		nextMovementY = 0;
	}

};