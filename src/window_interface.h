#ifndef WNDINTERFACE_H
#define WNDINTERFACE_H


#include <SFML/Graphics.hpp>


enum window_result_state { nothing_state, finished, restart, menu, quit };

class window_interface
{
public:
	window_interface(sf::IntRect bounds) : bounds(bounds), is_enabled(true) {};

	virtual ~window_interface() = default;

	virtual void update(const float delta_time) = 0;

	virtual void draw(sf::RenderWindow &render_window) const = 0;

	virtual void handle_mouse_press(const sf::Vector2i &mouse_position, bool is_left) {};

	virtual void handle_mouse_move(const sf::Vector2i &mouse_position) {};

	virtual void handle_key_input(const sf::Keyboard::Key key) {};

	void set_enabled(bool enabled) { is_enabled = enabled; };

	bool enabled() const { return is_enabled; }

	virtual window_result_state get_result_state() const { return window_result_state::nothing_state; };

protected:
	sf::IntRect bounds;

	bool is_enabled;
};

#endif // WNDINTERFACE_H
