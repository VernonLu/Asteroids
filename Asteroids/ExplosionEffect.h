#pragma once
#include <SFML/Graphics.hpp>
class ExplosionEffect : public sf::Drawable{
public:
	bool enable;
	int maxCount;
	float timer;
	float lifeTime;
	float interval;
	sf::Vector2f position;
	std::vector<sf::CircleShape*> shapes;
	
	ExplosionEffect();
	~ExplosionEffect();
	void Enable();
	void SetPosition(sf::Vector2f position);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

