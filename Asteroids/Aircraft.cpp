#include "Aircraft.h"

Aircraft::Aircraft() {}

Aircraft::~Aircraft() {}

void Aircraft::SetSize(sf::Vector2f size) {
	this->size = size;
}

void Aircraft::SetSize(float x, float y) {
	size = sf::Vector2f(x, y);
}

sf::Vector2f Aircraft::GetSize() {
	return size;
}

void Aircraft::SetDirection(float angle) {
	headingAngle = angle;
}

sf::Vector2f Aircraft::GetDirection() {
	return sf::Vector2f(cos(headingAngle), sin(headingAngle));
}

void Aircraft::Move(float dt) {
	move(sf::Vector2f(cos(headingAngle), sin(headingAngle) * speed * dt));
}
