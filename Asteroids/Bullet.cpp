#include "Bullet.h"

Bullet::Bullet() {
	enabled = true;
	headingAngle = true;
	speed = 0;
}

Bullet::~Bullet() {}


void Bullet::Move(float dt) {
	move(sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * speed * dt);
}

void Bullet::Update(float dt) {
	Move(dt);
}
