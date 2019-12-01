#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f position, void clickEvent()) {
	this->size = size;
	this->position = position;
	this->clickEvent = clickEvent;
	hovered = false;
	normalColor = sf::Color(200, 0, 0);
	highlightColor = sf::Color::Red;
}

Button::~Button() {}

void Button::SetPosition(sf::Vector2f position) {
	this->position = position;
}

void Button::SetSize(sf::Vector2f size) {
	this->size = size;
}

void Button::SetClickEvent(void clickEvent()) {
	this->clickEvent = clickEvent;
}

void Button::SetCaption(sf::Font& font, std::string str, float fontSize) {
	caption.setFont(font);
	caption.setCharacterSize(fontSize);

	caption.setString(str);

	sf::FloatRect captionSize = caption.getLocalBounds();

	caption.setOrigin(sf::Vector2f(captionSize.width / 2 , fontSize / 2 + 10));
	caption.setFillColor(sf::Color::White);
	caption.setPosition(position.x, position.y);
}

void Button::SetTexture(sf::Texture& texture) {
	sf::Vector2u texSize = texture.getSize();
	float factorX = size.x / texSize.x;
	float factorY = size.y / texSize.y;

	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));

	sprite.setOrigin(size.x / (2 * factorX), size.y / (2 * factorY));

	sprite.setScale(size.x / texSize.x, size.y / texSize.y);

	sprite.setPosition(position);

	sprite.setColor(normalColor);
}

void Button::SetColor(sf::Color color) {
	int r = color.r - 35;
	int g = color.g - 35;
	int b = color.b - 35;

	normalColor = sf::Color((r > 0 ? r : 0), (g > 0 ? g : 0), (b > 0 ? b : 0));
	highlightColor = color;
}

void Button::Hover(sf::Vector2i mousePos) {
	if (mousePos.x > position.x - (size.x / 2) &&
		mousePos.x < position.x + (size.x / 2) &&
		mousePos.y > position.y - (size.y / 2) &&
		mousePos.y < position.y + (size.y / 2)) {

		sprite.setColor(highlightColor);
		caption.setFillColor(highlightColor);
		hovered = true;
		return;

	}
	sprite.setColor(normalColor);
	caption.setFillColor(normalColor);
	hovered = false;
}

void Button::Click(){
	if (!hovered) { return; }

	clickEvent();
}

void Button::Draw(sf::RenderWindow& target) {
	target.draw(sprite);
	target.draw(caption);
}

void Button::Deselect() {
	hovered = false;
}

void Button::Update(sf::Vector2i mousePos) {
	Deselect();
	Hover(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Click();
	}
}
