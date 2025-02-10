#ifndef HORIZONTALHISTOGRAM_H
#define HORIZONTALHISTOGRAM_H

#include "histogram_bar.h"
#include <vector>


class horizontal_histogram
{
public:
	horizontal_histogram(const sf::IntRect &bounds, const sf::Font &font, std::vector<std::pair<int, int>> data, const int high_light_index);
	virtual ~horizontal_histogram() = default;

	void draw(sf::RenderWindow &render_window) const;

private:
	std::vector<std::unique_ptr<histogram_bar>> bars;
};

#endif // HORIZONTALHISTOGRAM_H
