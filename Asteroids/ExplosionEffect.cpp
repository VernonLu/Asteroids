#include "ExplosionEffect.h"


ExplosionEffect::ExplosionEffect() {
	enable = false;
	maxCount = 5;
	lifeTime = 2;
	for (int i = 0; i < maxCount; ++i) {
		sf::CircleShape* shape = new sf::CircleShape(5);
		shape->setFillColor(sf::Color::Transparent);
		shape->setOutlineColor(sf::Color::White);
		shape->setOutlineThickness(1);
		shapes.push_back(shape);
	}
}

ExplosionEffect::~ExplosionEffect() {

}

void ExplosionEffect::Enable() {
	enable = true;
	timer = 0;
}

void ExplosionEffect::SetPosition(sf::Vector2f position) {
	for (auto shape : shapes) {
		shape->setPosition(position);
	}
}


void ExplosionEffect::Update(float dt) {
	timer += dt;
	if (timer > lifeTime) {
		enable = false;
	}
	int count = 0;
	for (auto shape : shapes) {
		float radius = timer * count++ * 10;
		shape->setOrigin(radius , radius);
		shape->setRadius(radius);
	}
}

void ExplosionEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto shape : shapes) {
		target.draw((*shape));
	}
}