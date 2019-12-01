#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Bullet : public sf::CircleShape{
private:
	bool enabled;

	float headingAngle;

	float speed;

public:
	Bullet();
	~Bullet();
	void Move(float dt);


	void Start();
	void Update(float dt);

};