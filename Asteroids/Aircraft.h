#pragma once
#include <SFML/Graphics.hpp>
class Aircraft : public sf::Sprite {
private:
	float radius;

	float speed;

	sf::Vector2f direction;

	float force;

	sf::Vector2f velocity;

	float headingAngle;

	
	float rotateSpeed;

	void UpdateSpriteSize();

public:
	Aircraft();
	~Aircraft();
	void SetRadius(float radius);
	float GetRadius();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetHeading(float angle);
	float GetHeading();

	void SetForce(float force);
	float GetForce();

	void SetRotateSpeed(float angle);
	float GetRotateSpeed();

	void SetTexture(sf::Texture& texture);

	void Move(float dt);
	void RotateLeft(float dt);
	void RotateRight(float dt);
	void Accelerate(float dt);
		
};
