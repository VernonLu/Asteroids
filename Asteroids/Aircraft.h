#pragma once
#include "GameObject.h"

#include <SFML/Audio.hpp>
#include <vector>

#include "Bullet.h"
#include "Particle.h"


class Aircraft : public GameObject {
public:
	float headingAngle;

	float force;

	sf::Vector2f velocity;

	float rotateSpeed;

	sf::Sound thrustSound;

	std::vector<Bullet*>* bulletPool;

	float shootInterval = 0.2f;

	float lastShootTime = 0;

	sf::Vector2f boundary;

	std::vector<Particle*> flame;

	void UpdateSpriteSize();

	Aircraft();
	~Aircraft();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

	void SetThrustSound(sf::SoundBuffer& sound);

	void SetBulletPool(std::vector<Bullet*>* bulletPool);

	void SetBoundary(sf::Vector2f boundary);
	void SetBoundary(float x, float y);
	sf::Vector2f GetBoundary();

	/* Member functions*/
	void Accelerate(float dt);

	void Move(float dt);

	void RotateLeft(float dt);
	
	void RotateRight(float dt);		

	void Attack();

	void Update(float dt);
};
