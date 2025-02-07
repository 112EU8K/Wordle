#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <SFML/Graphics.hpp>
#include <string>


/*
Message Class:
Shows an error when a word isn't found in the list.x
*/
class MessageBox
{
public:
    MessageBox(const sf::Font& font, const std::string& message);
    void showMessage(const std::string& message);
    void hide();
    void draw(sf::RenderWindow& window) const;

private:
    void updateBoxSize();  // New helper function

    sf::RectangleShape _background;
    sf::Text _text;
    bool _isVisible;
    const float PADDING = 20.0f;  // Padding around text
};

#endif // MESSAGEBOX_H

