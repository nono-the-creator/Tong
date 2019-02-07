#include "MainMenu.h"

//finds the current button the users can press
int MainMenu::findClickable() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i).getClickability()) {
			return i;
		}
	}
}
void MainMenu::checkAndHandleUnRegularBallPedalCross(int side, byte& ballState) {


	int brickHitPosX = this->pGame->getTetris().getBricksHitPosX(this->pGame->getBall(), side);
	if (this->pGame->getBall().getState() == Ball::BOMB) {
		if (brickHitPosX != Tetris::NO_HIT_ACCURED && brickHitPosX != Tetris::BALL_HIT_WALL) { // a brick hit accured
			this->pGame->getBall().locateAtCenter();
			this->pGame->getTetris().popLine(brickHitPosX, side);
			handleScore(side, Pedal::INCREASE_SCORE);
		}
		else if (brickHitPosX == Tetris::BALL_HIT_WALL) {
			this->pGame->getTetris().popLine(side == Tetris::LEFT_WALL ? Arena::MIN_X + 1 : Arena::MAX_X - 1, side);
			this->pGame->getBall().locateAtCenter();
			handleScore(side, Pedal::INCREASE_SCORE);
		}
	}
	else if (this->pGame->getBall().getState() == Ball::BECOMING_A_BOMB && brickHitPosX != Tetris::NO_HIT_ACCURED) {//ball is becoming a bomb but didn't hit anything.
		this->pGame->getBall().locateAtCenter();
		setColor(COLOR::RED_FADE_TEXT);
		this->pGame->getTetris().dropBrick(side == Tetris::RIGHT_WALL ? this->pGame->getRPedal() : this->pGame->getLPedal(),
			side);
		setColor(COLOR::WHITE_TEXT);
		handleScore(side, Pedal::REDUCE_SCORE);
	}

	if (side == Tetris::LEFT_WALL) {
		this->pGame->getLPedal().PrintPedal();
	}
	else {
		this->pGame->getRPedal().PrintPedal();
	}
}
// the current game loop
void MainMenu::gameLoop() {

	printInitialziedGame(this->pGame);
	pGame->getTetris().printAllWalls();
	int delayCounter = -2; // a variable that postpones the after bombing pedal x movement
	bool rightPedalAfterBomb = false;
	bool leftPedalAfterBomb = false;
	while (true) {
		this->printScore();
		this->pGame->getKbManager().handleKeyboard();
		this->pGame->getLPedal().movemenHandler();
		this->pGame->getRPedal().movemenHandler();
		if (rightPedalAfterBomb) {
			if (delayCounter == 4) {
				delayCounter = -4;
				rightPedalAfterBomb = false;
			}
			else if (delayCounter >= 0) {
				if (this->pGame->getRPedal().movePedalX(-1) == Pedal::RIGHT_LOST) {
					this->endGame("right player lost");
					break;
				}
			}
		}
		if (leftPedalAfterBomb) {
			if (delayCounter == 4) {
				delayCounter = -4;
				leftPedalAfterBomb = false;
			}
			else if (delayCounter >= 0) {
				if (this->pGame->getLPedal().movePedalX(1) == Pedal::LEFT_LOST) {
					this->endGame("left player lost");
					break;
				}
			}
		}
		byte ballLocationState = this->pGame->getBall().moveBall(this->pGame->getLPedal(), this->pGame->getRPedal());
		if (ballLocationState == Ball::BOMB_HIT_RIGHT) {
			this->pGame->handleNewBrick(this->pGame->getRPedal(), Tetris::RIGHT_WALL);
			this->pGame->getRPedal().PrintPedal();
			rightPedalAfterBomb = true;
		}
		else if (ballLocationState == Ball::BOMB_HIT_LEFT) {
			this->pGame->handleNewBrick(this->pGame->getLPedal(), Tetris::LEFT_WALL);
			this->pGame->getLPedal().PrintPedal();
			leftPedalAfterBomb = true;
		}
		else if (ballLocationState == Ball::CROSSED_LEFT) {
			if (this->pGame->getBall().getState() == Ball::REGULAR) {
				this->pGame->handleNewBrick(this->pGame->getLPedal(), Tetris::LEFT_WALL);
				if (this->pGame->getLPedal().movePedalX(1) == Pedal::LEFT_LOST) {
					this->endGame("left player lost");
					break;
				}
			}
			else {
				checkAndHandleUnRegularBallPedalCross(Tetris::LEFT_WALL, ballLocationState);
			}
		}
		else if (ballLocationState == Ball::CROSSED_RIGHT) {
			if (this->pGame->getBall().getState() == Ball::REGULAR) {
				this->pGame->handleNewBrick(this->pGame->getRPedal(), Tetris::RIGHT_WALL);
				if (this->pGame->getRPedal().movePedalX(-1) == Pedal::RIGHT_LOST) {
					this->endGame("right player lost");
					break;
				}
			}
			else {
				checkAndHandleUnRegularBallPedalCross(Tetris::RIGHT_WALL, ballLocationState);
			}
		}
		if (this->pGame->getStatus() == Game::PAUSED) {

			system("cls");
			break;
		}
		Sleep(Game::gameDifficulty);
		if (rightPedalAfterBomb || leftPedalAfterBomb) {
			delayCounter++;
		}
	}
}
// presents the keys and instructions
void MainMenu::presentInstructions() {
	system("cls");
	this->printAsciiArt();
	setColor(COLOR::TEAL_TEXT);
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y);
	cout << "Welcome to Noam&Noam's Tong project game";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 2);
	cout << "Press ESC to go back to Main Menu";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 4);
	cout << "In game Buttons: ";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 5);
	cout << "Press ESC at any time to pause";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 7);
	cout << "Left player : a/A button - DOWN";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 8);
	cout << "q/Q - UP";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 10);
	cout << "Right player : l/L button - DOWN";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 11);
	cout << "p/P - UP";
	gotoxy(BUTTONS_X, BUTTONS_TOP_Y + 13);
	cout << "Dont forget to enjoy !!";
	while (true) {
		if (_kbhit) {
			char ch = _getch();
			if (ch == KeyboardManager::ESC) {
				system("cls");
				this->printButtons();
				break;
			}
		}
	}
	setColor(COLOR::WHITE_TEXT);
}
// prints the buttons
void MainMenu::printButtons() {

	for (const Button& b : this->buttons) {
		b.print();
	}
	this->printAsciiArt();
}