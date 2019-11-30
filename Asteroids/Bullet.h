#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Bullet : public sf::CircleShape{
private:
	bool enabled;
public:
	Bullet();
	~Bullet();


};

Bullet::Bullet() {
	enabled = true;
}

Bullet::~Bullet() {

}