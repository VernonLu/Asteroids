#include "GameObject.h"

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

bool GameObject::Collide(GameObject& other) {
	sf::Vector2f diff = position - other.position;

	float distance2 = pow(diff.x, 2) + pow(diff.y, 2);

	return distance2 <= pow((radius + other.radius), 2);
}
