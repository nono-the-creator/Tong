#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "utils.h"
#include <functional>
class Button {
private:
	std::string text;
	Position pos;
	bool isClickable; // indicates if the user can click the button
	static int count;	 // counts the bumber of buttons created
	std::function<void()> callBackFunction; // the function to be called when the user presses the button
public:
	Button(std::string text, Position pos, bool isClickable, std::function<void()> callBackFunction)
		: text(text), pos(pos), isClickable(isClickable) {
		count++;
		this->callBackFunction = callBackFunction;
	}
	// a function that prints the buttons
	void print() const {
		gotoxy(this->pos.getX(), this->pos.getY());
		if (this->isClickable) {
			setColor(COLOR::TEAL_TEXT);
		}
		else {
			setColor(COLOR::TEAL_FADE_TEXT);
		}
		std::cout << this->text;
		setColor(COLOR::WHITE_TEXT);
		
	}
	void setText(std::string text) {
		this->text = text;
	}
	void deleteText() {
		gotoxy(this->pos.getX(), this->pos.getY());
		for (int i = 0; i < this->text.size(); i++) {
			std::cout << ' ';
		}
	}
	static int getCount() {
		return count;
	}
	// sets the button clickability
	void setClickable(bool state) {
		this->isClickable = state;
		if (state) {
			this->text = ("--< " + text + " >--");
		}
		else {
			this->text.erase(0, 4);
			this->text.erase(this->text.size() - 4, this->text.size());
		}
	}
	bool getClickability() {
		return this->isClickable;
	}
	//envokes the action the button performs when pressed
	void onAction() {
		this->callBackFunction();
	}
};