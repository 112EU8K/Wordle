#include "Game.h"
#include <chrono>       // std::chrono::system_clock
#include <iostream>
#include "PuzzleWnd.h"
#include "PostGameWnd.h"

Game::Game(sf::RenderWindow& window, const sf::IntRect& gameBounds, const sf::Font& font, std::default_random_engine& randomEngine)
    : _window(window), _bounds(gameBounds), _font(font), _randomEngine(randomEngine)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	_randomEngine.seed(seed);
	_wordDatabase = std::make_unique<WordDatabase>(_randomEngine);
	_playHistory = std::make_unique<PlayHistory>("SAVEFILE/save.dat");

	_terminateGame = false;
	_activeInterface = nullptr;
	_activeOverlay = nullptr;

	// Create buttons for selecting word count (3 to 12)
	for (int i = 3; i <= 12; ++i) {
        float buttonX = _window.getSize().x * 0.9f; // 90% from the left
        float buttonY = 50 + (i - 3) * 50;
        _buttons.emplace_back(sf::IntRect(buttonX, buttonY, 50, 40), std::to_string(i), i, font);
	}

	// Default: Start with a random word length
	_activeInterface = new PuzzleWnd(gameBounds, font, _wordDatabase->getRandomWord(), randomEngine, *_wordDatabase);
}

Game::~Game()
{
	if (_activeInterface != nullptr) {
		delete _activeInterface;
	}
}

void Game::update(const float deltaTime)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->update(deltaTime);
		if (_activeOverlay->getResultState() == WndResultState::Restart) {
			delete _activeOverlay;
			_activeOverlay = nullptr;
			delete _activeInterface;
			_activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
		}
		else if (_activeOverlay->getResultState() == WndResultState::Quit) {
			_terminateGame = true;
		}
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->update(deltaTime);
		if (_activeInterface->getResultState() == WndResultState::Finished && _activeOverlay == nullptr) {
			auto guessGrid = dynamic_cast<PuzzleWnd*>(_activeInterface)->getGuessGrid();
			auto rules = guessGrid.getAllRules();
			std::string solution = guessGrid.getSolution();
			if (guessGrid.isSolved()) {
				_playHistory->insertHistory(rules.size() - 1);
			}
			else {
				_playHistory->insertHistoryLoss();
			}
			_activeOverlay = new PostGameWnd(_bounds, _font, solution, guessGrid.isSolved(), rules.size(), _playHistory, guessGrid.getShareString());
		}
	}
}

void Game::draw(sf::RenderWindow & renderWindow) const
{
	if (_activeInterface != nullptr) {
		_activeInterface->draw(renderWindow);
	}

	if (_activeOverlay != nullptr) {
		_activeOverlay->draw(renderWindow);
	}

	// Draw buttons
	for (const auto& button : _buttons) {
		button.draw(renderWindow);
	}
}

void Game::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
    sf::Vector2f worldPos = _window.mapPixelToCoords(mousePosition);

    if (_activeOverlay != nullptr) {
        _activeOverlay->handleMousePress(static_cast<sf::Vector2i>(worldPos), isLeft);
    }
    else if (_activeInterface != nullptr) {
        _activeInterface->handleMousePress(static_cast<sf::Vector2i>(worldPos), isLeft);
    }

    for (auto& button : _buttons) {
        if (button.isPositionInside(static_cast<sf::Vector2i>(worldPos))) {
            int newWordLength = button.getActionID();

            if (newWordLength != _wordDatabase->getCurrentWordLength()) {
                _wordDatabase->loadDatabase(newWordLength);
            }

            // Instead of creating a new WordDatabase, just update the interface
            _activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
            break;
        }
    }
}



void Game::handleMouseMove(const sf::Vector2i & mousePosition)
{

	if (_activeOverlay != nullptr) {
		_activeOverlay->handleMouseMove(mousePosition);
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->handleMouseMove(mousePosition);
	}
}

void Game::handleKeyInput(const sf::Keyboard::Key key)
{
	if (_activeOverlay != nullptr) {
		_activeOverlay->handleKeyInput(key);
	}
	else if (_activeInterface != nullptr) {
		_activeInterface->handleKeyInput(key);
	}
}

bool Game::getGameCloseRequested()
{
	return _terminateGame;
}
