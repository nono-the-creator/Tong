
#include "Arena.h"
#include "Tile.h"
Arena::Arena() {
	int i;
	for (i = MIN_Y; i < MAX_Y; ++i) {
		rWall.push_back(Tile{ { MAX_X, i }, 0,' ' });
		lWall.push_back(Tile{ { MIN_X, i }, 0,' ' });
	}
	for (i = MIN_X; i < MAX_X; ++i) {
		upWall.push_back(Tile({ i, MIN_Y }, 1, '-'));
		downWall.push_back(Tile({ i, MAX_Y }, 1, '-'));
	}
}
void Arena::printArena() const {

	for (const Tile& t : rWall) {
		t.PrintTile();
	}
	for (const Tile& t : lWall) {
		t.PrintTile();
	}
	for (const Tile& t : upWall) {
		t.PrintTile();
	}
	for (const Tile& t : downWall) {
		t.PrintTile();
	}
}

