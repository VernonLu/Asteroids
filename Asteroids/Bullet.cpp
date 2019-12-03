#include "Bullet.h"

Bullet::Bullet() {
	enable = false;
	headingAngle = 0;
	speed = 500;
	radius = 16;
	color = sf::Color::Yellow;
	sprite.setPosition(-10, -10);
}

Bullet::~Bullet() {}

void Bullet::SetHeading(float angle) {
	headingAngle = angle;
}

float Bullet::GetHeading() {
	return headingAngle;
}

void Bullet::SetSpeed(float speed) {
	this->speed = speed;
}

float Bullet::GetSpeed() {
	return speed;
}

void Bullet::SetTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
	sf::Vector2u texSize = texture.getSize();
	sprite.setScale(radius / texSize.x, radius / texSize.y);
	sprite.setOrigin(radius, radius);
}


void Bullet::Move(float dt) {
	sprite.move(sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * speed * dt);
}

void Bullet::Disable() {
	enable = false;
	position = sf::Vector2f(-99, -99);
}

void Bullet::Update(float dt) {
	Move(dt);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}


