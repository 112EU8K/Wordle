#ifndef HORIZONTALHISTOGRAM_H
#define HORIZONTALHISTOGRAM_H

#include "HistogramBar.h"
#include <vector>


class HorizontalHistogram
{
public:
	// Initialises the data into the bounds and optionally highlights one of the bar
	HorizontalHistogram(const sf::IntRect& bounds, const sf::Font& font, std::vector<std::pair<int, int>> data, const int highlightIndex);
	virtual ~HorizontalHistogram() = default;

	// Draws all the bars.
	void draw(sf::RenderWindow & renderWindow) const;

private:
	// The collection of bars to be drawn.
	std::vector<std::unique_ptr<HistogramBar>> _bars;
};

#endif // HORIZONTALHISTOGRAM_H
