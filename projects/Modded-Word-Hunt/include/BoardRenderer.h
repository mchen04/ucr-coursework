#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"

class Board;

class BoardRenderer
{
public:
    explicit BoardRenderer(const Board& board);

    void render(sf::RenderTarget& target) const;

private:
    const Board& board;

    void renderHighlightedPiece(sf::RenderTarget& target, const Piece& piece) const;
    void renderPiece(sf::RenderTarget& target, const Piece& piece) const;
};

#endif  // BOARD_RENDERER_H
