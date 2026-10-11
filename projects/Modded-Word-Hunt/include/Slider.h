#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>

class Slider
{
public:
    Slider(float width, float height, float xPos, float yPos);

    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    float getValue() const;

private:
    sf::RectangleShape sliderBar;
    sf::RectangleShape sliderHandle;
    bool isSliderPressed;

    sf::Vector2f calculateNewPosition(sf::RenderWindow& window) const;
    sf::Vector2f getMousePosition(const sf::RenderWindow& window) const;
    float getSliderWidth() const;
    float getHandlePosition() const;
    float getHandleWidth() const;
};

#endif // SLIDER_H
