#include "Game.h"
#include <chrono>       // std::chrono::system_clock
#include <iostream>
#include "PuzzleWnd.h"
#include "PostGameWnd.h"
#include "MenuWnd.h"
#include "PauseWnd.h"

// Game.cpp changes - Update constructor:
Game::Game(sf::RenderWindow& window, const sf::IntRect& gameBounds, const sf::Font& font, std::default_random_engine& randomEngine)
    : _window(window), _bounds(gameBounds), _font(font), _randomEngine(randomEngine), _inMenu(true), _isPaused(false)
{
    std::cout.setstate(std::ios_base::failbit);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    _randomEngine.seed(seed);
    _wordDatabase = std::make_unique<WordDatabase>(_randomEngine);
    _playHistory = std::make_unique<PlayHistory>("SAVEFILE/save.dat");

    _terminateGame = false;
    _activeInterface = nullptr;
    _activeOverlay = nullptr;

    // Start with menu
    _activeInterface = new MenuWnd(gameBounds, font, *_wordDatabase);
}

Game::~Game() {
    delete _activeInterface;
    delete _activeOverlay;
}


void Game::updateButtonStates()
{
    bool shouldEnableButtons = true;

    if (_activeInterface != nullptr) {
        auto* puzzleWnd = dynamic_cast<PuzzleWnd*>(_activeInterface);
        if (puzzleWnd && !puzzleWnd->getGuessGrid().isSolved() &&
            puzzleWnd->getGuessGrid().hasMoreGuesses() &&
            _activeOverlay == nullptr) {
            shouldEnableButtons = false;
        }
    }

    for (auto& button : _buttons) {
        button.setEnabled(shouldEnableButtons);
    }
}

// Game.cpp - Update update method:
void Game::update(const float deltaTime)
{
    if (_activeOverlay != nullptr) {
        _activeOverlay->update(deltaTime);
        std::cout << "Update called: _inMenu = " << _inMenu << std::endl;
        if (_activeOverlay->getResultState() == WndResultState::Restart) {
            delete _activeOverlay;
            _activeOverlay = nullptr;
            // If we're in game (not menu), start a new game with current word length
            if (!_inMenu) {
                delete _activeInterface;
                _activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
            } else {
                delete _activeInterface;
                _activeInterface = new MenuWnd(_bounds, _font, *_wordDatabase);
            }
        } else if (_activeOverlay != nullptr && _activeOverlay->getResultState() == WndResultState::Menu) {
                std::cout << "Returning to Menu from Pause!" << std::endl;

                delete _activeOverlay;
                _activeOverlay = nullptr;
                delete _activeInterface;
                _activeInterface = new MenuWnd(_bounds, _font, *_wordDatabase);
                _inMenu = true;
                _isPaused = false;
        }
        else if (_activeOverlay->getResultState() == WndResultState::Finished) {
            // Handle word length change from pause menu
            auto* pauseWnd = dynamic_cast<PauseWnd*>(_activeOverlay);
            if (pauseWnd) {
                int newWordLength = pauseWnd->getSelectedWordLength();
                if (newWordLength != _wordDatabase->getCurrentWordLength()) {
                    _wordDatabase->loadDatabase(newWordLength);
                    delete _activeInterface;
                    _activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
                }
            }
            delete _activeOverlay;
            _activeOverlay = nullptr;
            _isPaused = false;
        }
    }

    if (_activeInterface != nullptr && _activeInterface->getResultState() == WndResultState::Finished) {
        std::cout << "Switching from MenuWnd to PuzzleWnd!" << std::endl;

        delete _activeInterface;
        _activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
        _inMenu = false;
        }
    std::cout << "Active Interface: " << typeid(*_activeInterface).name() << std::endl;
}

void Game::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
    // Convert screen coordinates to world coordinates
    //sf::Vector2f worldPos = _window.mapPixelToCoords(mousePosition);

    std::cout << "Mouse Clicked at: " << mousePosition.x << ", " << mousePosition.y << std::endl;

    // Handle word length buttons with proper coordinate conversion
    for (auto& button : _buttons) {
        std::cout << "Button Bounds: " << button.getBounds().left << ", " << button.getBounds().top
                  << ", " << button.getBounds().width << ", " << button.getBounds().height << std::endl;
        if (button.isEnabled() && button.isPositionInside(mousePosition)) {  // Use original coordinates for button check
            int newWordLength = button.getActionID();

            if (newWordLength != _wordDatabase->getCurrentWordLength()) {
                _wordDatabase->loadDatabase(newWordLength);
                delete _activeInterface;
                _inMenu = false;
                _activeInterface = new PuzzleWnd(_bounds, _font, _wordDatabase->getRandomWord(), _randomEngine, *_wordDatabase);
                if (_activeOverlay != nullptr) {
                    delete _activeOverlay;
                    _activeOverlay = nullptr;
                }
                _inMenu = false;
            }

            break;
        }
    }

    // Handle regular game input with proper coordinate conversion
    if (_activeOverlay != nullptr) {
        _activeOverlay->handleMousePress(mousePosition, isLeft);  // Use original coordinates
    }
    else if (_activeInterface != nullptr) {
        _activeInterface->handleMousePress(mousePosition, isLeft);  // Use original coordinates
    }

    updateButtonStates();
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

void Game::handleMouseMove(const sf::Vector2i & mousePosition)
{
    // Use original screen coordinates for hover detection
    if (_activeOverlay != nullptr) {
        _activeOverlay->handleMouseMove(mousePosition);
    }
    else if (_activeInterface != nullptr) {
        _activeInterface->handleMouseMove(mousePosition);
    }
}
// Add to Game::handleKeyInput method:
void Game::handleKeyInput(const sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Escape && !_inMenu) {
        if (!_isPaused && _activeOverlay == nullptr) {
            _isPaused = true;
            auto* pauseMenu = new PauseWnd(_bounds, _font);
            pauseMenu->setCurrentWordLength(_wordDatabase->getCurrentWordLength());
            _activeOverlay = pauseMenu;
        }
        else if (_isPaused) {
            delete _activeOverlay;
            _activeOverlay = nullptr;
            _isPaused = false;
        }
        return;
    }

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
