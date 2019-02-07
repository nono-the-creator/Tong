#pragma once

#include "Tile.h"
#include "Arena.h"
#include "EventHandler.h"
#include <list>

class Pedal {
private:
	std::list<Tile> body;
public:
	enum { PEDAL_SIZE = 3, KB_LEFT = 0, KB_RIGHT = 1, BOMB = 2 };
	//starting position of pedals.
	enum PedalLocation {
		LEFT_PEDAL_X = 4, LEFT_PEDAL_Y = 10, RIGHT_PEDAL_X = 76,
		RIGHT_PEDAL_Y = 11, LEFT_LOST = 20, RIGHT_LOST = 60
	};
	enum { REDUCE_SCORE, INCREASE_SCORE };
	//gets the upper # of the pedal and completes the two beneath.
	Pedal(const Position& upperPosition);
	//moves pedal by the dirction given in the engine and prints it.
	void movePedalY(int dirY) {
		setColor(COLOR::RED_TEXT);
		if (dirY > 0 && (body.back().getPosition().getY() < Arena::MAX_Y - 1)) {
			Tile temp = body.front();
			temp.PrintTile(' ');
			body.pop_front();
			temp.move(0, PEDAL_SIZE);
			body.push_back(temp);
			temp.PrintTile();
		}
		if ((dirY < 0) && (body.front().getPosition().getY() > Arena::MIN_Y + 1)) {
			Tile temp = body.back();
			temp.PrintTile(' ');
			body.pop_back();
			temp.move(0, -PEDAL_SIZE);
			body.push_front(temp);
			temp.PrintTile();
		}
		setColor(COLOR::WHITE_TEXT);
	}
    //moves the pedal by x,and also indicates if the pedal lost for moving this far.
	int movePedalX(int dirX);
	//simply prints the pedal as it is on the engine.
	void PrintPedal() const;
	const std::list<Tile>& getBody() const {
		return this->body;
	}
	virtual void movemenHandler() = 0;
};

