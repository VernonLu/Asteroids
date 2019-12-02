#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Bullet.h"

class Aircraft : public sf::Drawable {
private:

	sf::Sprite aircraft;

	float radius;

	sf::Vector2f position;
	
	float headingAngle;
	
	float force;

	sf::Vector2f velocity;
	
	float rotateSpeed;

	sf::Sound thrustSound;

	sf::Sprite flame;

	std::vector<Bullet*>* bulletPool;

	float shootInterval = 0.1f;

	float lastShootTime = 0;

	void UpdateSpriteSize();

public:
	Aircraft();
	~Aircraft();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*Getters and Setters*/
	void SetRadius(float radius);
	float GetRadius();

	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition();

	void SetHeading(float angle);
	float GetHeading();

	void SetForce(float force);
	float GetForce();

	void SetRotateSpeed(float angle);
	float GetRotateSpeed();

	void SetTexture(sf::Texture& texture);

	void SetFlameTexture(sf::Texture& texture);

	void SetThrustSound(sf::SoundBuffer& sound);

	void SetBulletPool(std::vector<Bullet*>* bulletPool);

	/* Member functions*/
	void Accelerate(float dt);

	void Move(float dt);

	void RotateLeft(float dt);
	
	void RotateRight(float dt);		

	void Attack();

	void Update(float dt);
};
