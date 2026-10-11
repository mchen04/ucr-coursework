#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include "SFML/System.hpp" 
#include "SFML/Window.hpp" 
#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp" 
#include "SFML/Network.hpp" 

class State
{
private:
    sf::RenderWindow* window ; 
    std::vector<sf::Texture> textures ;

public:
    State(sf::RenderWindow* window);
    virtual ~State();

    virtual void update(const float& dt) = 0 ;
    virtual void render(sf::RenderWindow* window = nullptr) = 0 ;

    virtual void endState() = 0 ;
};

#endif