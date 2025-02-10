#include "histogram_bar.h"

histogram_bar::histogram_bar(const sf::IntRect &bounds, const sf::Font &font, const int title, const int value, const int max)
{

	title_text = std::make_unique<sf::Text>(std::to_string(title), font, 20);
	title_text->setPosition(sf::Vector2f(bounds.left, bounds.top + bounds.height / 2 - 10));

	value_text = std::make_unique<sf::Text>(std::to_string(value), font, 20);
	int width = max == 0 ? (bounds.width - 20) : (bounds.width - 20) * value / max;
	if (width < value_text->getGlobalBounds().width + 20) {
		width = value_text->getGlobalBounds().width + 20;
	}
	sf::IntRect bar_rect(bounds.left + 20, bounds.top, width, bounds.height);
	bar = std::make_unique<sf::RectangleShape>(sf::Vector2f(bar_rect.width, bar_rect.height));
	bar->setFillColor(sf::Color(40, 40, 40));
	bar->setPosition(sf::Vector2f(bar_rect.left, bar_rect.top));

	value_text->setPosition(sf::Vector2f(bar_rect.left + bar_rect.width - value_text->getGlobalBounds().width - 10, bounds.top + bounds.height / 2 - 13));
}

void histogram_bar::draw(sf::RenderWindow &renderWindow) const
{
	renderWindow.draw(*title_text);
	renderWindow.draw(*bar);
	renderWindow.draw(*value_text);
}

void histogram_bar::set_bar_colour(const sf::Color &colour)
{
	bar->setFillColor(colour);
}
