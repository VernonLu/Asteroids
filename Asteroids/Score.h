#pragma once
#include <SFML/Graphics.hpp>

class Score :public sf::Text {
public:
	Score();
	~Score();
	int operator=(const int& v);
	int operator+=(const int& v);
	bool operator >= (const int& v);
	bool operator == (const int& v);
private:
	int value;
};
