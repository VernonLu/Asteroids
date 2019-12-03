#include "Asteroid.h"

Asteroid::Asteroid() {
	radius = 30;
	sprite.setPosition(100, 100);
}

Asteroid::~Asteroid() {
}

void Asteroid::SetTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
	sf::Vector2u texSize = texture.getSize();
	sprite.setScale(radius / texSize.x, radius / texSize.y);
	sprite.setOrigin(radius, radius);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void Asteroid::Update(float dt) {
}
