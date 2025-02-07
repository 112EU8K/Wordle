#include "SFMLGame.h"
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_FILE_PATH "FONTS/arial.ttf"

// Define the static member
sf::RenderWindow SFMLGame::_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wordle - expanded Edition", sf::Style::Default);


// SFMLGame.cpp - Simplified constructor
SFMLGame::SFMLGame(Game &game)
    : _font(loadFont()),
      _game(game)  // Only initialize what we need
{
    if (!_icon.loadFromFile("WINDOWICON/Wordle_2021_icon.png"))
    {
        std::cerr << "Failed to load window icon" << std::endl;
    }
    else
    {
        _window.setIcon(_icon.getSize().x, _icon.getSize().y, _icon.getPixelsPtr());
    }
}

sf::RenderWindow& SFMLGame::getWindow()
{
    return _window;
}

void SFMLGame::gameLoop()
{
	sf::Clock clock;
	while (_window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();
		sf::Event event;
		if (_window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				_game.handleMousePress(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), event.mouseButton.button == sf::Mouse::Left);
			}
			else if (event.type == sf::Event::MouseMoved) {
				_game.handleMouseMove(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			else if (event.type == sf::Event::KeyPressed) {
				_game.handleKeyInput(event.key.code);
			}
		}
		_game.update(deltaTime);

		_window.clear(sf::Color::Black);
		_game.draw(_window);
		_window.display();

		if (_game.getGameCloseRequested()) {
			_window.close();
		}
	}
}

sf::Font SFMLGame::loadFont()
{
	sf::Font font;
	if (!font.loadFromFile(FONT_FILE_PATH))
	{
		throw("Failed to load font.");
	}

	return font;
}

