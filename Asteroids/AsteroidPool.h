#pragma once
#include "GameObject.h"
#include "Asteroid.h"
#include <vector>
class AsteroidPool : public GameObject {
public:
	std::vector<Asteroid*> pool;

	AsteroidPool();
	~AsteroidPool();

	void Update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};