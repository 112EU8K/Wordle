#include "MessageBox.h"

MessageBox::MessageBox(const sf::Font& font, const std::string& message)
{
    _text.setFont(font);
    _text.setString(message);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);

    _background.setFillColor(sf::Color(50, 50, 50, 200));
    _background.setOutlineThickness(2);
    _background.setOutlineColor(sf::Color::White);

    updateBoxSize();
    _isVisible = false;
}

void MessageBox::showMessage(const std::string& message)
{
    _text.setString(message);
    updateBoxSize();
    _isVisible = true;
}

void MessageBox::updateBoxSize()
{
    // Get the local bounds of the text
    sf::FloatRect textBounds = _text.getLocalBounds();

    // Calculate new background size with padding
    float boxWidth = textBounds.width + (PADDING * 2);
    float boxHeight = textBounds.height + (PADDING * 2);
    _background.setSize(sf::Vector2f(boxWidth, boxHeight));

    // Center the background in the window (assuming 1280x720)
    float backgroundX = (1280 - boxWidth) / 2;
    float backgroundY = (720 - boxHeight) / 2;
    _background.setPosition(backgroundX, backgroundY);

    // Center the text within the background
    // We need to account for the text's origin being at the top-left of its bounds
    float textX = backgroundX + PADDING - textBounds.left;
    float textY = backgroundY + PADDING - textBounds.top;
    _text.setPosition(textX, textY);
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

