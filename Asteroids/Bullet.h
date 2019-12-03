#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>
class Bullet : public GameObject{
public:
	float headingAngle;

	Bullet();

	~Bullet();

	/*Getters and Setters*/
	void SetHeading(float angle);
	float GetHeading();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetTexture(sf::Texture& texture);

	void Move(float dt);
	
	void Disable();

	void Update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};