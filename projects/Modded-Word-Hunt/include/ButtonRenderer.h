#ifndef BUTTONRENDERER_H
#define BUTTONRENDERER_H

#include <SFML/Graphics.hpp>

class ButtonCustom; // Forward declaration

class ButtonRenderer {
private:
    ButtonCustom& m_button; 
public:
    ButtonRenderer(ButtonCustom& button);
    void render(sf::RenderWindow& window);
};

#endif // BUTTON_RENDERER_H
