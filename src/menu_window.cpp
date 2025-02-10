#include "menu_window.h"

menu_window::menu_window(const sf::IntRect &bounds, const sf::Font &font, word_data_base &data_base)
    : window_interface(bounds),
      title_text("Wordle", font, 50),
      instruction_text("Select Word Length", font, 30),
      result_state(window_result_state::nothing_state),
      selected_word_length(0),
      word_data(data_base)
{
    title_text.setPosition(sf::Vector2f(bounds.left + bounds.width / 8 - title_text.getGlobalBounds().width / 8, bounds.top + 50));

    instruction_text.setPosition(sf::Vector2f(bounds.left + bounds.width / 8 - instruction_text.getGlobalBounds().width / 8, bounds.top + 120));

    const int button_width = 200;
    const int button_height = 50;
    const int vertical_spacing = 20;

    const int total_height = (button_height + vertical_spacing) * 10;
    const int start_y = bounds.top + (bounds.height - total_height) / 2;

    int center_x = bounds.left + bounds.width / 2 - button_width / 2;

    for (int i = 3; i <= 12; ++i) {
        int button_y = start_y + (i - 3) * (button_height + vertical_spacing);

        buttons.emplace_back(
            sf::IntRect(center_x, button_y, button_width, button_height),
            std::to_string(i) + " Letters",
            i,
            font
        );
    }
}

void menu_window::draw(sf::RenderWindow &render_window) const {
    render_window.draw(title_text);
    render_window.draw(instruction_text);
    for (const auto& button : buttons) {
        button.draw(render_window);
    }
}

void menu_window::handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) {
    for (auto& button : buttons) {
        if (button.is_position_inside(mouse_position)) {
            selected_word_length = button.get_action_id();
            result_state = window_result_state::finished;
            word_data.set_word_length(selected_word_length);
            break;
        }
    }
}

void menu_window::handle_mouse_move(const sf::Vector2i &mouse_position) {
    for (auto& button : buttons) {
        button.set_hovering(button.is_position_inside(mouse_position));
    }
}

window_result_state menu_window::get_result_state() const {
    return result_state;
}

int menu_window::get_selected_word_length() const {
    return selected_word_length;
}

