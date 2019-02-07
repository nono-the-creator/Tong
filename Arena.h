
#ifndef NUKINONO_ARENA_H
#define NUKINONO_ARENA_H

#include "Tile.h"
#include "Position.h"
#include <list>
#include "utils.h"
//represents the game space.
class Arena {
private:
	//every wall of the game comprised by a list of tiles.
	std::list<Tile> rWall;
	std::list<Tile> lWall;
	std::list<Tile> upWall;
	std::list<Tile> downWall;

public:
	enum ArenaSize { MIN_X = 1, MAX_X = 79, MIN_Y = 4, MAX_Y = 29};
	Arena();
	void printArena() const;
};


#endif //NUKINONO_ARENA_H
