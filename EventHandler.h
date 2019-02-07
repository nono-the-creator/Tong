#pragma once
class EventHandler {
public:
	virtual void handleKey(char ch) = 0;
	virtual std::string getKbChars() = 0;
};