#include "../include/Text.h"

Text::Text(sf::Font& font, const std::string& string, unsigned int characterSize, const sf::Color& fillColor,
           const sf::Color& outlineColor, float outlineThickness, const sf::Vector2f& position)
{
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
    text.setPosition(position);
}

void Text::setPosition(const sf::Vector2f& position) {
    text.setPosition(position);
}

void Text::setString(const std::string& string) {
    text.setString(string);
}

void Text::setCharacterSize(unsigned int characterSize) {
    text.setCharacterSize(characterSize);
}

void Text::setFillColor(const sf::Color& fillColor) {
    text.setFillColor(fillColor);
}

void Text::setOutlineColor(const sf::Color& outlineColor) {
    text.setOutlineColor(outlineColor);
}

void Text::setOutlineThickness(float outlineThickness) {
    text.setOutlineThickness(outlineThickness);
}

sf::Vector2f Text::getPosition() const {
    return text.getPosition();
}

std::string Text::getString() const {
    return text.getString();
}

unsigned int Text::getCharacterSize() const {
    return text.getCharacterSize();
}

sf::Color Text::getFillColor() const {
    return text.getFillColor();
}

sf::Color Text::getOutlineColor() const {
    return text.getOutlineColor();
}

float Text::getOutlineThickness() const {
    return text.getOutlineThickness();
}

sf::FloatRect Text::getLocalBounds() const {
    return text.getLocalBounds();
}

// Implement the getText() function
sf::Text& Text::getText() {
    return text;
}
