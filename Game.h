//
// Created by noam ambar on 16/12/2018.
//

#ifndef NUKINONO_GAME_H
#define NUKINONO_GAME_H

#include "Arena.h"
#include "HumanPedal.h"
#include "Pedal.h"
#include "Ball.h"
#include "KeyboardManager.h"
#include "Tetris.h"
#include "PcPedal.h"
#include "Pauser.h"
class Game {
private:

	int status; // game status
	Arena arena;
	Pedal* rPedal; // right pedal
	Pedal* lPedal; // left pedal
	Ball ball;
	KeyboardManager kbManager;
	Tetris tetris;
	Pauser pauser;
public:

	static int gameDifficulty; // the game difficulty
	enum GameStatus { READY, PAUSED, ONGOING, OVER };

	Game() : ball(""),
		pauser({ 1, KeyboardManager::ESC }) {
		this->status = READY;
		kbManager.registerKbListener(&pauser);
		this->lPedal = NULL;
		this->rPedal = NULL;
	};
	void initializeHumanPedal(int side) {
		if (side == PcPedal::LEFT_PEDAL && this->lPedal == NULL) {
			this->lPedal = new HumanPedal({ Pedal::LEFT_PEDAL_X, Pedal::LEFT_PEDAL_Y }, "qa");
			kbManager.registerKbListener((HumanPedal*)lPedal);
			this->ball.addCharToKbString('s');
		}
		else if(this->rPedal == NULL) {
			this->rPedal =  new HumanPedal({ Pedal::RIGHT_PEDAL_X, Pedal::RIGHT_PEDAL_Y }, "pl");
			kbManager.registerKbListener((HumanPedal*)rPedal);
			this->ball.addCharToKbString('k');
		}
		if (this->rPedal != NULL && this->lPedal != NULL) {
			kbManager.registerKbListener(&ball);
		}
	}
	
	////////////////////////////create destructor --- virtual ? pedal needs to be deleted ////////////////////
	int getStatus() {
		if (this->pauser.isToPause()) {
			this->status = PAUSED;
		}
		return status;
	}

	void setStatus(int status) {
		if (status != PAUSED) {
			pauser.setToPause(false);
		}
		else {
			pauser.setToPause(true);
		}
		Game::status = status;
	}

	Arena &getArena() {
		return arena;
	}

	void setArena(const Arena &arena) {
		Game::arena = arena;
	}

	Pedal &getRPedal() {
		return *this->rPedal;
	}

	Pedal &getLPedal() {
		return *this->lPedal;
	}
	Pedal*& getRPedalPointer() {
		return this->rPedal;
	}
	Pedal*& getLPedalPointer() {
		return this->lPedal;
	}
	void initializeLPedalPC(PcPedal*& lPedal) {
		if (this->lPedal == NULL) {
			this->lPedal = lPedal;
		}
		if (this->rPedal != NULL && this->lPedal != NULL) {
			kbManager.registerKbListener(&ball);
		}
	}
	void initializeRPedalPC(PcPedal*& rPedal) {
		if (this->rPedal == NULL) {
			this->rPedal = rPedal;
		}
		if (this->rPedal != NULL && this->lPedal != NULL) {
			kbManager.registerKbListener(&ball);
		}
	}
	Ball &getBall() {
		return ball;
	}

	void setBall(const Ball &ball) {
		Game::ball = ball;
	}

	KeyboardManager& getKbManager() {
		return this->kbManager;
	}

	Tetris& getTetris() {
		return this->tetris;
	}
	// handle the event of brick drop
	void handleNewBrick(Pedal& pedal, int side) {
		setColor(COLOR::RED_FADE_TEXT);
		this->tetris.dropBrick(pedal, side);
		setColor(COLOR::WHITE_TEXT);
	}
};

#endif //NUKINONO_GAME_H
