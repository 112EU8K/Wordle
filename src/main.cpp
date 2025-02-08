#include "SFMLGame.h"
// main.cpp - Simplified initialization
int main() {
    sf::Font font;
    if (!font.loadFromFile("FONTS/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
        return -1;
    }

    std::default_random_engine randomEngine(std::random_device{}());

    Game game(SFMLGame::getWindow(), sf::IntRect(0, 0, 1280, 720), font, randomEngine);

    SFMLGame sfmlGame(game);

    sfmlGame.gameLoop();

    return 0;
}
