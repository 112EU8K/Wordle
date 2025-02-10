#include "game.h"
#include <chrono>
#include <iostream>
#include "puzzle_window.h"
#include "post_game_window.h"
#include "menu_window.h"
#include "pause_window.h"


game::game(sf::RenderWindow &win, const sf::IntRect &game_bounds, const sf::Font &font, std::default_random_engine &random)
    : window(win), bounds(game_bounds), font(font), random_engine(random), in_menu(true), is_paused(false)
{
    std::cout.setstate(std::ios_base::failbit);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    random_engine.seed(seed);
    word_data = std::make_unique<word_data_base>(random);
    history = std::make_unique<play_history>("SAVEFILE/save.dat");

    terminate_game = false;
    active_interface = nullptr;
    active_overlay = nullptr;

    active_interface = new menu_window(bounds, font, *word_data);
}

game::~game() {
    delete active_interface;
    delete active_overlay;
}


void game::update_button_states()
{
    bool should_enable_buttons = true;

    if (active_interface != nullptr) {
        auto* puzzle = dynamic_cast<puzzle_window*>(active_interface);
        if (puzzle && !puzzle->get_guess_grid().is_solved() &&
            puzzle->get_guess_grid().has_more_guesses() &&
            active_overlay == nullptr) {
            should_enable_buttons = false;
        }
    }

    for (auto& button : buttons) {
        button.set_enabled(should_enable_buttons);
    }
}

void game::update(const float delta_time)
{
    if (active_overlay != nullptr) {
        active_overlay->update(delta_time);
        if (active_overlay->get_result_state() == window_result_state::restart) {
            delete active_overlay;
            active_overlay = nullptr;
            if (!in_menu) {
                delete active_interface;
                active_interface = new puzzle_window(bounds, font, word_data->get_random_word(), random_engine, *word_data);
            } else {
                delete active_interface;
                active_interface = new menu_window(bounds, font, *word_data);
            }
        } else if (active_overlay != nullptr && active_overlay->get_result_state() == window_result_state::menu) {
                delete active_overlay;
                active_overlay = nullptr;
                delete active_interface;
                active_interface = new menu_window(bounds, font, *word_data);
                in_menu = true;
                is_paused = false;
        }
        else if (active_overlay->get_result_state() == window_result_state::finished) {
            auto* pause = dynamic_cast<pause_window*>(active_overlay);
            if (pause) {
                int new_word_length = pause->get_selected_word_length();
                if (new_word_length != word_data->get_current_word_length()) {
                    word_data->load_data_base(new_word_length);
                    delete active_interface;
                    active_interface = new puzzle_window(bounds, font, word_data->get_random_word(), random_engine, *word_data);
                }
            }
            delete active_overlay;
            active_overlay = nullptr;
            is_paused = false;
        }
    }

    if (active_interface != nullptr && active_interface->get_result_state() == window_result_state::finished) {
        delete active_interface;
        active_interface = new puzzle_window(bounds, font, word_data->get_random_word(), random_engine, *word_data);
        in_menu = false;
        }
}

void game::handle_mouse_press(const sf::Vector2i & mouse_position, bool is_left)
{
    //sf::Vector2f world_pos = _window.mapPixelToCoords(mouse_position);

    for (auto& button : buttons) {
        if (button.enabled() && button.is_position_inside(mouse_position)) {
            int new_word_length = button.get_action_id();

            if (new_word_length != word_data->get_current_word_length()) {
                word_data->load_data_base(new_word_length);
                delete active_interface;
                in_menu = false;
                active_interface = new puzzle_window(bounds, font, word_data->get_random_word(), random_engine, *word_data);
                if (active_overlay != nullptr) {
                    delete active_overlay;
                    active_overlay = nullptr;
                }
                in_menu = false;
            }

            break;
        }
    }

    if (active_overlay != nullptr) {
        active_overlay->handle_mouse_press(mouse_position, is_left);
    }
    else if (active_interface != nullptr) {
        active_interface->handle_mouse_press(mouse_position, is_left);
    }

    update_button_states();
}

void game::draw(sf::RenderWindow & render_window) const
{
    if (active_interface != nullptr) {
        active_interface->draw(render_window);
    }

    if (active_overlay != nullptr) {
        active_overlay->draw(render_window);
    }

    for (const auto& button : buttons) {
        button.draw(render_window);
    }
}

void game::handle_mouse_move(const sf::Vector2i & mouse_position)
{
    if (active_overlay != nullptr) {
        active_overlay->handle_mouse_move(mouse_position);
    }
    else if (active_interface != nullptr) {
        active_interface->handle_mouse_move(mouse_position);
    }
}

void game::handle_key_input(const sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Escape && !in_menu) {
        if (!is_paused && active_overlay == nullptr) {
            is_paused = true;
            auto* pause_menu = new pause_window(bounds, font);
            pause_menu->set_current_word_length(word_data->get_current_word_length());
            active_overlay = pause_menu;
        }
        else if (is_paused) {
            delete active_overlay;
            active_overlay = nullptr;
            is_paused = false;
        }
        return;
    }
    if (active_overlay != nullptr) {
        active_overlay->handle_key_input(key);
    }
    else if (active_interface != nullptr) {
        active_interface->handle_key_input(key);
    }
}

bool game::get_game_close_requested()
{
    return terminate_game;
}

