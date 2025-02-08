#include "MenuWnd.h"
#include <iostream>
MenuWnd::MenuWnd(const sf::IntRect& bounds, const sf::Font& font, WordDatabase &dataBase)
    : WndInterface(bounds),
      _titleText("Wordle", font, 50),
      _instructionText("Select Word Length", font, 30),
      _resultState(WndResultState::NothingState),
      _selectedWordLength(0),
      _wordDatabase(dataBase)
{
    // Position the title
    _titleText.setPosition(sf::Vector2f(bounds.left + bounds.width / 8 - _titleText.getGlobalBounds().width / 8, bounds.top + 50));

    // Position the instruction text
    _instructionText.setPosition(sf::Vector2f(bounds.left + bounds.width / 8 - _instructionText.getGlobalBounds().width / 8, bounds.top + 120));

    // Create buttons for word lengths 3-12
    const int BUTTON_WIDTH = 200;  // Wider buttons
    const int BUTTON_HEIGHT = 50;  // Slightly shorter buttons
    const int VERTICAL_SPACING = 20;  // Space between buttons

    // Calculate starting Y position to center the button stack
    int totalHeight = (BUTTON_HEIGHT + VERTICAL_SPACING) * 10;  // 10 buttons (3-12)
    int startY = bounds.top + (bounds.height - totalHeight) / 2;

    // Center buttons horizontally
    int centerX = bounds.left + bounds.width / 2 - BUTTON_WIDTH / 2;

    for (int i = 3; i <= 12; ++i) {
        int buttonY = startY + (i - 3) * (BUTTON_HEIGHT + VERTICAL_SPACING);

        _buttons.emplace_back(
            sf::IntRect(centerX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT),
            std::to_string(i) + " Letters",
            i,
            font
        );
    }
}

void MenuWnd::update(const float deltaTime) {
    // No update logic needed for menu
}

void MenuWnd::draw(sf::RenderWindow& renderWindow) const {
    renderWindow.draw(_titleText);
    renderWindow.draw(_instructionText);

    for (const auto& button : _buttons) {
        button.draw(renderWindow);
    }
}

void MenuWnd::handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) {
    for (auto& button : _buttons) {
        if (button.isPositionInside(mousePosition)) {
            _selectedWordLength = button.getActionID();
            _resultState = WndResultState::Finished;
            std::cout << "Menu button clicked! Word Length: " << _selectedWordLength
                      << ", Result State: " << (int)_resultState << std::endl;

            // Update the word length in the WordDatabase
            _wordDatabase.setWordLength(_selectedWordLength);

            break;
        }
    }
}

void MenuWnd::handleMouseMove(const sf::Vector2i& mousePosition) {
    for (auto& button : _buttons) {
        button.setHovering(button.isPositionInside(mousePosition));
    }
}

WndResultState MenuWnd::getResultState() const {
    return _resultState;
}

int MenuWnd::getSelectedWordLength() const {
    return _selectedWordLength;
}
