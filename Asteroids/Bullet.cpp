#include "Bullet.h"

Bullet::Bullet() {
	enabled = false;
	headingAngle = 0;
	speed = 0;
	setRadius(3);
	setFillColor(sf::Color::Yellow);
	setPosition(-10, -10);
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

float Bullet::GetSped() {
	return speed;
}


void Bullet::Move(float dt) {
	move(sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * speed * dt);
}

void Bullet::Update(float dt) {
	Move(dt);
}


