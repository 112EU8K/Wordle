#ifndef BUTTON_H
#define BUTTON_H


#include <SFML/Graphics.hpp>

/**
 * Button class:
 * Defines a simple button consisting of a rectangle region,
 * some text to centre in it, a hover state, and an
 * actionID that is available to give the button context.
 */
class Button
{
public:
	/**
	* Sets up the Button ready to display and interact with.
	*
	* @param bounds Bounds of the button.
	* @param actionID A number that can be used to give context for when the button is detected to have been clicked.
	* @param font Reference to the font.
	*/
	Button(const sf::IntRect& bounds, const std::string& text, const int actionID, const sf::Font& font);
	virtual ~Button() = default;

	// Draws the button
	void draw(sf::RenderWindow& renderWindow) const;

	// Gets the actionID associated with the button that can be used for determining what should be done when it is pressed.
	int getActionID() const;

	// Updates the hovering state to the specified value.
	void setHovering(const bool isHovering);

	// returns true if the position is inside this button's bounds.
	bool isPositionInside(const sf::Vector2i& mousePosition) const;

	// Changes the background colour to the specified colour.
	void setBackgroundColour(const sf::Color& colour);

	// Uses preset colours to change the background colour only if the specified colourID is greater than the current value.
	void applyColourID(const int colourID);

	void setEnabled(bool enabled);

	bool isEnabled() const;

	sf::IntRect getBounds();

private:
	// The bounds of the rectangle used for isPositionInside().
	sf::IntRect _bounds;

	// A number that can be used to give context for when the button is detected to have been clicked.
	int _actionID;

	// True when the mouse is over the rectangle causing a colour change.
	bool _isHovered;

	// Text to centre in the button.
	std::string _text;

	// Button Background
	sf::RectangleShape _background;

	// Text Render
	sf::Text _textVisual;

	// The current colour ID set via applyColourID.
	int _colourID;

    	// For word length
	bool _isEnabled;
};

#endif // BUTTON_H
