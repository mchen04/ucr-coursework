#ifndef BUTTONCUSTOM_H
#define BUTTONCUSTOM_H

#include <SFML/Graphics.hpp>

#include "Text.h"

enum class ButtonState { Idle, Hover, Active };

class ButtonCustom {
private:
    ButtonState buttonState;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::RectangleShape shape;
    sf::Text text;

public:
    ButtonCustom(float x, float y, float width, float height, const sf::Font& font, const std::string& buttonText,
                 const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor);
    ~ButtonCustom();

    // Accessors
    bool isPressed() const;

    // Getters and setters
    sf::Color getIdleColor() const;
    void setIdleColor(const sf::Color& color);

    sf::Color getHoverColor() const;
    void setHoverColor(const sf::Color& color);

    sf::Color getActiveColor() const;
    void setActiveColor(const sf::Color& color);

    sf::Text getText() const;
    void setText(const std::string& text);

    // Other functions
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setFont(const sf::Font& font);
    void setFillColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);

    sf::RectangleShape& getShape();
    const sf::RectangleShape& getShape() const;
    sf::FloatRect getTextGlobalBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    void update(const sf::Vector2f& mousePos);
};

#endif // BUTTONCUSTOM_H
