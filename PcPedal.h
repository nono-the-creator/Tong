#pragma once
#include "Position.h"
#include "Pedal.h"
#include <ctime>
class PcPedal : public Pedal {
private:
	const Ball& ball;
	const Pedal* otherPedal;
	int yPosToGo;
	int difficulty;
	int side;
	bool timeToCalculate() {
		if (side == RIGHT_PEDAL &&
			this->ball.getDirX() == 1 &&													
			this->ball.getBody().at(2).getPosition().getX() == this->otherPedal->getBody().front().getPosition().getX() + 5) {
			return true;
		}
		if (side == LEFT_PEDAL &&
			this->ball.getDirX() == -1 &&
			this->ball.getBody().at(5).getPosition().getX() == this->otherPedal->getBody().front().getPosition().getX() - 5) {
			return true;
		}
		
		if (this->ball.getBody().at(0).getPosition().getX() == Arena::MAX_X / 2 
							&& (side == RIGHT_PEDAL ? this->ball.getDirX() == 1 : this->ball.getDirX() == -1)) {
			return true;
		}
		
		return false;
	}
	void moveToPos() {
		int middlePedalBodyY = this->getBody().front().getPosition().getY();
		if (middlePedalBodyY < this->yPosToGo) {
			this->movePedalY(1);
		}
		else if(middlePedalBodyY > this->yPosToGo) {
			this->movePedalY(-1);
		}
	}
	void CalculatePositionToGoTo() {
		int dirX = this->ball.getDirX();
		int dirY = this->ball.getDirY();
		Position res = this->ball.getBody().at(5).getPosition();
		if (side == LEFT_PEDAL) {
			res.addToX(-3);
		}
		while (true) {
			if (res.getX() == this->getBody().front().getPosition().getX()) {
				yPosToGo = res.getY();
				break;
			}
			if (res.getY() >= Arena::MAX_Y - 2 || res.getY() <= Arena::MIN_Y + 2) {
				dirY *= -1;
			}
			res.addToX(dirX);
			res.addToY(dirY);
		}
		srand(time(NULL));
		if (rand() % difficulty == 2) {
			this->yPosToGo = (this->yPosToGo - 10) % (Arena::MAX_Y - 1);
		}
	}
public:
	enum Kinds {HUMAN = 0, BEST = 2, GOOD = 40, NOVICE = 10 };
	enum Sides { LEFT_PEDAL, RIGHT_PEDAL };
	
	PcPedal(const Position& upperPosition, int difficulty, const Ball& ball, int side) :
		Pedal(upperPosition), difficulty(difficulty), ball(ball), side(side) {
		yPosToGo = upperPosition.getY();
	}
	void initializeOtherPedal(Pedal*& otherPeadl) {
		if (this->otherPedal == NULL) {
			this->otherPedal = otherPeadl;
		}
	}
	void movemenHandler() override {
		if (this->timeToCalculate() ) {
			this->CalculatePositionToGoTo();
		}
		this->moveToPos();
	}
	
};
