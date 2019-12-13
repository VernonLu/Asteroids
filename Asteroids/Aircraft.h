#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Particle.h"


class Aircraft : public GameObject {
private:
	float invincibleTimeLeft = 3.1f;

	float flashTimer = 0;

	bool showSprite = true;
public:

	float invincibleTime = 3.1f;

	float flashDuration = 0.1f;

	float headingAngle;

	float force;

	sf::Vector2f velocity;

	float rotateSpeed;

	sf::Sound thrustSound;

	sf::Sound bulletSound;

	sf::Sound explosionSound;

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

	void SetThrustSound(sf::SoundBuffer& sound);
	void SetBulletSound(sf::SoundBuffer& sound);
	void SetExplosionSound(sf::SoundBuffer& sound);

	void SetBulletPool(std::vector<Bullet*>* bulletPool);

	void SetBoundary(sf::Vector2f boundary);
	void SetBoundary(float x, float y);
	sf::Vector2f GetBoundary();

	/* Member functions*/
	void Enable();

	void Accelerate(float dt);

	void Move(float dt);

	void RotateLeft(float dt);
	
	void RotateRight(float dt);		

	void Attack();

	void Update(float dt);

	void Collide(GameObject& other);
};
