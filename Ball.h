#pragma once
#include "Tile.h"
#include <vector>
#include "Pedal.h"
#include <ctime>
#include "EventHandler.h"

class Ball : public EventHandler {
private:
	int movesCounter;
	int BALL_BODY_SIZE = 8;//from 8 'O's
	std::vector<Tile> body;//the order of the list goes like this : the first is the bottom left and then you go right if you can
						   // ,else up.
	int dirX;//direction of movement of ball x for sides,y for up and down
	int dirY;
	int state;
	std::string kbChars;
	//checks if the ball is going to hit the left pedal in the middle section
	bool leftPedalCenterHit(const Pedal& lPedal) {
		Position lCenterBall = this->body.at(2).getPosition();//creates the "future"position of the ball and checks it.
		lCenterBall.addToX(dirX);
		lCenterBall.addToY(dirY);

		//check if the "future" position of the ball will overlap the left pedal
		if (lCenterBall.getX() == lPedal.getBody().front().getPosition().getX()) {
			return (lCenterBall.getY() >= lPedal.getBody().front().getPosition().getY() - 1 &&
				lCenterBall.getY() <= lPedal.getBody().back().getPosition().getY() + 1);
		}
		return false;
	}
	//checks if the ball is going to hit the right pedal in the middle section
	bool rightPedalCenterHit(const Pedal& rPedal) {
		Position rCenterBall = this->body.at(5).getPosition();//creates the "future"position of the ball and checks it.

		rCenterBall.addToX(dirX);
		rCenterBall.addToY(dirY);
		//check if the "future" position of the ball will overlap the left pedal
		if (rCenterBall.getX() == rPedal.getBody().front().getPosition().getX()) {
			return (rCenterBall.getY() >= rPedal.getBody().front().getPosition().getY() - 1
				&& rCenterBall.getY() <= rPedal.getBody().back()
				.getPosition().getY() + 1);
		}
		return false;
	}
	//checks if the ball is going to hit the corner of the left pedal
	bool leftPedalCornerHit(const Pedal& lPedal) {
		Position lUpperCorner = this->body.at(6).getPosition();
		Position lLowerCorner = this->body.front().getPosition();
		lUpperCorner.addToX(dirX);
		lUpperCorner.addToY(dirY);
		lLowerCorner.addToX(dirX);
		lLowerCorner.addToY(dirY);
		return (lLowerCorner == lPedal.getBody().front().getPosition()
			|| lUpperCorner == lPedal.getBody().back().getPosition());
	}
	//checks if the ball is going to hit the corner of the right pedal
	bool rightPedalCornerHit(const Pedal& rPedal) {
		Position rUpperCorner = this->body.at(7).getPosition();
		Position rLowerCorner = this->body.at(1).getPosition();
		rUpperCorner.addToX(dirX);
		rUpperCorner.addToY(dirY);
		rLowerCorner.addToX(dirX);
		rLowerCorner.addToY(dirY);
		return (rLowerCorner == rPedal.getBody().front().getPosition()
			|| rUpperCorner == rPedal.getBody().back().getPosition());
	}
	void checkAndUpdateBallState(const Pedal& lPedal, const Pedal& rPedal) {
		this->movesCounter++;
		if (this->state == BECOMING_A_BOMB) {
			if (this->movesCounter == 8) {
				this->movesCounter = 0;
				this->state = BOMB;
			}
		}
		else if (this->state == BOMB) {
			if (this->movesCounter == 4 && this->isBetweenPedals(lPedal, rPedal)) {
				this->state = REGULAR;
			}
		}
		if (this->state == REGULAR) {
			movesCounter = 0;
		}
	}
	byte handlePedalHit(const Pedal& lPedal, const Pedal& rPedal) {

		//if its going to hit a pedal in the center,sends it to the matching animation.
		if (rightPedalCenterHit(rPedal)) {
			if (this->dirY == 1) { // ball hit from above
				this->drawBallImpactOnCenterFromAbove();
			}
			if (this->dirY == -1) { // ball hit from below
				this->drawBallImpactOnCenterFromBelow();
			}
			if (this->state == BECOMING_A_BOMB) {
				this->state = REGULAR;
			}
			if (this->state == BOMB) {
				return BOMB_HIT_RIGHT;
			}
		}
		else if (rightPedalCornerHit(rPedal)) {
			this->dirX *= -1;
			this->dirY *= -1;
			if (this->state == BECOMING_A_BOMB) {
				this->state = REGULAR;
			}
			if (this->state == BOMB) {
				return BOMB_HIT_RIGHT;
			}
		}
		if (leftPedalCenterHit(lPedal)) {
			if (this->dirY == 1) { // ball hit from above
				this->drawBallImpactOnCenterFromAbove();
			}
			if (this->dirY == -1) { // ball hit from below
				this->drawBallImpactOnCenterFromBelow();
			}
			if (this->state == BECOMING_A_BOMB) {
				this->state = REGULAR;
			}
			if (this->state == BOMB) {
				return BOMB_HIT_LEFT;
			}
		}
		else if (leftPedalCornerHit(lPedal)) {
			this->dirX *= -1;
			this->dirY *= -1;
			if (this->state == BECOMING_A_BOMB) {
				this->state = REGULAR;
			}
			if (this->state == BOMB) {
				return BOMB_HIT_LEFT;
			}
		}
		return VALID;
	}

