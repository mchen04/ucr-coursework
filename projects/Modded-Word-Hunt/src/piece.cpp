#include "../include/Piece.h"

Piece::Piece(float x, float y, float size, char letter)
    : position(sf::Vector2f(x, y)), size(size), letter(letter), isHovered(false)
{
    if (font.loadFromFile("Poppins-Black.ttf"))
    {
        shape.setPosition(position);
        shape.setSize(sf::Vector2f(size, size));
        shape.setOutlineThickness(2.0f);
        shape.setOutlineColor(sf::Color::Black);

        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(size * 0.4f));
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);

        updateText();
    }
}

void Piece::render(sf::RenderTarget& target) const
{
    target.draw(shape);
    target.draw(text);
}

sf::FloatRect Piece::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

void Piece::setRandomLetter()
{
    std::random_device rd;
    std::mt19937 generator(rd());

    // Define the letter distribution based on their frequencies in words
    std::discrete_distribution<> letterDistribution({ 12, 2, 3, 8, 18, 2, 2, 6, 14, 1, 1, 4, 2,
                                                      7, 12, 2, 1, 6, 12, 9, 6, 1, 2, 1, 2, 1 });

    // Generate a random letter based on the distribution
    char randomLetter = 'A' + letterDistribution(generator);
    letter = randomLetter;

    updateText();
}

sf::Vector2f Piece::getPosition() const {
    return position;
}

sf::Vector2f Piece::getSize() const {
    return sf::Vector2f(size, size);
}

sf::Text Piece::getCharacterText() const
{
    return text;
}

char Piece::getCharacter() const
{
    return letter;
}

void Piece::setLetter(char newLetter)
{
    letter = newLetter;
    updateText();
}

void Piece::updateText()
{
    text.setString(std::string(1, letter));
    text.setPosition(position.x + size / 2.0f, position.y + size / 2.0f);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}