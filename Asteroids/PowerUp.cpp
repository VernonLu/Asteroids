#include "PowerUp.h"

PowerUp::PowerUp(TAG type) {
	enable = false;
	this->tag = type;
	radius = 20;
}

PowerUp::~PowerUp() {

}

void PowerUp::SetPosition(sf::Vector2f pos) {
	position = pos;
	sprite.setPosition(pos);
}

void PowerUp::SetSoundBuffer(sf::SoundBuffer& buffer) {
	collectSound.setBuffer(buffer);
}

void PowerUp::Update(float dt) {
}

void PowerUp::Collide(GameObject& other) {
	if (other.tag == TAG::Aircraft) {
		collectSound.play();
		this->enable = false;
	}
}
