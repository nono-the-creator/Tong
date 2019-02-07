#pragma once

#include <vector>
#include <algorithm>
#include "Tile.h"
#include "Pedal.h"
#include "Brick.h"
#include "ball.h"

using namespace std;
//hendles all the tetris part of the game.
class Tetris {

private:
	//two brick arrays,one for every wall.
	std::vector<Brick> bricks[2];
	//every line of the areana in this array called "linesBrickCounters" gets represented by its 'x' position.
	//kind of like in bucket sort,
	// every node in the array is repersenting a line on the arena,
	//and every brick in the line adds +1 to the line where it is.
	//so when the node value is more then "BricksToCompelteLine" 
	//it indicates that the line it represents should explode.
	int linesBrickCounters[Arena::MAX_X + 1];
	//calculates how many in the same line for pop.
	int BricksToCompelteLine = (Arena::MAX_Y - Arena::MIN_Y) / Pedal::PEDAL_SIZE;
    //gets a brick and the the side its fallinf to and checks if it's "fallable",meaning if the next step for the brick is free and no wall/other brick is blocking it.	
	bool fallable(const Brick& fallingBrick, int side);
    //prints an animation of a line with given line and char.	
	void printExplosion(int line, char ch);
	//very long docomendation in the cpp file.
	void registerToBricks(Brick& brickToRegister, bool side, Pedal& pedal);
    //countes how many bricks are in each line,(only oprated after a line poped and all the data changed)	
	void updateLinesBrickCounters();
	void deleteAllWallsFromScreen();
public:
	enum { LEFT_WALL = 0, RIGHT_WALL = 1 , NO_HIT_ACCURED = -1, BALL_HIT_WALL = -2};
	Tetris();
    //moves brick untill no longer able,and then updates the new bricks sitoation.	
	void dropBrick(Pedal& pedal, int side);
    //prints the walls of bricks from the engine to the screen as is.	
	void printAllWalls();
    //calls line explosion animation,earase the poped line from engine, and then moves back the bricks that was above the poped line so the wall be consistant.
	void popLine(int line, int side);
	int getBricksHitPosX(const Ball& ball, int side);
};