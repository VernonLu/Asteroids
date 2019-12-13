#include "Aircraft.h"

void Aircraft::SetShieldTexture(sf::Texture& texture) {
	shieldSprite.setTexture(texture);
	sf::Vector2u texSize = texture.getSize();
	shieldSprite.setOrigin(texSize.x / 2, texSize.y / 2);
	shieldSprite.setScale((radius+5) / texSize.x * 2, (radius+5) / texSize.y * 2);
}

void Aircraft::UpdateSpriteSize() {
	if (sprite.getTexture() == NULL) { return; }
	sf::Vector2u texSize = sprite.getTexture()->getSize();
	sprite.setOrigin(texSize.x / 2, texSize.y / 2);
	sf::Vector2f scale(radius / texSize.x * 2, radius / texSize.y * 2);
	sprite.setScale(scale);
}

Aircraft::Aircraft() {
	tag = TAG::Aircraft;
	enable = true;
	SetRadius(30);
	SetForce(100);
	SetHeading(270);
	SetRotateSpeed(240);
	velocity = sf::Vector2f(0, 0);
	thrustSound.setLoop(true);
	sprite.setPosition(1, 1);
	boundary = sf::Vector2f(1366, 768);

	for (int i = 0; i < 100; ++i) {
		Particle* particle = new Particle();
		particle->SetLifetime(0.2);
		particle->SetSpeed(400);
		particle->SetColor(sf::Color(255, 139, 2));
		particle->EnableFade();
		flame.push_back(particle);
	}
}

Aircraft::~Aircraft() {}

void Aircraft::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!enable) { return; }
	if (!showSprite) { return; }
	target.draw(sprite);
	for (auto particle : flame) {
		if (particle->isDead) continue;
		target.draw(*particle);
	}
	if (isShieldActive) {
		target.draw(shieldSprite);
	}
}

void Aircraft::SetRadius(float radius) {
	this->radius = radius;
	UpdateSpriteSize();
}


float Aircraft::GetRadius() {
	return radius;
}

void Aircraft::SetPosition(sf::Vector2f position) {
	this->position = position;
	sprite.setPosition(position);
}

void Aircraft::SetPosition(float x, float y) {
	position = sf::Vector2f(x, y);
	sprite.setPosition(position);
}

sf::Vector2f Aircraft::GetPosition() {
	return position;
}


void Aircraft::SetHeading(float angle) {
	headingAngle = angle;
	sprite.setRotation(headingAngle);
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


void Aircraft::SetThrustSound(sf::SoundBuffer& sound) {
	thrustSound.setBuffer(sound);
}

void Aircraft::SetBulletSound(sf::SoundBuffer& sound) {
	bulletSound.setBuffer(sound);
}

void Aircraft::SetExplosionSound(sf::SoundBuffer& sound) {
	explosionSound.setBuffer(sound);
}

void Aircraft::SetBulletPool(std::vector<Bullet*>* bulletPool) {
	this->bulletPool = bulletPool;
}

void Aircraft::SetBoundary(sf::Vector2f boundary) {
	this->boundary = boundary;
}

void Aircraft::SetBoundary(float x, float y) {
	boundary = sf::Vector2f(x, y);
}

sf::Vector2f Aircraft::GetBoundary() {
	return boundary;
}

void Aircraft::Move(float dt) {
	position += velocity * dt;
	sprite.move(velocity * dt);

	if (velocity.x > 0 && position.x > boundary.x + radius * 2) {
		position.x -= boundary.x + radius * 2;
		sprite.setPosition(position);
	}
	if (velocity.x < 0 && position.x < -radius * 2) {
		position.x += boundary.x + radius * 4;
		sprite.setPosition(position);
	}

	if (velocity.y > 0 && position.y > boundary.y + radius * 2) {
		position.y -= boundary.y + radius * 4;
		sprite.setPosition(position);
		
	}
	if (velocity.y < 0 && position.y < -radius * 2) {
		position.y += boundary.y + radius * 4;
		sprite.setPosition(position);
	}
}

void Aircraft::Enable() {
	enable = true;
	invincibleTimeLeft = invincibleTime;
	flashTimer = 0;
}

void Aircraft::Accelerate(float dt) {
	sf::Vector2f front(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180));
	sf::Vector2f left(cos((headingAngle + 90) * 3.14 / 180), sin((headingAngle + 90) * 3.14 / 180));
	velocity += front * force * dt;
	for (auto particle : flame) {
		if (particle->isDead) {
			particle->SetDirection(-front);
			particle->setPosition(position - front * radius  + left * (float)(rand() % 10 - 5));
			particle->Enable();
			break;
		}
	}
}

void Aircraft::RotateLeft(float dt) {
	float rotation = -rotateSpeed * dt;

	sprite.rotate(rotation);

	headingAngle = sprite.getRotation();
}

void Aircraft::RotateRight(float dt) {

	float rotation = rotateSpeed * dt;

	sprite.rotate(rotation);

	headingAngle = sprite.getRotation();
	
}

void Aircraft::Attack() {

	if (lastShootTime < shootInterval) { return; }

	for (auto bullet : (*bulletPool)) {
		if (bullet->enable) { continue; }
		bulletSound.play();
		bullet->SetHeading(headingAngle);
		bullet->SetPosition(sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * 20.f + position);
		bullet->enable = true;
		break;
	}
	lastShootTime = 0;
}

void Aircraft::Update(float dt) {

	if (invincibleTimeLeft > 0) { 
		invincibleTimeLeft -= dt; 
		flashTimer += dt;
		if (flashTimer > flashDuration) {
			showSprite = !showSprite;
			flashTimer = 0;
		}
	}
	else {
		showSprite = true;
	}

	Move(dt);

	for (auto particle : flame) {
		particle->Update(dt);
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		RotateLeft(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		RotateRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Accelerate(dt);
		if (thrustSound.getStatus() != sf::SoundSource::Status::Playing) {
			thrustSound.play();
		}
	}
	else {
		thrustSound.pause();
	}

	lastShootTime += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Attack();
	}
	if (isShieldActive) {
		shieldSprite.setPosition(position);
	}

}

void Aircraft::Collide(GameObject& other) {
	switch (other.tag) {
	case TAG::Asteroid: {
		if (invincibleTimeLeft > 0) { return; }
		if (isShieldActive) {
			isShieldActive = false;
			velocity = -velocity;
			return;
		}
		explosionSound.play();
		enable = false;
	} break;
	case TAG::ShieldPowerUp: {
		isShieldActive = true;
	} break;
	default:
		break;
	}
}

