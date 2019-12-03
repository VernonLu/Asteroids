#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject : public sf::Drawable {
protected:

public:

	bool enable;

	float radius;

	sf::Sprite sprite;

	sf::Vector2f position;

	float rotation;

	sf::Vector2f direction;

	float speed;

	sf::Color color;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual bool Collide(GameObject& other);
	
	virtual void Update(float dt) = 0;
};