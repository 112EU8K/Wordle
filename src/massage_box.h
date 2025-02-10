#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class massage_box
{
public:
    massage_box(const sf::Font &font);
    void show_message(const std::string &message);
    void hide();
    void draw(sf::RenderWindow &window) const;

private:
    void update_box_size();

    sf::RectangleShape back_ground;
    sf::Text text;
    bool is_visible;
    const float padding = 20.0f;
};

#endif // MESSAGEBOX_H
