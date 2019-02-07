#include "Pedal.h"
//creats new pedal by the requested upper possiotion. 
Pedal::Pedal(const Position& upperPosition) {
	for (int i = 0; i < PEDAL_SIZE; i++) {
		body.push_back(Tile({ upperPosition.getX(),upperPosition.getY() + i }, 1, '#'));
	}
};
//moves the pedal by x,and also indicates if the pedal lost for moving this far.
int Pedal::movePedalX(int dirX) {
	if ((this->body.front().getPosition().getX() == LEFT_PEDAL_X && dirX == -1) ||
		this->body.front().getPosition().getX() == RIGHT_PEDAL_X && dirX == 1) {
		return 0;
	}
	setColor(COLOR::RED_TEXT);
	for (Tile& t : body) {
		t.PrintTile(' ');
		t.move(dirX, 0);
		t.PrintTile();
	}
	if (this->body.front().getPosition().getX() == RIGHT_LOST) {
		return RIGHT_LOST;
	}
	if (this->body.front().getPosition().getX() == LEFT_LOST) {
		return LEFT_LOST;
	}
	return 0;
	setColor(COLOR::WHITE_TEXT);
}
//simply prints the pedal as it is on the engine.
void Pedal::PrintPedal() const {
	setColor(COLOR::RED_TEXT);
	for (const Tile& t : body) {
		t.PrintTile();
	}
	setColor(COLOR::WHITE_TEXT);
}
