#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <random>

class Piece
{
public:
    Piece(float x, float y, float size, char letter);

    void render(sf::RenderTarget& target) const;
    sf::FloatRect getGlobalBounds() const;
    void setRandomLetter();
    sf::Text getCharacterText() const;
    char getCharacter() const;
    void setLetter(char newLetter);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    void updateText();

private:
    sf::Vector2f position;
    float size;
    char letter;
    bool isHovered;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
};

#endif // PIECE_H