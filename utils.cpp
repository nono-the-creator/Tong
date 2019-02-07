#include "utils.h"
using namespace std;
BOOL gotoxy(const WORD x, const WORD y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void setCursorOff() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = 0; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void setColor(COLOR color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// pick the colorattribute
	SetConsoleTextAttribute(hConsole, (int)color);
}
void printTitle(const Position& p, string text) {
	gotoxy(p.getX() - text.length() / 2, p.getY());
	setColor(COLOR::YELLOW_TEXT);
	cout << text;
	setColor(COLOR::WHITE_TEXT);
}
