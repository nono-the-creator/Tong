#include "Arena.h"
#include "Game.h"
#include "Pauser.h"

class StartNewGameMenu {
private:
	Arena arena;
	KeyboardManager kbManager;
	HumanPedal lPedal;
	HumanPedal rPedal;
	Pauser pauser;

	int getKind(int pedalY) {
		switch (pedalY) {
		case Arena::MIN_Y + 5:
			return PcPedal::HUMAN;	
		case Arena::MIN_Y + 10:
			return PcPedal::NOVICE;
		case Arena::MIN_Y + 15:
			return PcPedal::GOOD;
		case Arena::MIN_Y + 20:
			return PcPedal::BEST;
		}
	}
	void initiateGame(Game*& pGame) {
		int lPedalKind;
		int rPedalKind;
		PcPedal* gameLPedal = NULL;
		PcPedal* gameRPedal = NULL;
		lPedalKind = getKind(lPedal.getBody().front().getPosition().getY() + 1);
		rPedalKind = getKind(rPedal.getBody().front().getPosition().getY() + 1);
		pGame = new Game();
		if (lPedalKind == PcPedal::HUMAN) {
			pGame->initializeHumanPedal(PcPedal::LEFT_PEDAL);
		}
		else {
			gameLPedal = new PcPedal({ Pedal::LEFT_PEDAL_X, Pedal::LEFT_PEDAL_Y },
				lPedalKind, pGame->getBall(), PcPedal::LEFT_PEDAL);
			pGame->initializeLPedalPC(gameLPedal);
		}
		if (rPedalKind == PcPedal::HUMAN) {
			pGame->initializeHumanPedal(PcPedal::RIGHT_PEDAL);
		}
		else {
			gameRPedal = new PcPedal({ Pedal::RIGHT_PEDAL_X, Pedal::RIGHT_PEDAL_Y },
				rPedalKind, pGame->getBall(), PcPedal::RIGHT_PEDAL);
			pGame->initializeRPedalPC(gameRPedal);
		}
		if (lPedalKind != PcPedal::HUMAN) {
			gameLPedal->initializeOtherPedal(pGame->getRPedalPointer());
		}
		if (rPedalKind != PcPedal::HUMAN) {
			gameRPedal->initializeOtherPedal(pGame->getLPedalPointer());
		}
	}
public:
	StartNewGameMenu() : lPedal({ Pedal::LEFT_PEDAL_X + 10, Arena::MIN_Y + 4 }, "qa", true),
		rPedal({ Pedal::RIGHT_PEDAL_X - 10, Arena::MIN_Y + 4 }, "pl", true),
		pauser({ 2, KeyboardManager::ESC, KeyboardManager::ENTER_BUTTON }) {
		kbManager.registerKbListener(&lPedal);
		kbManager.registerKbListener(&rPedal);
		kbManager.registerKbListener(&pauser);
	}
	bool showUntilEscOrNewGame(Game*& pGame) {
		setColor(COLOR::TEAL_FADE_BACKGROUND);
		arena.printArena();
		setColor(COLOR::BLACK_BACKGROUND);
		setColor(COLOR::RED_TEXT);
		lPedal.PrintPedal();
		rPedal.PrintPedal();
		setColor(COLOR::WHITE_TEXT);
		printTitle({ Arena::MAX_X / 2, 2 }, "Use 'P', 'L', 'A', 'Q' To Choose Players");
		printTitle({ Arena::MAX_X / 2, Arena::MIN_Y + 5 }, "Human Player");
		printTitle({ Arena::MAX_X / 2, Arena::MIN_Y + 10 }, "Computer : Novice");
		printTitle({ Arena::MAX_X / 2, Arena::MIN_Y + 15 }, "Computer : Good");
		printTitle({ Arena::MAX_X / 2, Arena::MIN_Y + 20 }, "Computer : Best");

		while (true) {

			if (this->pauser.isToPause()) {
				system("cls");
				return false;
			}
			kbManager.handleKeyboard();
			this->lPedal.movemenHandler();
			this->rPedal.movemenHandler();
			if (pauser.isToEnter()) {
				this->initiateGame(pGame);
				return true;
			}
		}
	}
};