#pragma once

#include <list>
#include "Tile.h"
#include "Pedal.h"
//object of class Brick isan object of a "pedals copies" as we where constracted to make,or as we call it-brick.brick is falling-to\comprising  a wall in the tetris class.
class Brick {

private:
	std::list<Tile> body; //a list of the tiles of every brick
	int dirX; //dirction of falling of the brick

public:
	//gets a peadal that had just lost a round,and copies its loction what seem as a "copy" of the pedal drops is actually a new brick added.
	Brick(const Pedal& pedal, int dirX) {
		//constant amount of loops(3)
		for (const Tile& t : pedal.getBody()) {
			this->body.push_back(t);
			this->dirX = dirX;
		}
		this->printBrick();
	}
	void printBrick(char ch = '#') const {
		//constant amount of loops(3)		
		for (const Tile& t : body) {
			t.PrintTile(ch);
		}
	}
	const std::list<Tile>& getBody() const {
		return this->body;
	}
	//moves by all means,deletes from preveus location,moves by dir in the engine and then prints new location.
	void move();
	//moves all the num times.(by dirction of num).
	void addToX(int num);
	//checks if there is an overlap between two bricks.(actually used by "future" bricks to prevent such over lap.)
	bool isOverlapping(const Brick& other) const;
	int getX() const {
		return this->body.front().getPosition().getX();
	}
};