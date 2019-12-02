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
	float GetSped();

	void Move(float dt);
	
	void Update(float dt);



};