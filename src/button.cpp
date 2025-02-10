#include "button.h"

button::button(const sf::IntRect & bounds, const std::string & text, const int action_id, const sf::Font& font)
    : bounds(bounds), action_id(action_id), text(text),
    background(sf::Vector2f(bounds.width - 2, bounds.height - 2)),
    text_visual(text, font, 30)
{
    this->text_visual.setFillColor(sf::Color(sf::Color::White));
    this->text_visual.setStyle(sf::Text::Bold);
    this->text_visual.setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - text_visual.getGlobalBounds().width / 2, bounds.top + bounds.height / 2 - 20));

    this->background.setPosition(sf::Vector2f(bounds.left + 1, bounds.top + 1));
    this->background.setFillColor(sf::Color(5, 5, 5));
    this->background.setOutlineThickness(1);
    this->background.setOutlineColor(sf::Color::White);

    this->colour_id = 0;
    this->is_hovered = false;
    this->is_enabled = true;
}

void button::draw(sf::RenderWindow &render_window) const
{
    sf::Color bg_color = this->is_enabled ? sf::Color(5, 5, 5) : sf::Color(30, 30, 30);
    sf::Color text_color = this->is_enabled ? sf::Color::White : sf::Color(100, 100, 100);

    sf::RectangleShape temp_background = background;
    temp_background.setFillColor(sf::Color(bg_color));

    sf::Text temp_text_visual = text_visual;
    temp_text_visual.setFillColor(sf::Color(text_color));

    render_window.draw(temp_background);
    render_window.draw(temp_text_visual);
}

int button::get_action_id() const
{
    return this->action_id;
}

sf::IntRect button::get_bounds()
{
    return this->bounds;
}

void button::set_hovering(const bool is_hovering)
{
    if (!this->is_enabled) return;  // Don't hover if disabled
    is_hovered = is_hovering;
    background.setOutlineThickness(is_hovered ? 3 : 1);
}

bool button::is_position_inside(const sf::Vector2i & mousePosition) const
{
    return this->is_enabled && this->bounds.contains(mousePosition);
}

void button::set_background_colour(const sf::Color & colour)
{
    this->background.setFillColor(sf::Color(colour));
}

void button::apply_colour_id(const int colour_id)
{
    if (colour_id > this->colour_id) {
        this->colour_id = colour_id;
        switch (this->colour_id) {
        case 1:
            this->background.setFillColor(sf::Color(40, 40, 40));
            break;
        case 2:
            this->background.setFillColor(sf::Color(141, 141, 74));
            break;
        case 3:
            this->background.setFillColor(sf::Color(93, 141, 74));
            break;
        }
    }
}

void button::set_enabled(bool enabled)
{
    this->is_enabled = enabled;
    if (!this->is_enabled) {
        this->is_hovered = false;
        this->background.setOutlineThickness(1);
    }
}

bool button::enabled() const
{
    return this->is_enabled;
}
