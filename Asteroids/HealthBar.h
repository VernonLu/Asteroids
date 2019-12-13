#pragma once
#include <SFML/Graphics.hpp>
class HealthBar : public sf::Drawable {
private:
	int curHealth;
	int maxHealth;
	sf::Sprite sprite;
	sf::Sprite bgSprite;
	sf::Vector2f size;
	sf::Vector2f texSize;
	sf::Vector2f bgTexSize;
	void UpdateHealth();
	void UpdateMaxHealth();

public:
	HealthBar(int max, int current = -1);
	~HealthBar();
	void SetSize(sf::Vector2f size);
	void SetSize(float x, float y);
	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);
	void SetTexture(sf::Texture& texture);
	void SetBgTexture(sf::Texture& texture);
	void IncreaseHealth(int value = 1);
	void DecreaseHealth(int value = 1);
	void IncreaseMaxHealth(int value = 1);
	void DecreaseMaxHealth(int value = 1);
	bool isEmpty();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};