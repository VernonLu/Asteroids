#include "Aircraft.h"
#include <iostream>
void Aircraft::UpdateSpriteSize() {
	if (aircraft.getTexture() == NULL) { return; }
	sf::Vector2u texSize = aircraft.getTexture()->getSize();
	aircraft.setOrigin(texSize.x / 2, texSize.y / 2);
	sf::Vector2f scale(radius / texSize.x, radius / texSize.y);
	aircraft.setScale(scale);
}

Aircraft::Aircraft() {
	destroied = false;
	SetRadius(50);
	SetForce(100);
	SetHeading(270);
	SetRotateSpeed(240);
	velocity = sf::Vector2f(0, 0);
	thrustSound.setLoop(true);
	aircraft.setPosition(1, 1);
	boundary = sf::Vector2f(1366, 768);
}

Aircraft::~Aircraft() {}

void Aircraft::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(aircraft);
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
	aircraft.setPosition(position);
}

void Aircraft::SetPosition(float x, float y) {
	position = sf::Vector2f(x, y);
	aircraft.setPosition(position);
}

sf::Vector2f Aircraft::GetPosition() {
	return position;
}


void Aircraft::SetHeading(float angle) {
	headingAngle = angle;
	aircraft.setRotation(headingAngle);
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

void Aircraft::SetTexture(sf::Texture& texture) {
	texture.generateMipmap();
	aircraft.setTexture(texture);
	UpdateSpriteSize();
}

void Aircraft::SetFlameTexture(sf::Texture& texture) {
	flame.setTexture(texture);
}

void Aircraft::SetThrustSound(sf::SoundBuffer& sound) {
	thrustSound.setBuffer(sound);
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
	aircraft.move(velocity * dt);

	if (velocity.x > 0 && position.x > boundary.x + radius * 2) {
		position.x -= boundary.x + radius * 4;
		aircraft.setPosition(position);
	}
	if (velocity.x < 0 && position.x < -radius * 2) {
		position.x += boundary.x + radius * 4;
		aircraft.setPosition(position);
	}

	if (velocity.y > 0 && position.y > boundary.y + radius * 2) {
		position.y = position.y - boundary.y - radius * 4;
		aircraft.setPosition(position);
		
	}
	if (velocity.y < 0 && position.y < -radius * 2) {
		position.y = position.y + boundary.y + radius * 4;
		aircraft.setPosition(position);
	}
}

void Aircraft::Accelerate(float dt) {
	velocity += sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * force * dt;
}

void Aircraft::RotateLeft(float dt) {
	float rotation = -rotateSpeed * dt;

	aircraft.rotate(rotation);

	headingAngle = aircraft.getRotation();
}

void Aircraft::RotateRight(float dt) {

	float rotation = rotateSpeed * dt;

	aircraft.rotate(rotation);

	headingAngle = aircraft.getRotation();
	
}

void Aircraft::Attack() {

	if (lastShootTime < shootInterval) { return; }
	
	for (auto bullet : (*bulletPool)) {
		if (bullet->enabled) { continue; }
		bullet->SetHeading(headingAngle);
		bullet->SetSpeed(200);
		bullet->setPosition(sf::Vector2f(cos(headingAngle * 3.14 / 180), sin(headingAngle * 3.14 / 180)) * radius + position);
		bullet->enabled = true;
		break;
	}
	lastShootTime = 0;
}

void Aircraft::Update(float dt) {
	Move(dt);


	if (destroied) { return; }

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

}

