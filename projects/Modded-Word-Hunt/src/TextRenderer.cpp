#include "../include/TextRenderer.h"

TextRenderer::TextRenderer(Text& text) : text(text) {}

void TextRenderer::render(sf::RenderWindow& window) {
    window.draw(text.getText());
}
