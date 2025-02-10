#ifndef BUTTON_H
#define BUTTON_H


#include <SFML/Graphics.hpp>


class button
{
public:
	button(const sf::IntRect &bounds, const std::string &text, const int action_id, const sf::Font &font);
	virtual ~button() = default;

	void draw(sf::RenderWindow& render_window) const;

	int get_action_id() const;

	void set_hovering(const bool is_hovering);

	bool is_position_inside(const sf::Vector2i& mousePosition) const;

	void set_background_colour(const sf::Color& colour);

	void apply_colour_id(const int colour_id);

	void set_enabled(bool enabled);

	bool enabled() const;

	sf::IntRect get_bounds();

private:

	sf::IntRect bounds;

	int action_id;

	bool is_hovered;

	std::string text;

	sf::RectangleShape background;

	sf::Text text_visual;

	int colour_id;

	bool is_enabled;
};

#endif
