#include "sfml_game.h"

int main() {
    sf::Font font;
    if (!font.loadFromFile("FONTS/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
        return -1;
    }

    std::default_random_engine random_engine(std::random_device{}());

    game game(sfml_game::get_window(), sf::IntRect(0, 0, 1280, 720), font, random_engine);

    sfml_game sfml_game(game);

    sfml_game.game_loop();

    return 0;
}
