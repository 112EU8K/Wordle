#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <iostream>
#include "game.h"


class sfml_game
{
public:
    sfml_game(game &game);
    virtual ~sfml_game() = default;

    static sf::RenderWindow &get_window();
    void game_loop();
    void handle_resize(unsigned int width, unsigned int height);

private:
    static sf::RenderWindow window;
    sf::Font font;
    sf::Image icon;
    game &ggg;
    static sf::Font load_font();
};


#endif // SFMLGAME_H
