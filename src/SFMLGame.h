#ifndef SFMLGAME_H
#define SFMLGAME_H


#include "Game.h"


class SFMLGame
{
public:
	// Initialises the game ready to start.
	SFMLGame();
	virtual ~SFMLGame() = default;

	// Continues running the game until
	void gameLoop();

private:
	// The window used for the game until it ends.
	sf::RenderWindow _window;

	// The font used throughout the game.
	sf::Font _font;

	// icon
	sf::Image _icon;

	// Reference to the Game used to manage all the interfaces within the game.
	Game _game;

	// uhhh
	std::default_random_engine _randomEngine;  // Change reference to a value

	// Loads the font
	static sf::Font loadFont();
};

#endif // SFMLGAME_H
