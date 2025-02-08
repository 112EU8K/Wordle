#include "PauseWnd.h"

PauseWnd::PauseWnd(const sf::IntRect& bounds, const sf::Font& font)
    : WndInterface(bounds),
      _restartButton(sf::IntRect(0, 0, 200, 50), "Restart", 1, font),
      _menuButton(sf::IntRect(0, 0, 200, 50), "Menu", 2, font),
      _resultState(WndResultState::NothingState),
      _selectedWordLength(0)
{
    // Setup semi-transparent fullscreen background
    _fullScreenBackground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width, bounds.height));
    _fullScreenBackground->setFillColor(sf::Color(20, 20, 20, 150));

    // Setup pause menu background
    const float menuWidth = 400;
    const float menuHeight = 500;
    _background = std::make_unique<sf::RectangleShape>(sf::Vector2f(menuWidth, menuHeight));
    _background->setFillColor(sf::Color(60, 60, 60, 230));
    _background->setOutlineColor(sf::Color::White);
    _background->setOutlineThickness(1);
    _background->setPosition(bounds.left + (bounds.width - menuWidth)/2, bounds.top + (bounds.height - menuHeight)/2);

    // Setup title
    _titleText = std::make_unique<sf::Text>("Game Paused", font, 40);
    _titleText->setPosition(
        bounds.left + bounds.width/2 - _titleText->getGlobalBounds().width/2,
        _background->getPosition().y + 20
    );

    // Setup the word length text
    int currentWordLength = 5; // Default value
    _wordLengthText = std::make_unique<sf::Text>("Current Word Length: " + std::to_string(currentWordLength), font, 25);
    _wordLengthText->setFillColor(sf::Color::White);
    _wordLengthText->setPosition(
        bounds.left + bounds.width / 2 - _wordLengthText->getGlobalBounds().width / 2,
        _background->getPosition().y + 80
    );

    // Position restart button
    _restartButton.setBackgroundColour(sf::Color(93, 141, 74));
    float buttonX = bounds.left + bounds.width/2 - 100;
    float buttonY = _background->getPosition().y + menuHeight - 90;
    _restartButton = Button(sf::IntRect(buttonX, buttonY, 200, 50), "Restart", 1, font);

     // Position the menu button below the restart button
    buttonY += 60;  // Offset to place it below restart
    _menuButton = Button(sf::IntRect(buttonX, buttonY, 200, 50), "Menu", 2, font);

    // Initialize word length buttons
    initializeWordLengthButtons(font);
}

void PauseWnd::initializeWordLengthButtons(const sf::Font& font) {
    const float buttonWidth = 60;
    const float buttonHeight = 60;
    const float buttonSpacing = 10;
    const int buttonsPerRow = 5;

    // Calculate total row width
    float totalRowWidth = buttonsPerRow * buttonWidth + (buttonsPerRow - 1) * buttonSpacing;

    // New: Calculate perfect center X position
    float startX = _background->getPosition().x + (_background->getSize().x - totalRowWidth) / 2;
    float startY = _background->getPosition().y + 100;

    for (int i = WORD_LENGTH_MIN; i <= WORD_LENGTH_MAX; ++i) {
        int row = (i - WORD_LENGTH_MIN) / buttonsPerRow;
        int col = (i - WORD_LENGTH_MIN) % buttonsPerRow;

        float x = startX + col * (buttonWidth + buttonSpacing);
        float y = startY + row * (buttonHeight + buttonSpacing);

        _wordLengthButtons.emplace_back(
            sf::IntRect(x, y, buttonWidth, buttonHeight),
            std::to_string(i),
            i,
            font
        );
    }
}


void PauseWnd::update(const float deltaTime) {
    // No update logic needed for pause menu
}

void PauseWnd::draw(sf::RenderWindow& renderWindow) const {
    renderWindow.draw(*_fullScreenBackground);
    renderWindow.draw(*_background);
    renderWindow.draw(*_titleText);
    renderWindow.draw(*_wordLengthText);

    for (const auto& button : _wordLengthButtons) {
        button.draw(renderWindow);
    }

    _restartButton.draw(renderWindow);
    _menuButton.draw(renderWindow);
}

void PauseWnd::setCurrentWordLength(int length) {
    _wordLengthText->setString("Current Word Length: " + std::to_string(length));
    _wordLengthText->setPosition(
        _background->getPosition().x + (_background->getSize().x / 2) - (_wordLengthText->getGlobalBounds().width / 2),
        _background->getPosition().y + 300
    );
}


void PauseWnd::handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) {
    // Check word length buttons
    for (auto& button : _wordLengthButtons) {
        if (button.isPositionInside(mousePosition)) {
            _selectedWordLength = button.getActionID();
            _resultState = WndResultState::Finished;
            return;
        }
    }

    // Check restart button
    if (_restartButton.isPositionInside(mousePosition)) {
        _resultState = WndResultState::Restart;
    }
    else if (_menuButton.isPositionInside(mousePosition)) {  // Check for menu button
        _resultState = WndResultState::Menu;
    }
}

void PauseWnd::handleMouseMove(const sf::Vector2i& mousePosition) {
    for (auto& button : _wordLengthButtons) {
        button.setHovering(button.isPositionInside(mousePosition));
    }

    _restartButton.setHovering(_restartButton.isPositionInside(mousePosition));
}

WndResultState PauseWnd::getResultState() const {
    return _resultState;
}

int PauseWnd::getSelectedWordLength() const {
    return _selectedWordLength;
}
