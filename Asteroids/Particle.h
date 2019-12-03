#pragma once
#include <SFML/Graphics.hpp>

class Particle : public sf::CircleShape {
private:

	//How long the particle has exised
	float time;

	//Existing Time
	float lifeTime;

	//Particle move speed;
	float speed;

	//Whether the particle will fade
	bool fade;

	//Particle move direction
	sf::Vector2f direction;

	//Particle Color
	sf::Color color;

public:

	bool isDead = false;

	Particle();

	~Particle();

	void Update(float dt);

	void SetRadius(float radius);

	void SetLifetime(float lifeTime);

	void SetSpeed(float speed);

	void SetDirection(sf::Vector2f direction);

	void SetColor(sf::Color color);

	void EnableFade();
	void DisableFade();

	void Enable();
};