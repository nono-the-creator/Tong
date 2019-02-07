#include "Tetris.h"
#include "Ball.h"
//gets a brick and the the side its fallinf to and checks if it's "fallable",meaning if the next step for the brick is free and no wall/other brick is blocking it.
bool Tetris::fallable(const Brick& fallingBrick, int side) {
	//future brick is temporarly being made to makesure its o.k to move the real brick to the future position.
	Brick futureBrick{ fallingBrick };
	futureBrick.addToX((side * 2) - 1);
	//checks if going to hit a wall.
	if (futureBrick.getBody().front().getPosition().getX() == Arena::MAX_X ||
		futureBrick.getBody().front().getPosition().getX() == Arena::MIN_X) {
		return false;
	}
	//checking if going to overlap another brick.
	for (const Brick& b : bricks[side]) {
		if (b.isOverlapping(futureBrick)) {
			return false;
		}
	}
	return true;
}
//prints an animation of a line with given line and char.
void Tetris::printExplosion(int line, char ch) {
	for (int i = Arena::MIN_Y + 1; i < Arena::MAX_Y; i++) {
		gotoxy(line, i);
		std::cout << ch;
	}
}
//once the brick stopped from moving,the function saves it in the array of bricks in the matching wall.
//also,it increaces by 1 the line counter of bricks,and if it indicates that the is now full(after adding the brick),it sends the line to "popline".
//becuase the line should explode and disapear.
void Tetris::registerToBricks(Brick& brickToRegister, bool side, Pedal& pedal) {
	bricks[side].push_back(brickToRegister);
	if (++linesBrickCounters[brickToRegister.getX()] >= BricksToCompelteLine) {
		popLine(brickToRegister.getX(), side);
		for (int i = 0; i < 6; i++) {
			pedal.movePedalX((2 * side) - 1);
		}
	}
}
void Tetris::deleteAllWallsFromScreen() {
	for (const Brick& b : this->bricks[LEFT_WALL]) {
		b.printBrick(' ');
	}
	for (const Brick& b : this->bricks[RIGHT_WALL]) {
		b.printBrick(' ');
	}
}
//countes how many bricks are in each line,(only oprated after a line poped and all the data changed)
void Tetris::updateLinesBrickCounters() {
	for (int& t : linesBrickCounters) {
		t = 0;
	}
	for (Brick& b : bricks[RIGHT_WALL]) {
		linesBrickCounters[b.getX()]++;
	}
	for (Brick& b : bricks[LEFT_WALL]) {
		linesBrickCounters[b.getX()]++;
	}
}
//when tetris is being created, no bricks are on the walls.so the indicators should all be 0.
Tetris::Tetris() {
	for (int& t : linesBrickCounters) {
		t = 0;
	}
}
//moves brick untill no longer able,and then updates the new bricks sitoation.
void Tetris::dropBrick(Pedal& pedal, int side) {
	Brick brick({ pedal, (side * 2) - 1 });
	while (fallable(brick, side)) {
		brick.move();
		Sleep(30);
	}
	this->registerToBricks(brick, side, pedal);
}
//prints the walls of bricks from the engine to the screen as is.
void Tetris::printAllWalls() {
	setColor(COLOR::RED_FADE_TEXT);
	for (const Brick& b : this->bricks[LEFT_WALL]) {
		b.printBrick();
	}
	for (const Brick& b : this->bricks[RIGHT_WALL]) {
		b.printBrick();
	}
	setColor(COLOR::WHITE_TEXT);
}
//calls line explosion animation,earase the poped line from engine, and then moves back the bricks that was above the poped line so the wall be consistant.
void Tetris::popLine(int line, int side) {
	//animation of explosion
	setColor(COLOR::YELLOW_TEXT);
	printExplosion(line, '*');
	Sleep(50);
	setColor(COLOR::RED_TEXT);
	printExplosion(line, '#');
	Sleep(50);
	setColor(COLOR::YELLOW_TEXT);
	printExplosion(line, '*');
	Sleep(50);
	printExplosion(line, ' ');
	setColor(COLOR::WHITE_TEXT);
	Sleep(60);

	vector<Brick>::iterator temp;
	//erase all of the poped line bricks.
	this->deleteAllWallsFromScreen();
	for (vector<Brick>::iterator iterator = this->bricks[side].begin();
		iterator != this->bricks[side].end();) {
		if (iterator->getX() == line) {
			iterator = this->bricks[side].erase(iterator);
		}
		else {
	        //moves back the bricks that was above the poped line
			if (side == RIGHT_WALL && iterator->getX() < line) {
				iterator->addToX(1);
			}
			if (side == LEFT_WALL && iterator->getX() > line) {
				iterator->addToX(-1);
			}
			iterator++;
		}
	}
	//counters now should be recounting by the new valuse.
	updateLinesBrickCounters();
	//prints the new sitoation.
	this->printAllWalls();
}
int Tetris::getBricksHitPosX(const Ball& ball, int side) {

	std::vector<Tile> nextMovementBallBody = ball.getNextMovementBody();

	for (const Brick& brick : this->bricks[side]) {
		for (const Tile& ballTile : nextMovementBallBody) {
			for (const Tile& brickTile : brick.getBody()) {
				if (brickTile.getPosition() == ballTile.getPosition()) {
					return ballTile.getPosition().getX();
				}
			}
		}
	}
	for (const Tile& t : nextMovementBallBody) {
		if (t.getPosition().getX() <= Arena::MIN_X || t.getPosition().getX() >= Arena::MAX_X) {
			return BALL_HIT_WALL;
		}
	}
	return NO_HIT_ACCURED;
}