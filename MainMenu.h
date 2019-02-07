#pragma once
#include <vector>
#include "Button.h"
#include "Tile.h"
#include <conio.h>
#include "utils.h"
#include "game.h"
#include "EventHandler.h"
#include <cwchar>
#include "StartNewGameMenu.h"

using namespace std;

class MainMenu : public EventHandler {
private:
	std::string kbChars;
	std::vector<Button> buttons;
	Game* pGame; // the current running game
	int findClickable();
	void exitGame() {
		exit(0);
	}
	// sets game difficulty
	void setDifficulty(int i) {
		int diffs[] = { 60, 40 ,20 };
		Game::gameDifficulty = diffs[i];
	}
	// prints the initial arena and pedals
	void printInitialziedGame(Game* game) {
		setColor(COLOR::TEAL_FADE_BACKGROUND);
		game->getArena().printArena();
		setColor(COLOR::RED_FADE_TEXT);
		setColor(COLOR::WHITE_TEXT);
		setColor(COLOR::RED_TEXT);
		game->getLPedal().PrintPedal();
		game->getRPedal().PrintPedal();
		setColor(COLOR::WHITE_TEXT);
		game->getBall().setDirX((rand() % 2) == 0 ? -1 : 1);
		game->getBall().setDirY((rand() % 2) == 0 ? -1 : 1);

	}
	void printScore() {
		setColor(COLOR::RED_TEXT);
		gotoxy(Arena::MIN_X, 2);
		cout << "       " ;
		gotoxy(Arena::MIN_X, 2);
		cout << "Life: " << Pedal::LEFT_LOST - this->pGame->getLPedal().getBody().front().getPosition().getX();
		gotoxy(Arena::MAX_X - 7 , 2);
		cout << "       " ;
		gotoxy(Arena::MAX_X - 7, 2);
		cout << "Life: " <<  this->pGame->getRPedal().getBody().front().getPosition().getX() - Pedal::RIGHT_LOST;
		setColor(COLOR::WHITE_TEXT);
	}
	// statrs a new game
	void startNewGame() {
		if (this->pGame != NULL) {
			delete this->pGame;
		}
		system("cls");
		StartNewGameMenu newGameMenu;
		if (newGameMenu.showUntilEscOrNewGame(pGame)) {
			system("cls");
			gameLoop();
		}
		this->printButtons();
	}
	// resumes an existing game
	void resumeGame() {
		if (this->pGame != NULL && this->pGame->getStatus() != Game::OVER) {
			this->pGame->setStatus(Game::ONGOING);
			this->pGame->getBall().locateAtCenter();
			system("cls");
			gameLoop();
			this->printButtons();
		}
		else {
			gotoxy(BUTTONS_X, BUTTONS_TOP_Y + BUTTONS_MARGIN_Y + 1);
			std::cout << "    No Game To Resume";
			Sleep(400);
			gotoxy(BUTTONS_X, BUTTONS_TOP_Y + BUTTONS_MARGIN_Y + 1);
			std::cout << "                      ";
		}
	}
	void gameLoop();
	// prints the ascii art at the main menu
	void printAsciiArt() {
		setColor(COLOR::YELLOW_TEXT);
		gotoxy(35, 0);
		cout << " ________   ______   __    __   ______   ";
		gotoxy(35, 1);
		cout << "|        \ /      \ |  \  |  \ /      \  ";
		gotoxy(35, 2);
		cout << " \ $$$$$$$|  $$$$$$\|   $$\ | $$|  $$$$$$\ ";
		gotoxy(35, 3);
		cout << "   | $$  | $$   | $$| $$$\| $$| $$ __\$$  ";
		gotoxy(35, 4);
		cout << "   | $$  | $$   | $$| $$$$\ $$| $$|    \ ";
		gotoxy(35, 5);
		cout << "   | $$  | $$   | $$| $$\$$ $$| $$ \$$$$";
		gotoxy(35, 6);
		cout << "   | $$  | $$__/  $$| $$ \$$$$| $$__| $$";
		gotoxy(35, 7);
		cout << "   | $$    \$$     $$| $$  \$$$  \$$    $$";
		gotoxy(35, 8);
		cout << "     \$$     \$$$$$$    \$$   \$$  \$$$$$$ ";
		setColor(COLOR::RED_TEXT);

		gotoxy(80, 10);
		cout << "          ,;;;!!!!!;;.";
		gotoxy(80, 11);
		cout << "        :!!!!!!!!!!!!!!;";
		gotoxy(80, 12);
		cout << "      :!!!!!!!!!!!!!!!!!;";
		gotoxy(80, 13);
		cout << "     ;!!!!!!!!!!!!!!!!!!!;";
		gotoxy(80, 14);
		cout << "    ;!!!!!!!!!!!!!!!!!!!!!";
		gotoxy(80, 15);
		cout << "    ;!!!!!!!!!!!!!!!!!!!!'";
		gotoxy(80, 16);
		cout << "    ;!!!!!!!!!!!!!!!!!!!'";
		gotoxy(80, 17);
		cout << "     :!!!!!!!!!!!!!!!!'";
		gotoxy(80, 18);
		cout << "      ,!!!!!!!!!!!!!''";
		gotoxy(80, 19);
		cout << "   ,;!!!''''''''''";
		gotoxy(80, 20);
		cout << " .!!!!'";
		gotoxy(80, 21);
		cout << "!!!!`";
		setColor(COLOR::PINK_TEXT);

		gotoxy(1, 5);
		cout << " __________________________";
		gotoxy(1, 6);
		cout << "| .----------------------. |";
		gotoxy(1, 7);
		cout << "| |  .----------------.  | |";
		gotoxy(1, 8);
		cout << "| |  |                |  | |";
		gotoxy(1, 9);
		cout << "| |))|                |  | |";
		gotoxy(1, 10);
		cout << "| |  |                |  | |";
		gotoxy(1, 11);
		cout << "| |  |                |  | |";
		gotoxy(1, 12);
		cout << "| |  |                |  | |";
		gotoxy(1, 13);
		cout << "| |  |                |  | |";
		gotoxy(1, 14);
		cout << "| |  '----------------'  | |";
		gotoxy(1, 15);
		cout << "| |__TONG________________/ |";
		gotoxy(1, 16);
		cout << "|          ________        |";
		gotoxy(1, 17);
		cout << "|    _ (NOAM&NOAM)         |";
		gotoxy(1, 18);
		cout << "|  _| |_              .-.  |";
		gotoxy(1, 19);
		cout << "|-[_   _]-       .-. (   ) |";
		gotoxy(1, 20);
		cout << "|   |_|         (   ) '-'  |";
		gotoxy(1, 21);
		cout << "|    '           '-'   A   |";
		gotoxy(1, 22);
		cout << "|                 B        |";
		gotoxy(1, 23);
		cout << "|          ___   ___       |";
		gotoxy(1, 24);
		cout << "|         (___) (___)  ,., |";
		gotoxy(1, 25);
		cout << "|        select start ;:;: |";
		gotoxy(1, 26);
		cout << "|                    ,;:;' /";
		gotoxy(1, 27);
		cout << "|                   ,:;:'.'";
		gotoxy(1, 28);
		cout << " '-----------------------`";
		setColor(COLOR::WHITE_TEXT);
	}
	void presentInstructions();
	// a function that does basicly nothing when you try to press enter to change difficulty
	void doNothing() {
	}
	void endGame(string display) {
		this->pGame->setStatus(Game::OVER);
		system("cls");
		gotoxy(Arena::MAX_X / 2, Arena::MAX_Y / 2);
		cout << display;
		Sleep(1500);
		system("cls");
	}
	void checkAndHandleUnRegularBallPedalCross(int side, byte& ballState);

