#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Bullet : public sf::CircleShape{
private:

	float headingAngle;

	float speed;

public:
	bool enabled;

	Bullet();

	~Bullet();

	/*Getters and Setters*/
	void SetHeading(float angle);
	float GetHeading();

	void SetSpeed(float speed);
	float GetSpeed();

	void Move(float dt);
	
	void Disable();

	void Update(float dt);
};