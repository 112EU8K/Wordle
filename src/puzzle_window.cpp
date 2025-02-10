#include "puzzle_window.h"

puzzle_window::puzzle_window(const sf::IntRect & bounds, const sf::Font & fon, const std::string& solution, std::default_random_engine& random_engine, word_data_base& data_base)
	: window_interface(bounds), font(fon), game_title("Wordle", font, 50),
	keyboard(bounds, font), guess_grid(bounds, font, solution, 6, random_engine, data_base)
{
	game_title.setPosition(sf::Vector2f(5, 5));
	current_state = window_result_state::nothing_state;
}

void puzzle_window::update(const float delta_time)
{
	if (guess_grid.is_solved() || !guess_grid.has_more_guesses()) {
		current_state = window_result_state::finished;
	}
}

void puzzle_window::draw(sf::RenderWindow & render_window) const
{
	render_window.draw(game_title);
	keyboard.draw(render_window);
	guess_grid.draw(render_window);
}

void puzzle_window::handle_mouse_press(const sf::Vector2i & mouse_position, bool is_left)
{
	keyboard.handle_mouse_press(mouse_position, is_left);
	int action = keyboard.get_action_id_reset();
	if (action == static_cast<int>('<')) {
		guess_grid.back_space();
	}
	else if (action == 1) {
		guess_grid.check_solution();
	}
	else if (action != -1) {
		guess_grid.try_insert_letter(static_cast<char>(action));
	}
}

void puzzle_window::handle_mouse_move(const sf::Vector2i & mouse_position)
{
	keyboard.handle_mouse_move(mouse_position);
}

void puzzle_window::handle_key_input(const sf::Keyboard::Key key)
{
	guess_grid.handle_key_input(key);
	if (guess_grid.get_key_check_reset()) {
		keyboard.apply_rules(guess_grid.get_all_rules());
	}
}

const guess_grid & puzzle_window::get_guess_grid() const
{
	return guess_grid;
}

window_result_state puzzle_window::get_result_state() const
{
	return current_state;
}