	//reduce moves the pedal towards the center and increase moves the pedal backwords 
	void handleScore(int side, int action) {
		if (action == Pedal::REDUCE_SCORE) {
			if (side == Tetris::LEFT_WALL) {
				this->pGame->getLPedal().movePedalX(1);
			}
			if (side == Tetris::RIGHT_WALL) {
				this->pGame->getRPedal().movePedalX(-1);
			}
		}
		if (action == Pedal::INCREASE_SCORE) {
			if (side == Tetris::LEFT_WALL) {
				this->pGame->getLPedal().movePedalX(-1);
			}
			if (side == Tetris::RIGHT_WALL) {
				this->pGame->getRPedal().movePedalX(1);
			}
		}
	}
public:
	enum { BUTTONS_X = 40, BUTTONS_TOP_Y = 12, BUTTONS_MARGIN_Y = 4, PAUSE_GAME = 1 };
	MainMenu() {
		buttons.push_back({ { "Start New Game" },{ BUTTONS_X, BUTTONS_TOP_Y },
						0, std::bind(&MainMenu::startNewGame, this) });
		buttons.at(0).setClickable(true);
		buttons.push_back({ { "Continue A Paused Game" },{ BUTTONS_X, BUTTONS_TOP_Y + Button::getCount() * BUTTONS_MARGIN_Y},
						0, std::bind(&MainMenu::resumeGame, this) });
		buttons.push_back({ { "Set Difficulty : SLOW" },{ BUTTONS_X, BUTTONS_TOP_Y + Button::getCount() * BUTTONS_MARGIN_Y },
						0, std::bind(&MainMenu::doNothing, this) });
		buttons.push_back({ { "Present Instructions And Keys" },{ BUTTONS_X, BUTTONS_TOP_Y + Button::getCount() * BUTTONS_MARGIN_Y},
						0, std::bind(&MainMenu::presentInstructions, this) });
		buttons.push_back({ { "EXIT" },{ BUTTONS_X, BUTTONS_TOP_Y + Button::getCount() * BUTTONS_MARGIN_Y },
						0, std::bind(&MainMenu::exitGame, this) });
		this->kbChars.push_back((char)KeyboardManager::UP_BUTTON);
		this->kbChars.push_back((char)KeyboardManager::DOWN_BUTTON);
		this->kbChars.push_back((char)KeyboardManager::RIGHT_BUTTON);
		this->kbChars.push_back((char)KeyboardManager::LEFT_BUTTON);
		this->kbChars.push_back((char)KeyboardManager::ENTER_BUTTON);
		this->pGame = NULL;
	}
	void printButtons();