	byte checkPedalCross(const Pedal& lPedal, const Pedal& rPedal) {
		int lCenterBallX = this->body.at(2).getPosition().getX() - 1;
		int rCenterBallX = this->body.at(5).getPosition().getX() + 1;
		//checks if the ball is about to cross the left pedal 
		if (rCenterBallX > rPedal.getBody().front().getPosition().getX()) {
			if (this->state == REGULAR) {
				this->body.clear();
				this->locateAtCenter();
			}
			else {
				this->printBallByDir();
			}
			return CROSSED_RIGHT;
		}
		if (lCenterBallX < lPedal.getBody().front().getPosition().getX()) {
			if (this->state == REGULAR) {
				this->body.clear();
				this->locateAtCenter();
			}
			else {
				this->printBallByDir();
			}
			return CROSSED_LEFT;
		}
		else {
			this->printBallByDir();
			return VALID;
		}
	}

	bool isBetweenPedals(const Pedal& lPedal, const Pedal& rPedal) {

		int lCenterBallX = this->body.at(2).getPosition().getX();
		int rCenterBallX = this->body.at(5).getPosition().getX();
		return (lCenterBallX >= lPedal.getBody().front().getPosition().getX()
			&& rCenterBallX <= rPedal.getBody().front().getPosition().getX());
	}
public:

	enum BallState { REGULAR, BECOMING_A_BOMB, BOMB, VALID, CROSSED_LEFT, CROSSED_RIGHT, BOMB_HIT_RIGHT, BOMB_HIT_LEFT };

	//gets the left lowest point.
	Ball(std::string kbChars) {
		this->locateAtCenter();
		this->state = REGULAR;
		this->movesCounter = 0;
		this->kbChars = kbChars;
	}
	void addCharToKbString(char toAdd) {
		this->kbChars.push_back(toAdd);
	}
	std::vector<Tile> getNextMovementBody() const;
	const int getState() {
		return this->state;
	}
	void setState(int state) {
		this->state = state;
	}
	//locating the ball at the center in the engin,then randomly pick dirctions for it/
	void locateAtCenter() {
		this->state = REGULAR;
		Position firstBallPos{ Arena::MAX_X / 2, Arena::MAX_Y / 2 };
		srand(time(NULL));
		this->dirX = (rand() % 2) == 0 ? -1 : 1;
		this->dirY = (rand() % 2) == 0 ? -1 : 1;
		int x = firstBallPos.getX();
		int y = firstBallPos.getY();
		this->eraseBall();
		this->body.clear();
		this->body.push_back(Tile(firstBallPos, 1, 'O'));
		this->body.push_back(Tile({ x + 1, y }, 1, 'O'));
		this->body.push_back(Tile({ x - 1, y - 1 }, 1, 'O'));
		this->body.push_back(Tile({ x, y - 1 }, 1, 'O'));
		this->body.push_back(Tile({ x + 1 , y - 1 }, 1, 'O'));
		this->body.push_back(Tile({ x + 2 , y - 1 }, 1, 'O'));
		this->body.push_back(Tile({ x , y - 2 }, 1, 'O'));
		this->body.push_back(Tile({ x + 1, y - 2 }, 1, 'O'));
	}
	void printBallByDir();
	void setDirX(int dirX) {
		this->dirX = dirX;
	}
	void setDirY(int dirY) {
		this->dirY = dirY;
	}
	void eraseBall();

	void drawBallImpactOnCenterFromAbove();
	void drawBallImpactOnCenterFromBelow();
	void printStaticBall();
	//this function is how the ball logicly moves in the game,the game calls it and expects it to know
	//how the ball should indepently behave by only knowing the location of the pedals.
	int getDirX() {
		return this->dirX;
	}
	int getDirX() const {
		return this->dirX;
	}
	int getDirY() const {
		return this->dirY;
	}
	void becomeABomb() {
		this->state = BECOMING_A_BOMB;
	}
	byte moveBall(const Pedal& lPedal, const Pedal& rPedal) {

		byte res;
		//checks if the ball is about to pass the arena boundris
		if (this->body.front().getPosition().getY() >= Arena::MAX_Y - 1 ||
			this->body.back().getPosition().getY() <= Arena::MIN_Y + 1) {
			this->dirY *= -1;
		}
		this->checkAndUpdateBallState(lPedal, rPedal);
		res = this->handlePedalHit(lPedal, rPedal);
		if (res == VALID) {
			this->eraseBall();
			return this->checkPedalCross(lPedal, rPedal);
		}
		else {
			return res;
		}
	}
	void handleKey(char ch) override {
		if (ch == tolower('s') && this->dirX == 1) {
			this->becomeABomb();
		}
		if (ch == tolower('k') && this->dirX == -1) {
			this->becomeABomb();
		}
	}
	std::string getKbChars() override {
		return this->kbChars;
	}
	const std::vector<Tile>& getBody() const {
		return this->body;
	}
};

