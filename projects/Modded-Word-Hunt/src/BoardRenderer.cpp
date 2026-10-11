#include "../include/BoardRenderer.h"

BoardRenderer::BoardRenderer(const Board& board) : board(board) {}

void BoardRenderer::render(sf::RenderTarget& target) const
{
    target.draw(board.getBoardShape());
    sf::RectangleShape highlight;
    const auto& pieces = board.getPieces();
    const auto& pieceSelected = board.getPieceSelected();

    for (size_t i = 0; i < pieces.size(); ++i)
    {
        const auto& piece = pieces[i];

        if (pieceSelected[i])
        {
            sf::FloatRect bounds = piece.getGlobalBounds();
            highlight.setSize(sf::Vector2f(bounds.width, bounds.height));
            highlight.setPosition(bounds.left, bounds.top);
            highlight.setOutlineThickness(2.0f);

            // First draw with transparent fill color and green outline
            highlight.setFillColor(sf::Color::Transparent);
            highlight.setOutlineColor(sf::Color::Green);
            sf::Text pieceText = pieces[i].getCharacterText();
            target.draw(highlight);
            target.draw(pieceText);

            // Draw the piece, including its text
            piece.render(target);

            // Draw again with green fill color and black outline
            highlight.setFillColor(sf::Color::Green);
            highlight.setOutlineColor(sf::Color::Black);
            target.draw(highlight);
            target.draw(pieceText);
        }
        else
        {
            piece.render(target);
        }
    }
}





