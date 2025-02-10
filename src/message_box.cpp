#include "message_box.h"

massage_box::massage_box(const sf::Font &font)
{
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    back_ground.setFillColor(sf::Color(50, 50, 50, 200));
    back_ground.setOutlineThickness(2);
    back_ground.setOutlineColor(sf::Color::White);

    update_box_size();
    is_visible = false;
}

void massage_box::show_message(const std::string &message)
{
    text.setString(message);
    update_box_size();
    is_visible = true;
}

void massage_box::update_box_size()
{
    sf::FloatRect text_bounds = text.getLocalBounds();

    float box_width = text_bounds.width + (padding * 2);
    float box_height = text_bounds.height + (padding * 2);
    back_ground.setSize(sf::Vector2f(box_width, box_height));

    float back_ground_x = (1280 - box_width) / 2;
    float back_ground_y = (720 - box_height) / 2;
    back_ground.setPosition(back_ground_x, back_ground_y);


    float text_x = back_ground_x + padding - text_bounds.left;
    float text_y = back_ground_y + padding - text_bounds.top;
    text.setPosition(text_x, text_y);
}

void massage_box::hide()
{
    is_visible = false;
}

void massage_box::draw(sf::RenderWindow &window) const
{
    if (is_visible) {
        window.draw(back_ground);
        window.draw(text);
    }
}

