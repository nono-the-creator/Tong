
#ifndef NUKINONO_TILE_H
#define NUKINONO_TILE_H

#include <iostream>
#include "Position.h"
#include "utils.h"
//the class is much like position,simply there to be able to get,set,move,positions of objects in the game,but with a certien char that is representing it.
class Tile {
private:
	Position position;
	bool isSolid;
	char ch;
public:

	const Position& getPosition() const {
		return this->position;
	}

	Tile(const Position &position, bool isSolid, char ch);
	void PrintTile() const {
		gotoxy(this->position.getX(), this->position.getY());
		std::cout << this->ch;
	}
	void PrintTile(char ch) const {
		gotoxy(this->position.getX(), this->position.getY());
		std::cout << ch;
	}
	void move(int dirX, int dirY) {
		this->position.x += dirX;
		this->position.y += dirY;
	}
	void addToX(int num) {
		this->position.addToX(num);
	}
	void addToY(int num) {
		this->position.addToY(num);
	}
	void setCharacter(char ch) {
		this->ch = ch;
	}
};


#endif //NUKINONO_TILE_H
