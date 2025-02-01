#include "SFMLGame.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_FILE_PATH "FONTS/arial.ttf"

SFMLGame::SFMLGame()
	: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wordle - by Peter Mitchell (2025 edit by 112EU8K)", sf::Style::Titlebar | sf::Style::Close),
      _font(loadFont()),
      _randomEngine(std::random_device{}()),  // Initialize random engine properly
      _game(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), _font, _randomEngine) // Pass the random engine
{
    if (!_icon.loadFromFile("WINDOWICON/Wordle_2021_icon.png"))
    {
        return; // Error handling if file not found
    }
    _window.setIcon(_icon.getSize().x, _icon.getSize().y, _icon.getPixelsPtr());
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
