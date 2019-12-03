#pragma once
#include "GameObject.h"

class Asteroid : public GameObject {
public:


	Asteroid();
	~Asteroid();

	void SetTexture(sf::Texture& texture);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Update(float dt);
};