#ifndef GAME_H
#define GAME_H

#include "window_interface.h"
#include <random>
#include "word_data_base.h"
#include "play_history.h"
#include <memory>
#include "button.h"

class sfml_game;

class game
{
public:
	game(sf::RenderWindow& window, const sf::IntRect& game_bounds, const sf::Font& font, std::default_random_engine& random_engine);
	virtual ~game();

	void update(const float delta_time);

	void draw(sf::RenderWindow & render_window) const;

	void handle_mouse_press(const sf::Vector2i& mouse_position, bool is_left);

	void handle_mouse_move(const sf::Vector2i& mouse_position);

	void handle_key_input(const sf::Keyboard::Key key);

	bool get_game_close_requested();

	void update_button_states();

private:
    	sf::RenderWindow &window;

	const sf::IntRect bounds;

	const sf::Font& font;

	std::default_random_engine random_engine;

	window_interface* active_interface;

	window_interface* active_overlay;

	bool in_menu;

	bool is_paused;

	bool terminate_game;

	std::unique_ptr<word_data_base> word_data;

	std::unique_ptr<play_history> history;

    	std::vector<button> buttons;
};

#endif // GAME_H
