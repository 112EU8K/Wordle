#include "keyboard_window.h"

keyboard_window::keyboard_window(const sf::IntRect& bounds, const sf::Font& font)
	: window_interface(bounds)
{
	initialise_buttons(font);
	action_id = -1;
}

void keyboard_window::draw(sf::RenderWindow & render_window) const
{
	for (const auto& button : buttons) {
		button.draw(render_window);
	}
}

void keyboard_window::handle_mouse_press(const sf::Vector2i & mouse_position, bool is_left)
{
	for (auto& button : buttons) {
		if (button.is_position_inside(mouse_position)) {
			action_id = button.get_action_id();
			break;
		}
	}
}

void keyboard_window::handle_mouse_move(const sf::Vector2i & mouse_position)
{
	for (auto& button : buttons) {
		button.set_hovering(button.is_position_inside(mouse_position));
	}
}

int keyboard_window::get_action_id_reset()
{
	int old_action_id = action_id;
	action_id = -1;
	return old_action_id;
}

void keyboard_window::apply_rules(std::vector<std::string> rules)
{
	for (auto rule : rules) {
		for (size_t i = 0, pos = 0; i < rule.length(); i++, pos++) {
			int colour_id = 1;
			if (rule[i] == '*') {
				i++;
				colour_id = 3;
			}
			else if (rule[i] == '#') {
				i++;
				colour_id = 2;
			}

			int letter_casted = static_cast<int>(rule[i]);
			auto b = std::find_if(buttons.begin(), buttons.end(),
				[&](button b) { return b.get_action_id() == letter_casted; });
			if (b != buttons.end()) {
				b->apply_colour_id(colour_id);
			}
		}
	}
}

void keyboard_window::initialise_buttons(const sf::Font& font)
{
	std::vector<std::string> button_text{ "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Check", "Z", "X", "C", "V", "B", "N", "M", "<" };

	const int button_width = 60;
	const int button_height = 60;

	const int mid_x = ((button_width + 10) * (3 + 8) - 10) / 2;
	const int actual_left = bounds.left + bounds.width / 2 - mid_x;

	int pos_x = actual_left + mid_x - ((button_width + 10) * (10) - 10) / 2;
	int pos_y = bounds.top + bounds.height - (button_height + 15) * 3;
	size_t i = 0;

	for (; i < 10; i++, pos_x += button_width + 10) {
		buttons.emplace_back(button(sf::IntRect(pos_x, pos_y, button_width, button_height), button_text[i], static_cast<int>(button_text[i][0]), font));
	}

	pos_x = actual_left + mid_x - ((button_width + 10) * (9) - 10) / 2;
	pos_y += 10 + button_height;
	for (; i < 19; i++, pos_x += button_width + 10) {
		buttons.emplace_back(button(sf::IntRect(pos_x, pos_y, button_width, button_height), button_text[i], static_cast<int>(button_text[i][0]), font));
	}

	pos_x = actual_left;
	pos_y += 10 + button_height;
	buttons.emplace_back(button(sf::IntRect(pos_x, pos_y, button_width * 3, button_height), button_text[i], 1, font));
	i++;
	pos_x += button_width * 3 + 10;
	for (; i < button_text.size(); i++, pos_x += button_width + 10) {
		buttons.emplace_back(button(sf::IntRect(pos_x, pos_y, button_width, button_height), button_text[i], static_cast<int>(button_text[i][0]), font));
	}
}