	Game* getGame() {
		return this->pGame;
	}

	void setGame(Game* pGame) {
		this->pGame = pGame;
	}

	void handleKey(char ch) override {
		std::string diffs[3] = { "SLOW", "MEDIUM", "FAST" }; // possible speeds
		static int i = 0;
		int currentClickable = findClickable();
		switch (ch) {
		case KeyboardManager::UP_BUTTON:
			this->buttons.at(currentClickable).deleteText();
			this->buttons.at(currentClickable).setClickable(false);
			this->buttons.at(currentClickable).print();
			if (currentClickable == 0) {
				currentClickable = this->buttons.size();
			}
			this->buttons.at(currentClickable - 1).setClickable(true);
			this->buttons.at(currentClickable - 1).print();
			break;
		case KeyboardManager::DOWN_BUTTON:
			this->buttons.at(currentClickable).deleteText();
			this->buttons.at(currentClickable).setClickable(false);
			this->buttons.at(currentClickable).print();
			this->buttons.at((currentClickable + 1) % this->buttons.size()).setClickable(true);
			this->buttons.at((currentClickable + 1) % this->buttons.size()).print();
			break;
		case KeyboardManager::LEFT_BUTTON:
			if (currentClickable == 2) {
				if (i != 0) {
					i--;
					this->buttons.at(currentClickable).deleteText();
					buttons.at(currentClickable).setText("Set Difficulty : " + diffs[i]);
					buttons.at(currentClickable).setClickable(true);
					this->setDifficulty(i);
				}
			}
			this->buttons.at(currentClickable).print();
			break;
		case KeyboardManager::RIGHT_BUTTON:
			if (currentClickable == 2) {
				if (i != 2) {
					i++;
					this->buttons.at(currentClickable).deleteText();
					buttons.at(currentClickable).setText("Set Difficulty : " + diffs[i]);
					buttons.at(currentClickable).setClickable(true);
					this->setDifficulty(i);
				}
			}
			this->buttons.at(currentClickable).print();
			break;
		case KeyboardManager::ENTER_BUTTON:
			this->buttons.at(currentClickable).onAction();

		default: break;
		}
	}
	std::string getKbChars() override {
		return this->kbChars;
	}
};