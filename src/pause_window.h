#ifndef PAUSEWND_H
#define PAUSEWND_H

#include "window_interface.h"
#include "button.h"
#include <memory>
#include <vector>

class pause_window : public window_interface {
public:
    pause_window(const sf::IntRect &bounds, const sf::Font &font);

    void update(const float delta_time) override {}
    void draw(sf::RenderWindow &render_window) const override;
    void handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) override;
    void handle_mouse_move(const sf::Vector2i &mouse_position) override;
    window_result_state get_result_state() const override;
    int get_selected_word_length() const;
    void set_current_word_length(int length);

private:
    void initialize_word_length_buttons(const sf::Font &font);

    std::unique_ptr<sf::RectangleShape> full_screen_back_ground;
    std::unique_ptr<sf::RectangleShape> back_ground;
    std::unique_ptr<sf::Text> title_text;
    std::vector<button> word_length_buttons;

    button restart_button;
    button menu_button;

    window_result_state result_state;
    int selected_word_length;

    std::unique_ptr<sf::Text> word_length_text;

    static const int word_length_min = 3;
    static const int word_length_max = 12;
};

#endif // PAUSEWND_H
