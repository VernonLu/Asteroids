#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(Vector2f pos, float lifetime, int count) {
	this->position = pos;
	this->lifetime = lifetime;
	this->count = count;
	this->time = 0;
	this->speed = 0;
}

ParticleSystem::~ParticleSystem() {}

void ParticleSystem::SetSpeed(float speed) {
	this->speed = speed;
}

void ParticleSystem::Update(float dt) {
	time += dt;

	if (time > lifetime) {
		isDead = true;
		return;
	}

	int currentCount = time / lifetime * count;

	float particleLifetime = lifetime - time;

	float angle = rand() % 360;
	float len = (rand() % 1000) / 100;
	Vector2f pos = Vector2f(cos(angle), sin(angle)) * len + position;

	if (currentCount < particlePool.size()) {
		particlePool[currentCount]->isDead = false;
		particlePool[currentCount]->setPosition(pos);
		particlePool[currentCount]->SetLifetime(particleLifetime);
	}
	else {
		Particle* newParticle = new Particle();
		newParticle->SetSpeed(speed);

		newParticle->SetColor(Color(255, rand() % 255, rand() % 255, particleLifetime / lifetime * 255));

		particlePool.push_back(newParticle);
	}
	for (auto particle : particlePool) {
		if (!particle->isDead) {
			particle->Update(dt);
		}
	}


}


void ParticleSystem::Draw(RenderWindow& window) {
	for (auto particle : particlePool) {
		if (!particle->isDead) {
			window.draw(*particle);
		}
	}
}

void ParticleSystem::Restart() {
	isDead = false;
	this->time = 0;
}
