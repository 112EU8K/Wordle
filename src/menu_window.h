#ifndef MENUWND_H
#define MENUWND_H

#include "window_interface.h"
#include "button.h"
#include "word_data_base.h"
#include <vector>
#include <memory>

class menu_window : public window_interface {
public:
    menu_window(const sf::IntRect &bounds, const sf::Font &font, word_data_base &data_base);

    void update(const float delta_time) override {};
    void draw(sf::RenderWindow &renderWindow) const override;
    void handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) override;
    void handle_mouse_move(const sf::Vector2i &mouse_position) override;

    window_result_state get_result_state() const override;
    int get_selected_word_length() const;

private:
    sf::Text title_text;
    sf::Text instruction_text;
    std::vector<button> buttons;
    window_result_state result_state;
    int selected_word_length;
    word_data_base &word_data;
};


#endif // MENUWND_H

