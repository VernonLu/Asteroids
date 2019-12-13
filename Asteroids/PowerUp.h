#pragma once

#include "GameObject.h"

class PowerUp : public GameObject {
public:

	sf::Sound collectSound;
	PowerUp(TAG type = TAG::ShieldPowerUp);
	~PowerUp();

	void SetPosition(sf::Vector2f pos);

	void SetSoundBuffer(sf::SoundBuffer& buffer);

	void Update(float dt);

	void Collide(GameObject& other);

};