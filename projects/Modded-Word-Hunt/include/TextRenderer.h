#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <SFML/Graphics.hpp>
#include "Text.h"

class TextRenderer {
private:
    Text& text;

public:
    TextRenderer(Text& text);
    void render(sf::RenderWindow& window);
};

#endif // TEXTRENDERER_H
