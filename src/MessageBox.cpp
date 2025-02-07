#include "MessageBox.h"

MessageBox::MessageBox(const sf::Font& font, const std::string& message)
{
    _background.setSize(sf::Vector2f(400, 100));
    _background.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent gray
    _background.setOutlineThickness(2);
    _background.setOutlineColor(sf::Color::White);
    _background.setPosition(440, 310); // Centered in 1280x720 window

    _text.setFont(font);
    _text.setString(message);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(460, 340);

    _isVisible = false;
}

void MessageBox::showMessage(const std::string& message)
{
    _text.setString(message);
    _isVisible = true;
}

void MessageBox::hide()
{
    _isVisible = false;
}

void MessageBox::draw(sf::RenderWindow& window) const
{
    if (_isVisible) {
        window.draw(_background);
        window.draw(_text);
    }
}

