#include "../include/Slider.h"

Slider::Slider(float width, float height, float xPos, float yPos)
    : sliderBar(sf::Vector2f(width, height)),
      sliderHandle(sf::Vector2f(height, height)),
      isSliderPressed(false)
{
    sliderBar.setPosition(xPos, yPos);
    sliderHandle.setPosition(xPos, yPos);
}

void Slider::update(sf::RenderWindow& window)
{
    if (isSliderPressed)
    {
        sf::Vector2f newPosition = calculateNewPosition(window);
        sliderHandle.setPosition(newPosition);
    }
}

void Slider::draw(sf::RenderWindow& window)
{
    window.draw(sliderBar);
    window.draw(sliderHandle);
}

void Slider::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePosition = getMousePosition(window);
        if (sliderHandle.getGlobalBounds().contains(mousePosition))
            isSliderPressed = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        isSliderPressed = false;
    }
}

float Slider::getValue() const
{
    float sliderWidth = getSliderWidth();
    float handlePosition = getHandlePosition();
    float percentage = handlePosition / sliderWidth;
    return percentage * 100.f;
}

sf::Vector2f Slider::calculateNewPosition(sf::RenderWindow& window) const
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f newPosition = window.mapPixelToCoords(mousePosition);
    newPosition.x = std::max(newPosition.x, sliderBar.getPosition().x);
    newPosition.x = std::min(newPosition.x, sliderBar.getPosition().x + getSliderWidth() - getHandleWidth());
    return newPosition;
}

sf::Vector2f Slider::getMousePosition(const sf::RenderWindow& window) const
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return window.mapPixelToCoords(mousePosition);
}

float Slider::getSliderWidth() const
{
    return sliderBar.getSize().x - getHandleWidth();
}

float Slider::getHandlePosition() const
{
    return sliderHandle.getPosition().x - sliderBar.getPosition().x;
}

float Slider::getHandleWidth() const
{
    return sliderHandle.getSize().x;
}
