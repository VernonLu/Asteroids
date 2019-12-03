#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <vector>

using namespace sf;

class ParticleSystem {
private:
	//Container
	std::vector<Particle*> particlePool;

	//Particle Generation Center
	Vector2f position;

	//Existing Time
	float lifetime;

	//Existed time
	float time;

	//Particle Number
	int count;

	//Particle Speed
	float speed;
	
public:
	bool isDead = false;

	ParticleSystem(Vector2f pos, float lifetime, int count = 20);

	~ParticleSystem();

	void SetSpeed(float speed);
	
	void Update(float dt);

	void Draw(RenderWindow& window);

	void Restart();

};
