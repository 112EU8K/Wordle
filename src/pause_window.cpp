#include "pause_window.h"

pause_window::pause_window(const sf::IntRect &bounds, const sf::Font &font)
    : window_interface(bounds),
      restart_button(sf::IntRect(0, 0, 200, 50), "Restart", 1, font),
      menu_button(sf::IntRect(0, 0, 200, 50), "Menu", 2, font),
      result_state(window_result_state::nothing_state),
      selected_word_length(0)
{
    full_screen_back_ground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width, bounds.height));
    full_screen_back_ground->setFillColor(sf::Color(20, 20, 20, 150));

    const float menu_width = 400;
    const float menu_height = 500;
    back_ground = std::make_unique<sf::RectangleShape>(sf::Vector2f(menu_width, menu_height));
    back_ground->setFillColor(sf::Color(60, 60, 60, 230));
    back_ground->setOutlineColor(sf::Color::White);
    back_ground->setOutlineThickness(1);
    back_ground->setPosition(bounds.left + (bounds.width - menu_width) / 2, bounds.top + (bounds.height - menu_height) / 2);

    title_text = std::make_unique<sf::Text>("Game Paused", font, 40);
    title_text->setPosition(
        bounds.left + bounds.width / 2 - title_text->getGlobalBounds().width / 2,
        back_ground->getPosition().y + 20
    );

    int current_word_length = 5;
    word_length_text = std::make_unique<sf::Text>("Current Word Length: " + std::to_string(current_word_length), font, 25);
    word_length_text->setFillColor(sf::Color::White);
    word_length_text->setPosition(
        bounds.left + bounds.width / 2 - word_length_text->getGlobalBounds().width / 2,
        back_ground->getPosition().y + 80
    );

    restart_button.set_background_colour(sf::Color(93, 141, 74));
    float button_x = bounds.left + bounds.width / 2 - 100;
    float button_y = back_ground->getPosition().y + menu_height - 90;
    restart_button = button(sf::IntRect(button_x, button_y, 200, 50), "Restart", 1, font);

    button_y += 60;
    menu_button = button(sf::IntRect(button_x, button_y, 200, 50), "Menu", 2, font);

    initialize_word_length_buttons(font);
}

void pause_window::initialize_word_length_buttons(const sf::Font &font) {
    const float button_width = 60;
    const float button_height = 60;
    const float button_spacing = 10;
    const int buttons_per_row = 5;

    float total_row_width = buttons_per_row * button_width + (buttons_per_row - 1) * button_spacing;

    float start_x = back_ground->getPosition().x + (back_ground->getSize().x - total_row_width) / 2;
    float start_y = back_ground->getPosition().y + 100;

    for (int i = word_length_min; i <= word_length_max; i++) {
        int row = (i - word_length_min) / buttons_per_row;
        int col = (i - word_length_min) % buttons_per_row;

        float x = start_x + col * (button_width + button_spacing);
        float y = start_y + row * (button_height + button_spacing);

        word_length_buttons.emplace_back(
            sf::IntRect(x, y, button_width, button_height),
            std::to_string(i),
            i,
            font
        );
    }
}


void pause_window::draw(sf::RenderWindow &render_window) const {
    render_window.draw(*full_screen_back_ground);
    render_window.draw(*back_ground);
    render_window.draw(*title_text);
    render_window.draw(*word_length_text);

    for (const auto &button : word_length_buttons) {
        button.draw(render_window);
    }

    restart_button.draw(render_window);
    menu_button.draw(render_window);
}

void pause_window::set_current_word_length(int length) {
    word_length_text->setString("Current Word Length: " + std::to_string(length));
    word_length_text->setPosition(
        back_ground->getPosition().x + (back_ground->getSize().x / 2) - (word_length_text->getGlobalBounds().width / 2),
        back_ground->getPosition().y + 300
    );
}


void pause_window::handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) {
    for (auto &button : word_length_buttons) {
        if (button.is_position_inside(mouse_position)) {
            selected_word_length = button.get_action_id();
            result_state = window_result_state::finished;
            return;
        }
    }

    if (restart_button.is_position_inside(mouse_position)) {
        result_state = window_result_state::restart;
    }
    else if (menu_button.is_position_inside(mouse_position)) {
        result_state = window_result_state::menu;
    }
}

void pause_window::handle_mouse_move(const sf::Vector2i &mouse_position) {
    for (auto &button : word_length_buttons) {
        button.set_hovering(button.is_position_inside(mouse_position));
    }

    restart_button.set_hovering(restart_button.is_position_inside(mouse_position));
}

window_result_state pause_window::get_result_state() const {
    return result_state;
}

int pause_window::get_selected_word_length() const {
    return selected_word_length;
}
