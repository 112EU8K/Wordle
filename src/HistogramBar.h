#ifndef HISTOGRAMBAR_H
#define HISTOGRAMBAR_H

#include <SFML/Graphics.hpp>
#include <memory>


class histogram_bar
{
public:

	histogram_bar(const sf::IntRect &bounds, const sf::Font &font, const int title, const int value, const int max);
	virtual ~histogram_bar() = default;

	void draw(sf::RenderWindow &render_window) const;

	void set_bar_colour(const sf::Color &colour);

private:
	std::unique_ptr<sf::Text> title_text;

	std::unique_ptr<sf::RectangleShape> bar;

	std::unique_ptr<sf::Text> value_text;
};

#endif // HISTOGRAMBAR_H
