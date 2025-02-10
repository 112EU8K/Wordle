#include "post_game_window.h"

post_game_window::post_game_window(const sf::IntRect &bounds, const sf::Font &font, const std::string &solution, const bool won_game, const int attempts, const std::unique_ptr<play_history> &play_history, const std::string& str)
	: window_interface(bounds), share_str(str)
{
	result_state = window_result_state::nothing_state;

	full_screen_back_ground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width, bounds.height));
	full_screen_back_ground->setFillColor(sf::Color(20, 20, 20, 150));

	back_ground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	back_ground->setFillColor(sf::Color(60, 60, 60, 230));
	back_ground->setOutlineColor(sf::Color::White);
	back_ground->setOutlineThickness(1);
	back_ground->setPosition(bounds.left + bounds.width / 4 + 1, bounds.top + bounds.height / 4 + 1);

	title_text = std::make_unique<sf::Text>((won_game ? "You solved it!" : "Better Luck Next Time!"), font, 40);
	title_text->setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - title_text->getGlobalBounds().width / 2, bounds.top + bounds.height / 4 + 10));
	title_text->setFillColor(won_game ? sf::Color(93, 141, 74) : sf::Color(230, 93, 74));

	solution_text = std::make_unique<sf::Text>("Solution: " + solution, font, 30);
	solution_text->setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - solution_text->getGlobalBounds().width / 2, bounds.top + bounds.height / 4 + 10 + 50));

	buttons.emplace_back(button(sf::IntRect(bounds.left + bounds.width / 2 - 225, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "New Word", 0, font));
	buttons.emplace_back(button(sf::IntRect(bounds.left + bounds.width / 2 + 25, bounds.top + bounds.height * 3 / 4 - 70, 200, 60), "Quit", 1, font));
	buttons.emplace_back(button(sf::IntRect(bounds.left + bounds.width * 3 / 4 + 25, bounds.top + bounds.height / 2 - 30, 200, 60), "Share", 2, font));
	buttons[buttons.size() - 1].set_background_colour(sf::Color(93, 141, 74));


	sf::IntRect histogram_rect = sf::IntRect(bounds.left + bounds.width / 4 + 30, bounds.top + bounds.height / 4 + 10 + 50 + 40 + 10,
		bounds.width / 2 - 60, bounds.top + bounds.height * 3 / 4 - 70 - (bounds.top + bounds.height / 4 + 10 + 50 + 40));

	histogram = std::make_unique<horizontal_hitogram>(histogram_rect, font, play_history->get_history(), won_game ? attempts - 1 : -1);

	total_played_text = std::make_unique<sf::Text>("Played: " + std::to_string(play_history->get_total_played()), font, 30);
	total_played_text->setPosition(sf::Vector2f(30, bounds.top + bounds.height / 2 - 75));
	win_percent_text = std::make_unique<sf::Text>("Win %: " + std::to_string(play_history->get_win_percent()), font, 30);
	win_percent_text->setPosition(sf::Vector2f(30, bounds.top + bounds.height / 2 - 25));
	current_streak_text = std::make_unique<sf::Text>("Current Streak: " + std::to_string(play_history->get_current_streak()), font, 30);
	current_streak_text->setPosition(sf::Vector2f(30, bounds.top + bounds.height / 2 + 25));
	max_streak_text = std::make_unique<sf::Text>("Max Streak: " + std::to_string(play_history->get_max_streak()), font, 30);
	max_streak_text->setPosition(sf::Vector2f(30, bounds.top + bounds.height / 2 + 75));
}

void post_game_window::draw(sf::RenderWindow &render_window) const
{
	render_window.draw(*full_screen_back_ground);
	render_window.draw(*back_ground);
	render_window.draw(*title_text);
	render_window.draw(*solution_text);
	render_window.draw(*total_played_text);
	render_window.draw(*win_percent_text);
	render_window.draw(*current_streak_text);
	render_window.draw(*max_streak_text);
	histogram->draw(render_window);
	for (const auto& button : buttons) {
		button.draw(render_window);
	}
}

void post_game_window::handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left)
{
	for (auto &button : buttons) {
		if (button.is_position_inside(mouse_position)) {
			if (button.get_action_id() == 0) {
				result_state = window_result_state::restart;
			}
			else if (button.get_action_id() == 1) {
				result_state = window_result_state::quit;
			}
			else if (button.get_action_id() == 2) {
				sf::Clipboard::setString(share_str);
			}
		}
	}
}

void post_game_window::handle_mouse_move(const sf::Vector2i &mouse_position)
{
	for (auto &button : buttons) {
		button.set_hovering(button.is_position_inside(mouse_position));
	}
}

window_result_state post_game_window::get_result_state() const
{
	return result_state;
}

