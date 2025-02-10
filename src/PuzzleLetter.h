#ifndef PUZZLELETTER_H
#define PUZZLELETTER_H

#include <SFML/Graphics.hpp>

class puzzle_letter
{
public:
	enum solution_state { NO_STATE, CORRECT, WRONG_POS };

	puzzle_letter(const sf::IntRect &bounds, const sf::Font &font);
	virtual ~puzzle_letter() = default;

	void draw(sf::RenderWindow &render_window) const;

	char get_letter() const;

	void set_letter(const char letter);

	void set_solution_state(const solution_state &solution_state);

	solution_state get_solution_state() const;

private:
	sf::IntRect bounds;

	char letter;

	sf::RectangleShape back_ground;

	sf::Text text_visual;

	solution_state current_state;

	void set_background_colour(const sf::Color &colour);
};

#endif // PUZZLELETTER_H
