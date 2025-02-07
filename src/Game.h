#ifndef GAME_H
#define GAME_H

#include "WndInterface.h"
#include <random>
#include "WordDatabase.h"
#include "PlayHistory.h"
#include <memory>
#include "Button.h"

class SFMLGame;


/*
Game class:
Manages instances of the puzzle window.
*/
class Game
{
public:
	// Initialises the game.
	Game(sf::RenderWindow& window, const sf::IntRect& gameBounds, const sf::Font& font, std::default_random_engine& randomEngine);
	virtual ~Game();

	// Updates the current state of the active window.
	void update(const float deltaTime);

	// Draws the current window.
	void draw(sf::RenderWindow & renderWindow) const;

	// Handles passing events on to the active interface.
	void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft);

	// Handles passing the mouse moved event to the active interface.
	void handleMouseMove(const sf::Vector2i& mousePosition);

	// Handles passing key pressed event to the active interface.
	void handleKeyInput(const sf::Keyboard::Key key);

	//  When true, the game should end.
	bool getGameCloseRequested();

private:
    	// Reference to the window
    	sf::RenderWindow& _window; // Store a reference instead of calling SFMLGame::getWindow()

	// Bounds of the game area.
	const sf::IntRect _bounds;

	// Reference to the font
	const sf::Font& _font;

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine _randomEngine;

	// Reference to the current active interface.
	WndInterface* _activeInterface;

	// Reference to the current active overlay if one exists.
	WndInterface* _activeOverlay;

	// When true, the game should end.
	bool _terminateGame;

	// Collection of words
	std::unique_ptr<WordDatabase> _wordDatabase;

	// The player's saved history
	std::unique_ptr<PlayHistory> _playHistory;

    	std::vector<Button> _buttons; // Stores number selection buttons
};

#endif // GAME_H
