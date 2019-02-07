
#include "Brick.h"

//checks if there is an overlap between two bricks.(actually used by "future" bricks to prevent such over lap.)
bool Brick::isOverlapping(const Brick& other) const {
	//these loops runs a constant amount of times (9) so its not inefficient.
	for (const Tile& t1 : other.body) {
		for (const Tile& t2 : this->body) {
			if ((t1.getPosition() == t2.getPosition())) {
				return true;
			}
		}
	}
	return false;
}
//moves all the num times.(by dirction of num).
void Brick::addToX(int num) {
	for (Tile& t : body) {
		t.addToX(num);
	}
}
//moves by all means,deletes from preveus location,moves by dir in the engine and then prints new location.
void Brick::move() {
	for (Tile& t : body) {
		t.PrintTile(' ');
		t.move(dirX, 0);
		t.PrintTile();
	}
}