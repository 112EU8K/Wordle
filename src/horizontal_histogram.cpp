#include "horizontal_histogram.h"

horizontal_hitogram::horizontal_hitogram(const sf::IntRect &bounds, const sf::Font &font, std::vector<std::pair<int, int>> data, const int high_light_index)
{
	auto cmp = [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
		return a.second < b.second;
	};
	int max = std::max_element(data.begin(), data.end(), cmp)->second;

	int padding = 5;
	int bar_height = bounds.height / data.size() - 10;

	for (size_t i = 0; i < data.size(); i++) {
		bars.emplace_back(std::make_unique<histogram_bar>(sf::IntRect(bounds.left, bounds.top + i * (bar_height + padding),
							bounds.width, bar_height), font, data[i].first, data[i].second, max));
	}

	if (high_light_index >= 0 && static_cast<size_t>(high_light_index) <= bars.size()) {
		bars.at(high_light_index)->set_bar_colour(sf::Color(93, 141, 74));
	}
}

void horizontal_hitogram::draw(sf::RenderWindow &render_window) const
{
	for (const auto &bar : bars) {
		bar->draw(render_window);
	}
}
