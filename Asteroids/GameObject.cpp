#include "GameObject.h"

void GameObject::SetTexture(sf::Texture& texture) {
	sf::Vector2u texSize = texture.getSize();
	sprite.setTexture(texture);
	sprite.setOrigin(texSize.x / 2, texSize.y / 2);
	sprite.setScale(radius / texSize.x * 2, radius / texSize.y * 2);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void GameObject::Destroy() {
}

void GameObject::Collide(GameObject& other) {
	
}