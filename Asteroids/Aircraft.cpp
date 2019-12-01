#include "Aircraft.h"

void Aircraft::UpdateSpriteSize() {
	if (aircraft.getTexture() == NULL) { return; }
	sf::Vector2u texSize = aircraft.getTexture()->getSize();
	aircraft.setOrigin(texSize.x / 2, texSize.y / 2);
	sf::Vector2f scale(radius / texSize.x, radius / texSize.y);
	aircraft.setScale(scale);
}

Aircraft::Aircraft() {
	radius = 1;
	force = 0;
	velocity = sf::Vector2f(0, 0);
	headingAngle = 0;
	rotateSpeed = 0;
	thrustSound.setLoop(true);
	aircraft.setPosition(1, 1);
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

void Aircraft::Move(float dt) {
	position += velocity * dt;
	aircraft.move(velocity * dt);
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

}

void Aircraft::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		RotateLeft(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		RotateRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		Accelerate(dt);
		if (thrustSound.getStatus() != sf::SoundSource::Status::Playing) {
			thrustSound.play();
		}
	}
	else {
		thrustSound.pause();
	}

	Move(dt);
}

