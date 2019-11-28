#pragma once
#include <SFML/Graphics.hpp>
class Aircraft : public sf::Sprite {
private:
	sf::Vector2f size;

public:
	Aircraft();
	~Aircraft();
	void SetSize(sf::Vector2f size);
	void SetSize(float x, float y);
	sf::Vector2f GetSize();
	void Move(float dt);
};
