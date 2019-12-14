#include "Asteroid.h"

Asteroid::Asteroid(int life) {
	tag = TAG::Asteroid;
	this->life = life;
	radius = life * 5 + 15;
}

Asteroid::~Asteroid() {
}

void Asteroid::SetLife(int value) {
	life = value;
	SetRadius(radius = life * 5 + 15);
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

void Asteroid::SetBuffer(sf::SoundBuffer& buffer) {
	sound.setBuffer(buffer);
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

void Asteroid::SetRadius(float value) {
	radius = value;
	sf::Vector2u texSize = sprite.getTexture()->getSize();
	sprite.setScale(radius / texSize.x * 2, radius / texSize.y * 2);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void Asteroid::Update(float dt) {
	Move(dt);
	Rotate(dt);
}

void Asteroid::Collide(GameObject& other) {
	for (auto effect : (*effectContainer)) {
		if (!effect->enable) {
			effect->SetPosition(position);
			effect->Enable();
			break;
		}
	}
	switch (other.tag) {
	case TAG::Asteroid: {
		sound.play();
		sf::Vector2f force = position - other.position;
		direction = (force + direction * speed) / (speed + radius);
	} break;
	case TAG::Aircraft: {
		sound.play();
		sf::Vector2f diff = position - other.position;
		SetDirection(diff.x, diff.y);
	} break;
	case TAG::Bullet: {
		sound.play();
		Destroy();
	} break;
	default:
		break;
	}
}

void Asteroid::Destroy() {
	--life;
	++(*playerScore);
	if (life > 0) {
		radius = life * 5 + 15;
		SetRadius(radius);
		direction = sf::Vector2f(-direction.y, direction.x);
		//Generate New Small
		for (auto asteroid : (*container)) {
			if (!asteroid->enable) {
				asteroid->life = life;
				asteroid->SetRadius(radius);
				asteroid->direction = -direction;
				asteroid->SetPosition(-direction * radius + position); 
				asteroid->enable = true;
				break;
			}
		}
		SetPosition(direction * radius + position);
	}
	else {
		int dice = rand() % 10 ;
		if (dice > 7) {

			int index = rand() % 2;
			auto p = (*powerUpContainer)[index];
			if (!p->enable) {
				p->SetPosition(position);
				p->enable = true;
			}
		}
		enable = false;
	}
}
