#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class MessageBox
{
public:
    MessageBox(const sf::Font& font, const std::string& message);

    // Set the message and make it visible
    void showMessage(const std::string& message);

    // Hides the message box
    void hide();

    // Draws the message box if it's visible
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape _background;
    sf::Text _text;
    bool _isVisible;
};

#endif // MESSAGEBOX_H
