
#include "Ball.h"
#include "Game.h"
//checks the direction of the ball ,moves it there in the engine and prints it in the new location.
void Ball::printBallByDir() {
	if ((this->state == BECOMING_A_BOMB && this->movesCounter%2 == 0)) {
		setColor(COLOR::RED_FADE_TEXT);
	}
	else {
		setColor(COLOR::YELLOW_TEXT);
	}
	if (this->state == BOMB) {
		setColor(COLOR::RED_TEXT);
	}
	for (Tile& t : body) {
		t.move(this->dirX, this->dirY);
		t.PrintTile();
	}
	setColor(COLOR::WHITE_TEXT);
}
void Ball::eraseBall() {
	for (Tile& t : body) {
		t.PrintTile(' ');
	}
}
//this is exectly step by step the way the animation was requsted to be.when the ball comes from above to the center.
void Ball::drawBallImpactOnCenterFromAbove() {
	setColor(COLOR::YELLOW_TEXT);
	//by dirction checks what pedal it hits.
	if (this->dirX == -1) {
		this->eraseBall();
		this->body.at(3).addToX(-1);
		this->body.at(4).addToX(-1);
		this->body.at(5).addToX(-1);
		this->body.at(6).addToX(-1);
		this->body.at(7).addToX(-2);
		this->body.at(0).addToX(-1);
		this->body.at(1).addToX(-1);
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(3).addToX(1);
		this->body.at(4).addToX(1);
		this->body.at(5).addToX(1);
		this->body.at(7).addToX(1);
		this->body.at(0).addToX(1);
		this->body.at(1).addToX(1);
		//prvents the animation from licking into the walls.
		if (this->body.front().getPosition().getY() < Arena::MAX_Y - 3) {
			for (Tile& t : body) {
				t.addToY(1);
			}
		}
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(6).addToX(1);
		this->body.at(7).addToX(1);
	}
	else {
		this->eraseBall();
		this->body.at(4).addToX(1);
		this->body.at(3).addToX(1);
		this->body.at(2).addToX(1);
		this->body.at(7).addToX(1);
		this->body.at(6).addToX(2);
		this->body.at(1).addToX(1);
		this->body.at(0).addToX(1);
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(4).addToX(-1);
		this->body.at(3).addToX(-1);
		this->body.at(2).addToX(-1);
		this->body.at(6).addToX(-1);
		this->body.at(1).addToX(-1);
		this->body.at(0).addToX(-1);
		//prvents the animation from licking into the walls.
		if (this->body.front().getPosition().getY() < Arena::MAX_Y - 3) {
			for (Tile& t : body) {
				t.addToY(1);
			}
		}
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(7).addToX(-1);
		this->body.at(6).addToX(-1);
	}
	this->dirX *= -1;
	setColor(COLOR::WHITE_TEXT);
}
//this is exectly step by step the way the animation was requsted to be.when the ball comes from above to the center.
void Ball::drawBallImpactOnCenterFromBelow() {
	setColor(COLOR::YELLOW_TEXT);
	if (this->dirX == -1) {
		this->eraseBall();
		this->body.at(3).addToX(-1);
		this->body.at(4).addToX(-1);
		this->body.at(5).addToX(-1);
		this->body.at(6).addToX(-1);
		this->body.at(7).addToX(-2);
		this->body.at(0).addToX(-1);
		this->body.at(1).addToX(-1);
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(3).addToX(1);
		this->body.at(4).addToX(1);
		this->body.at(5).addToX(1);
		this->body.at(7).addToX(1);
		this->body.at(0).addToX(1);
		this->body.at(1).addToX(1);
		//prvents the animation from licking into the walls.
		if (this->body.back().getPosition().getY() > Arena::MIN_Y + 3) {
			for (Tile& t : body) {
				t.addToY(-1);
			}
		}
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(6).addToX(1);
		this->body.at(7).addToX(1);
	}
	else {
		this->eraseBall();
		this->body.at(4).addToX(1);
		this->body.at(3).addToX(1);
		this->body.at(2).addToX(1);
		this->body.at(7).addToX(1);
		this->body.at(6).addToX(2);
		this->body.at(1).addToX(1);
		this->body.at(0).addToX(1);
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(4).addToX(-1);
		this->body.at(3).addToX(-1);
		this->body.at(2).addToX(-1);
		this->body.at(6).addToX(-1);
		this->body.at(1).addToX(-1);
		this->body.at(0).addToX(-1);
		//prvents the animation from licking into the walls.
		if (this->body.back().getPosition().getY() > Arena::MIN_Y + 3) {
			for (Tile& t : body) {
				t.addToY(-1);
			}
		}
		printStaticBall();
		Sleep(Game::gameDifficulty);
		this->eraseBall();
		this->body.at(7).addToX(-1);
		this->body.at(6).addToX(-1);
	}
	this->dirX *= -1;
	setColor(COLOR::WHITE_TEXT);
}
std::vector<Tile> Ball::getNextMovementBody() const {
	std::vector<Tile> bodyCopy(this->body);
	for (Tile& t : bodyCopy) {
		t.move(this->dirX, this->dirY);
	}
	return bodyCopy;
}
//prints the ball in place.
void Ball::printStaticBall() {
	for (const Tile& t : this->body) {
		t.PrintTile();
	}
}


