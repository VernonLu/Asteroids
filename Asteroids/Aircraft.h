#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Aircraft : public sf::Sprite {
private:
	float radius;
	
	float force;

	sf::Vector2f velocity;

	float headingAngle;
	
	float rotateSpeed;

	sf::Sound thrustSound;

	void UpdateSpriteSize();

public:
	Aircraft();
	~Aircraft();

	void SetRadius(float radius);
	float GetRadius();

	void SetHeading(float angle);
	float GetHeading();

	void SetForce(float force);
	float GetForce();

	void SetRotateSpeed(float angle);
	float GetRotateSpeed();

	void SetTexture(sf::Texture& texture);

	void SetThrustSound(sf::SoundBuffer& sound);

	void Accelerate(float dt);

	void Move(float dt);

	void RotateLeft(float dt);
	void RotateRight(float dt);		

	void Attack();

	void Update(float dt);

	void Destroy();
};
