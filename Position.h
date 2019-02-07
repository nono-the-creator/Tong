//
// Created by noam ambar on 16/12/2018.
//

#ifndef NUKINONO_POSITION_H
#define NUKINONO_POSITION_H
//the class is simply there to be able to get,set,move,positions of objects in the game.
class Position {
private:
    int x;
    int y;
public:
    int getX() const {
        return x;
    }

    void setX(int x) {
        Position::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Position::y = y;
    }

    Position(int x, int y) : x(x), y(y) {};
	friend class Tile;
	void addToX(int num) {
		this->x += num;
	}
	void addToY(int num) {
		this->y += num;
	}
	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};




#endif //NUKINONO_POSITION_H
