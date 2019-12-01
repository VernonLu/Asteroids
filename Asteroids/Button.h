#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button : public sf::Drawable {
private:

	sf::Text caption;

	sf::Sprite sprite;

	sf::Color normalColor;

	sf::Color highlightColor;

	sf::Vector2f size;

	sf::Vector2f position;
	
	bool hovered;

	void (*clickEvent)();

	void UpdateSize();
public:
	Button();
	
	~Button();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetPosition(sf::Vector2f position);

	void SetSize(sf::Vector2f size);

	void SetClickEvent(void clickEvent());

	void SetCaption(sf::Font& font, std::string str, float fontSize);

	void SetTexture(sf::Texture& texture);

	void SetColor(sf::Color color);

	void Hover(sf::Vector2i mousePos);

	void Click();

	void Deselect();

	void Update(sf::Vector2i mousePos);
};
