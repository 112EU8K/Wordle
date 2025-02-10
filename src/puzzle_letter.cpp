#include "puzzle_letter.h"

puzzle_letter::puzzle_letter(const sf::IntRect &bound, const sf::Font &font)
	: bounds(bound), letter(' '),
	back_ground(sf::Vector2f(bounds.width - 2, bounds.height - 2)),
	text_visual('A', font, 30)
{
	text_visual.setFillColor(sf::Color::White);
	text_visual.setStyle(sf::Text::Bold);
	text_visual.setPosition(sf::Vector2f(bounds.left + bounds.width / 2 - text_visual.getGlobalBounds().width / 2, bounds.top + bounds.height / 2 - 20));
	text_visual.setString(' ');
	back_ground.setPosition(sf::Vector2f(bounds.left + 1, bounds.top + 1));
	back_ground.setFillColor(sf::Color(5, 5, 5));
	back_ground.setOutlineThickness(1);
	back_ground.setOutlineColor(sf::Color::White);

	current_state = solution_state::NO_STATE;
}

void puzzle_letter::draw(sf::RenderWindow &render_window) const
{
	render_window.draw(back_ground);
	render_window.draw(text_visual);
}

char puzzle_letter::get_letter() const
{
	return letter;
}

void puzzle_letter::set_letter(const char let)
{
	letter = let;
	text_visual.setString(letter);
}

void puzzle_letter::set_solution_state(const solution_state & solution_state)
{
	current_state = solution_state;
	switch (current_state) {
	case solution_state::NO_STATE:
		back_ground.setFillColor(sf::Color(40, 40, 40));
		break;
	case solution_state::CORRECT:
		back_ground.setFillColor(sf::Color(93, 141, 74));
		break;
	case solution_state::WRONG_POS:
		back_ground.setFillColor(sf::Color(141, 141, 74));
		break;
	}
}

puzzle_letter::solution_state puzzle_letter::get_solution_state() const
{
	return current_state;
}

void puzzle_letter::set_background_colour(const sf::Color &colour)
{
	back_ground.setFillColor(colour);
}
