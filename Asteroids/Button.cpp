#include "Button.h"

void Button::UpdateSize() {
	if (sprite.getTexture() == nullptr) { return; }
	sf::Vector2u texSize = (sprite.getTexture()->getSize());
	sprite.setOrigin(texSize.x / 2, texSize.y / 2);
	sprite.setScale(size.x / texSize.x, size.y / texSize.y);
}

Button::Button() {
	this->size = sf::Vector2f(1 ,1);
	this->position = sf::Vector2f(1, 1);
	this->clickEvent = nullptr;
	normalColor = sf::Color(200, 200, 200);
	highlightColor = sf::Color::White;
	hovered = false;
}

Button::~Button() {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
	target.draw(caption);
}

void Button::SetPosition(sf::Vector2f position) {
	this->position = position;
	sprite.setPosition(position);
	caption.setPosition(position);
}

void Button::SetPosition(float x, float y) {
	position = sf::Vector2f(x, y);
	sprite.setPosition(position);
	caption.setPosition(position);
}

void Button::SetSize(sf::Vector2f size) {
	this->size = size;
	UpdateSize();
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
	sprite.setTexture(texture);
	UpdateSize();
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
