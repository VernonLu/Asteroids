#include "Bullet.h"

Bullet::Bullet() {
	tag = TYPE::Bullet;
	enable = false;
	headingAngle = 0;
	speed = 1000;
	radius = 10;
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

void Bullet::SetPosition(sf::Vector2f position) {
	this->position = position;
	sprite.setPosition(position);
}

void Bullet::SetPosition(float x, float y) {
	position = sf::Vector2f(x, y);
	sprite.setPosition(position);
}

void Bullet::Move(float dt) {
	sf::Vector2f velocity = sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * speed * dt;
	position += velocity;
	sprite.move(velocity);
}

void Bullet::Disable() {
	enable = false;
}

void Bullet::Update(float dt) {
	if (!enable) { return; }
	Move(dt);
	if (position.x < -radius * 2 ||
		position.x > boundary.x + radius * 2 ||
		position.y < -radius * 2 ||
		position.y > boundary.y + radius * 2) {
		enable = false;
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void Bullet::Collide(GameObject& other) {
	if (other.tag != TYPE::Asteroid) { return; }
	enable = false;
}


