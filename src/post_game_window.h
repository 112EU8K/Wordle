#ifndef POSTGAMEWND_H
#define POSTGAMEWND_H


#include "window_interface.h"
#include "button.h"
#include "horizontal_histogram.h"
#include "play_history.h"


class post_game_window :
	public window_interface
{
public:
	post_game_window(const sf::IntRect &bounds, const sf::Font &font, const std::string &solution, const bool won_game,
				const int attempts, const std::unique_ptr<play_history> &play_history, const std::string &str);
	virtual ~post_game_window() = default;

	virtual void update(const float delta_time) override {};

	virtual void draw(sf::RenderWindow &render_window) const override;

	virtual void handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) override;

	virtual void handle_mouse_move(const sf::Vector2i &mousePosition) override;

	window_result_state get_result_state() const override;

private:
	window_result_state result_state;

	std::vector<button> buttons;

	std::unique_ptr<sf::RectangleShape> back_ground;

	std::unique_ptr<sf::RectangleShape> full_screen_back_ground;

	std::unique_ptr<sf::Text> title_text;

	std::unique_ptr<sf::Text> solution_text;

	std::unique_ptr<horizontal_hitogram> histogram;

	std::unique_ptr<sf::Text> total_played_text;

	std::unique_ptr<sf::Text> win_percent_text;

	std::unique_ptr<sf::Text> current_streak_text;

	std::unique_ptr<sf::Text> max_streak_text;

	std::string share_str;
};

#endif // POSTGAMEWND_H
