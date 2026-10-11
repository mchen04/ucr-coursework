#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <random>
#include <vector>

#include "Piece.h"

class Board {
public:
    Board(unsigned int dimensions);
    void initializeRandomLetters();
    void update(const sf::Vector2f& mousePosition, bool isMousePressed);
    void handleEvent(const sf::Event& event);
    void render(sf::RenderTarget& target) const;
    void printWord();
    std::vector<std::string> getWordList() { return wordList; }
    
    const sf::RectangleShape& getBoardShape() const;         
    const std::vector<Piece>& getPieces() const;  
    const std::vector<bool>& getPieceSelected() const; 

private:
    unsigned int dimensions;
    std::string word;
    std::vector<std::string> wordList;
    std::vector<Piece> pieces;
    std::vector<bool> pieceSelected;
    std::vector<char> characters;
    const Piece* hoverPiece;
    bool isMousePressed;
    sf::RectangleShape board;
    sf::Vector2f mousePosition;
};

#endif // BOARD_H
