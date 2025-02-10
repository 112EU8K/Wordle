#ifndef PUZZLEWND_H
#define PUZZLEWND_H

#include "window_interface.h"
#include "keyboard_window.h"
#include "guess_grid.h"

class puzzle_window :
	public window_interface
{
public:
	puzzle_window(const sf::IntRect& bounds, const sf::Font& fon, const std::string& solution, std::default_random_engine& random_engine, word_data_base& data_base);
	virtual ~puzzle_window() = default;

	virtual void update(const float delta_time) override;

	virtual void draw(sf::RenderWindow & render_window) const override;

	virtual void handle_mouse_press(const sf::Vector2i& mouse_position, bool is_left) override;

	virtual void handle_mouse_move(const sf::Vector2i& mouse_position) override;

	virtual void handle_key_input(const sf::Keyboard::Key key) override;

	const guess_grid &get_guess_grid() const;

	window_result_state get_result_state() const override;

private:

	const sf::Font &font;

	sf::Text game_title;

	keyboard_window keyboard;

	guess_grid guess_grid;

	window_result_state current_state;
};


#endif // PUZZLEWND_H
