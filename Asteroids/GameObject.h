#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject : public sf::Drawable {
protected:

public:

	bool enable;

	std::string tag;

	float radius;

	sf::Sprite sprite;

	sf::Vector2f position;

	float rotation;

	sf::Vector2f direction;

	float speed;

	sf::Color color;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void Collide(GameObject& other);

	virtual void Destroy();
	
	virtual void Update(float dt) = 0;
};