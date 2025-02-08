#include "Button.h"

Button::Button(const sf::IntRect & bounds, const std::string & text, const int actionID, const sf::Font& font)
    : _bounds(bounds), _actionID(actionID), _text(text),
    _background(sf::Vector2f(_bounds.width - 2, _bounds.height - 2)),
    _textVisual(text, font, 30)
{
    _textVisual.setFillColor(sf::Color::White);
    _textVisual.setStyle(sf::Text::Bold);
    _textVisual.setPosition(sf::Vector2f(_bounds.left + _bounds.width / 2 - _textVisual.getGlobalBounds().width / 2, _bounds.top + _bounds.height / 2 - 20));

    _background.setPosition(sf::Vector2f(_bounds.left + 1, _bounds.top + 1));
    _background.setFillColor(sf::Color(5, 5, 5));
    _background.setOutlineThickness(1);
    _background.setOutlineColor(sf::Color::White);

    _colourID = 0;
    _isHovered = false;
    _isEnabled = true;
}

void Button::draw(sf::RenderWindow & renderWindow) const
{
    sf::Color bgColor = _isEnabled ? sf::Color(5, 5, 5) : sf::Color(30, 30, 30);
    sf::Color textColor = _isEnabled ? sf::Color::White : sf::Color(100, 100, 100);

    sf::RectangleShape tempBackground = _background;
    tempBackground.setFillColor(bgColor);

    sf::Text tempTextVisual = _textVisual;
    tempTextVisual.setFillColor(textColor);

    renderWindow.draw(tempBackground);
    renderWindow.draw(tempTextVisual);
}

int Button::getActionID() const
{
    return _actionID;
}

sf::IntRect Button::getBounds()
{
    return _bounds;
}

void Button::setHovering(const bool isHovering)
{
    if (!_isEnabled) return;  // Don't hover if disabled
    _isHovered = isHovering;
    _background.setOutlineThickness(_isHovered ? 3 : 1);
}

bool Button::isPositionInside(const sf::Vector2i & mousePosition) const
{
    return _isEnabled && _bounds.contains(mousePosition);
}

void Button::setBackgroundColour(const sf::Color & colour)
{
    _background.setFillColor(colour);
}

void Button::applyColourID(const int colourID)
{
    if (colourID > _colourID) {
        _colourID = colourID;
        switch (_colourID) {
        case 1:
            _background.setFillColor(sf::Color(40, 40, 40));
            break;
        case 2:
            _background.setFillColor(sf::Color(141, 141, 74));
            break;
        case 3:
            _background.setFillColor(sf::Color(93, 141, 74));
            break;
        }
    }
}

void Button::setEnabled(bool enabled)
{
    _isEnabled = enabled;
    if (!_isEnabled) {
        _isHovered = false;
        _background.setOutlineThickness(1);
    }
}

bool Button::isEnabled() const
{
    return _isEnabled;
}
