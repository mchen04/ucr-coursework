#include "../include/Board.h"
#include "../include/BoardRenderer.h"

Board::Board(unsigned int dimensions)
    : dimensions(dimensions), hoverPiece(nullptr), isMousePressed(false)
{
    int windowSize = 1300;
    word = "";
    pieces.reserve(dimensions * dimensions);
    pieceSelected.resize(dimensions * dimensions, false);
    characters.reserve(dimensions * dimensions);

    float pieceSize = static_cast<float>(windowSize) / dimensions;
    for (unsigned int row = 0; row < dimensions; ++row)
    {
        for (unsigned int col = 0; col < dimensions; ++col)
        {
            float x = col * pieceSize + 100 ;
            float y = row * pieceSize + 100 ;
            pieces.emplace_back(x, y, pieceSize, 'A' + (row * dimensions + col));
        }
    }
}

void Board::update(const sf::Vector2f& mousePosition, bool isMousePressed)
{
    // Track whether any piece was clicked or not
    bool pieceClicked = false;
    hoverPiece = nullptr;

    for (size_t i = 0; i < pieces.size(); ++i)
    {
        if (pieces[i].getGlobalBounds().contains(mousePosition))
        {
            hoverPiece = &pieces[i];
            
            if (isMousePressed)
            {
                if (!pieceSelected[i]) // Check if the piece is not already selected
                {
                    pieceSelected[i] = true;
                    word += pieces[i].getCharacter(); // Set the character value directly to the string
                }
            } 
            else 
            {
                for (size_t i = 0; i < pieces.size(); ++i)
                {
                    pieceSelected[i] = false;
                }
            }
            pieceClicked = true; 
            break;
        }
    }

    // If no piece was clicked and the mouse is pressed, unclick all pieces
    if (!pieceClicked && isMousePressed)
    {
        for (size_t i = 0; i < pieces.size(); ++i)
        {
            pieceSelected[i] = false;
        }
    }
    else if (!isMousePressed)
    {
        // Mouse is released, print the word and clear it
        if(!word.empty()) {
            std::cout << "Selected word: " << word << std::endl;
            wordList.push_back(word);
            word.clear();
        }
    }
}


void Board::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - board.getPosition();
        update(mousePosition, isMousePressed);
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        isMousePressed = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        isMousePressed = false;
    }
}

void Board::printWord()
{
    std::cout << word << std::endl;
}

void Board::initializeRandomLetters()
{
    for (auto& piece : pieces)
    {
        piece.setRandomLetter();
    }
}

const sf::RectangleShape& Board::getBoardShape() const
{
    return board;
}

const std::vector<Piece>& Board::getPieces() const
{
    return pieces;
}

const std::vector<bool>& Board::getPieceSelected() const
{
    return pieceSelected;
}