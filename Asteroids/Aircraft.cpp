#include "Aircraft.h"

void Aircraft::UpdateSpriteSize() {
	if (getTexture() == NULL) { return; }
	sf::Vector2u texSize = getTexture()->getSize();
	setOrigin(texSize.x / 2, texSize.y / 2);
	sf::Vector2f scale(radius / texSize.x, radius / texSize.y);
	setScale(scale);
}

Aircraft::Aircraft() {
	radius = 1;
	headingAngle = 0;
	speed = 0;
	rotateSpeed = 0;
	setPosition(1, 1);
}

Aircraft::~Aircraft() {}

void Aircraft::SetRadius(float radius) {
	this->radius = radius;
	UpdateSpriteSize();
}


float Aircraft::GetRadius() {
	return radius;
}

void Aircraft::SetSpeed(float speed) {
	this->speed = speed;
}

float Aircraft::GetSpeed() {
	return speed;
}

void Aircraft::SetHeading(float angle) {
	headingAngle = angle;
	setRotation(headingAngle);
}

float Aircraft::GetHeading() {
	return headingAngle;
}

void Aircraft::SetForce(float force) {
	this->force = force;
}

float Aircraft::GetForce() {
	return force;
}

void Aircraft::SetRotateSpeed(float angle) {
	this->rotateSpeed = angle;
}

float Aircraft::GetRotateSpeed() {
	return rotateSpeed;
}

void Aircraft::SetTexture(sf::Texture& texture) {
	setTexture(texture);
	UpdateSpriteSize();
}



void Aircraft::Move(float dt) {

	move(velocity * dt);
	//move(sf::Vector2f(cos(headingAngle *3.14 / 180), sin(headingAngle * 3.14 / 180)) * speed * dt);
}


void Aircraft::RotateLeft(float dt) {
	float rotation = -rotateSpeed * dt;

	rotate(rotation);

	headingAngle = getRotation();
}

void Aircraft::RotateRight(float dt) {

	float rotation = rotateSpeed * dt;

	rotate(rotation);

	headingAngle = getRotation();
	
}

void Aircraft::Accelerate(float dt) {
	velocity += sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * force * dt;
}
