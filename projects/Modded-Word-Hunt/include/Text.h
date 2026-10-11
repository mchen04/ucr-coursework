#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

class Text {
private:
    sf::Text text;

public:
    Text(sf::Font& font, const std::string& string, unsigned int characterSize, const sf::Color& fillColor,
         const sf::Color& outlineColor = sf::Color::Transparent, float outlineThickness = 0.0f,
         const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f));

    void setPosition(const sf::Vector2f& position);
    void setString(const std::string& string);
    void setCharacterSize(unsigned int characterSize);
    void setFillColor(const sf::Color& fillColor);
    void setOutlineColor(const sf::Color& outlineColor);
    void setOutlineThickness(float outlineThickness);

    sf::Vector2f getPosition() const;
    std::string getString() const;
    unsigned int getCharacterSize() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    float getOutlineThickness() const;
    sf::FloatRect getLocalBounds() const; // Added getLocalBounds function

    // Added getText function
    sf::Text& getText();
};

#endif // TEXT_H
