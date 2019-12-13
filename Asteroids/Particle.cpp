#include "Particle.h"

Particle::Particle() {
	isDead = true;

	lifeTime = 0;

	time = 0;

	speed = 0;

	direction = sf::Vector2f(0, 0);

	fade = false;

	color = sf::Color::White;

	setRadius(2);
	setOrigin(1, 1);
	setFillColor(color);
	setPosition(sf::Vector2f(0, 0));
}

Particle::~Particle() {
	delete this;
}

void Particle::Update(float dt) {
	time -= dt;
	move(direction * speed * dt);
	if (fade) {
		sf::Color newColor = color;
		//newColor.r = (time > 0) ? (sf::Uint8)(time/ lifeTime * color.r) : 0;
		newColor.g = (time > 0) ? (sf::Uint8)((lifeTime - time) / time  * color.g) : 0;
		newColor.b = (time > 0) ? (sf::Uint8)(lifeTime / time * color.b) : 0;
		newColor.a = (time > 0) ? (sf::Uint8)(time / lifeTime * color.a) : 0;
		setFillColor(newColor);
	}
	if (time <= 0) { isDead = true; }
}

void Particle::SetRadius(float radius) {
	setRadius(radius);
	setOrigin(radius, radius);
}

void Particle::SetLifetime(float lifeTime) {
	this->lifeTime = lifeTime;
}

void Particle::SetSpeed(float speed) {
	this->speed = speed;
}

void Particle::SetDirection(sf::Vector2f direction) {
	this->direction = direction;
}

void Particle::SetColor(sf::Color color) {
	this->color = color;
	setFillColor(color);
}

void Particle::EnableFade() {
	fade = true;
}

void Particle::DisableFade() {
	fade = false;
}

void Particle::Enable() {
	time = lifeTime;
	isDead = false;
}
