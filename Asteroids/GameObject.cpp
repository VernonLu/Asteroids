#include "GameObject.h"

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void GameObject::Destroy() {
}

void GameObject::Collide(GameObject& other) {
}