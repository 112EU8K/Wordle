#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <iostream>
#include "Game.h"

/*
SMFLGame class:
Manages the sf::RenderWindow and game loop by passing information to the Game class.
*/

class SFMLGame
{
public:
    SFMLGame(Game &game);
    virtual ~SFMLGame() = default;

    static sf::RenderWindow &getWindow();
    void gameLoop();
    void handleResize(unsigned int width, unsigned int height);

private:
    static sf::RenderWindow _window;
    sf::Font _font;
    sf::Image _icon;
    Game &_game;
    static sf::Font loadFont();
};


#endif // SFMLGAME_H
