#include "HealthBar.h"

void HealthBar::UpdateHealth() {
	sprite.setTextureRect(sf::IntRect(0, 0, texSize.x * (curHealth < 0 ? 0 : curHealth), texSize.y));
}

void HealthBar::UpdateMaxHealth() {
	bgSprite.setTextureRect(sf::IntRect(0, 0, texSize.x * maxHealth, texSize.y));
}

///If Current Health is not provided it will be set to Max Health
HealthBar::HealthBar(int max, int current) {
	maxHealth = max;
	curHealth = (current == -1) ? max : current;
	size = sf::Vector2f(1, 1);
}

HealthBar::~HealthBar() {}

void HealthBar::SetSize(sf::Vector2f size) {
	this->size.x = size.x <= 0 ? 1 : size.x;
	this->size.y = size.y <= 0 ? 1 : size.y;

	float factor = (size.y / texSize.y);
	sprite.setScale(sf::Vector2f(factor, factor));
	bgSprite.setScale(sf::Vector2f(factor, factor));
	UpdateHealth();
	UpdateMaxHealth();
}

void HealthBar::SetSize(float x, float y) {
	this->size.x = x <= 0 ? 1 : x;
	this->size.y = y <= 0 ? 1 : y;

	float factor = (size.y / texSize.y);
	sprite.setScale(sf::Vector2f(factor, factor));
	bgSprite.setScale(sf::Vector2f(factor, factor));
	UpdateHealth();
	UpdateMaxHealth();
}

void HealthBar::SetPosition(sf::Vector2f position) {
	sprite.setPosition(position);
	bgSprite.setPosition(position);
}

void HealthBar::SetPosition(float x, float y) {
	sf::Vector2f position(x, y);
	sprite.setPosition(position);
	bgSprite.setPosition(position);
}

void HealthBar::SetTexture(sf::Texture& texture) {
	texture.setRepeated(true);
	sf::Vector2u s = texture.getSize();
	texSize = sf::Vector2f(s.x, s.y);
	sprite.setTexture(texture);
}

void HealthBar::SetBgTexture(sf::Texture& texture) {
	texture.setRepeated(true);
	sf::Vector2u s = texture.getSize();
	texSize = sf::Vector2f(s.x, s.y);
	bgSprite.setTexture(texture);
}

void HealthBar::IncreaseHealth(int value) {
	curHealth += value;
	curHealth = curHealth >= maxHealth ? maxHealth : curHealth;
	UpdateHealth();
}

void HealthBar::DecreaseHealth(int value) {
	curHealth -= value;
	UpdateHealth();
}

void HealthBar::IncreaseMaxHealth(int value) {
	maxHealth += value;
	UpdateMaxHealth();
}

void HealthBar::DecreaseMaxHealth(int value) {
	maxHealth -= value;
	maxHealth = maxHealth < 0 ? 0 : maxHealth;
	UpdateMaxHealth();
}

bool HealthBar::isEmpty() {
	return curHealth < 0;
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(bgSprite);
	target.draw(sprite);
}
