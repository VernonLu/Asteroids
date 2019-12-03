#include "Asteroid.h"

Asteroid::Asteroid() {
	radius = 30;
	enable = true;
}

Asteroid::~Asteroid() {
}

void Asteroid::SetPosition(sf::Vector2f position) {
	this->position = position;
	sprite.setPosition(position);
}

void Asteroid::SetDirection(float x, float y) {
	if (x == 0 && y == 0) {
		direction = sf::Vector2f(0, 0);
		return;
	}
	float len = sqrt(x * x + y * y);
	direction = sf::Vector2f(x / len, y / len);
}

void Asteroid::SetTexture(sf::Texture& texture) {
	sf::Vector2u texSize = texture.getSize();
	sprite.setTexture(texture);
	sprite.setScale(radius / texSize.x * 2, radius / texSize.y * 2);
	sprite.setOrigin(radius, radius);
}

void Asteroid::Move(float dt) {
	
	sf::Vector2f velocity = direction * speed * dt;
	position += velocity;
	sprite.move(velocity);

	if (velocity.x > 0 && position.x > boundary.x + radius) {
		position.x -= boundary.x + radius * 2;
		sprite.setPosition(position);
	}
	if (velocity.x < 0 && position.x < -radius ) {
		position.x += boundary.x + radius * 2;
		sprite.setPosition(position);
	}

	if (velocity.y > 0 && position.y > boundary.y + radius ) {
		position.y = position.y - boundary.y - radius * 2;
		sprite.setPosition(position);

	}
	if (velocity.y < 0 && position.y < -radius) {
		position.y = position.y + boundary.y + radius * 2;
		sprite.setPosition(position);
	}
}

void Asteroid::Rotate(float dt) {
	sprite.rotate(rotateSpeed * dt);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void Asteroid::Update(float dt) {
	Move(dt);
	Rotate(dt);
}

void Asteroid::Collide(GameObject& other) {
	sf::Vector2f force = position - other.position;
	direction = (force + direction * speed) / (speed + radius) ;
}

void Asteroid::Destroy() {
	if (life > 0) {
		for (int i = 0; i < 2; ++i) {
			Asteroid* a = new Asteroid();
			container->push_back(a);
		}
	}
	enable = false;
}
