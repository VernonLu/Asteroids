#pragma once
#include <SFML/Graphics.hpp>
class Aircraft : public sf::Sprite {
private:
	float radius;

	float headingAngle;

	float speed;
	
	float rotateSpeed;

	void UpdateSpriteSize();

public:
	Aircraft();
	~Aircraft();
	void SetRadius(float radius);
	float GetRadius();
	void SetSpeed(float speed);
	float GetSpeed();
	void SetRotateSpeed(float angle);
	float GetRotateSpeed();
	void SetTexture(sf::Texture& texture);
	void SetDirection(float angle); 
	float GetDirection();
	void Move(float dt);
	void RotateLeft(float dt);
	void RotateRight(float dt);
};
