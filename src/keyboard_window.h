#ifndef KEYBOARDWND_H
#define KEYBOARDWND_H

#include "window_interface.h"
#include "button.h"


class keyboard_window :
	public window_interface
{
public:
	keyboard_window(const sf::IntRect &bounds, const sf::Font &font);
	virtual ~keyboard_window() = default;

	virtual void update(const float delta_time) override {};

	virtual void draw(sf::RenderWindow & render_window) const override;

	virtual void handle_mouse_press(const sf::Vector2i& mouse_position, bool is_left) override;

	virtual void handle_mouse_move(const sf::Vector2i& mouse_position) override;

	int get_action_id_reset();

	void apply_rules(std::vector<std::string> rules);

private:

	std::vector<button> buttons;

	int action_id;

	void initialise_buttons(const sf::Font& font);
};

#endif // KEYBOARDWND_H
