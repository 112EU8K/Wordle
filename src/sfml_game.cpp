#include "sfml_game.h"
#include <iostream>

#define window_width 1280
#define window_height 720
#define font_file_path "FONTS/arial.ttf"

sf::RenderWindow sfml_game::window(sf::VideoMode(window_width, window_height), "Wordle - expanded Edition");

sfml_game::sfml_game(game &gg) :
    font(load_font()),
    ggg(gg)
{
    if (!icon.loadFromFile("WINDOWICON/Wordle_2021_icon.png"))
    {
        std::cerr << "Failed to load window icon" << std::endl;
    }
    else
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}


sf::RenderWindow &sfml_game::get_window()
{
    return window;
}

void sfml_game::game_loop()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float delta_time = elapsed.asSeconds();
		sf::Event event;
		if (window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				ggg.handle_mouse_press(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), event.mouseButton.button == sf::Mouse::Left);
			}
			else if (event.type == sf::Event::MouseMoved) {
				ggg.handle_mouse_move(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			else if (event.type == sf::Event::KeyPressed) {
				ggg.handle_key_input(event.key.code);
			} else if (event.type == sf::Event::Resized) {
                handle_resize(event.size.width, event.size.height);
            }
		}
		ggg.update(delta_time);

		window.clear(sf::Color::Black);
		ggg.draw(window);
		window.display();

		if (ggg.get_game_close_requested()) {
			window.close();
		}
	}
}


void sfml_game::handle_resize(unsigned int width, unsigned int height)
{
	if (width == 0 || height == 0) {
		return;
	}

	float window_ratio = static_cast<float>(width) / height;
	float game_ratio = static_cast<float>(window_width) / window_height;

	sf::View view(sf::FloatRect(0, 0, window_width, window_height));
	if (window_ratio > game_ratio) {
		float view_width = window_height * window_ratio;
		view.setSize(view_width, window_height);
	} else {
		float view_height = window_width / window_ratio;
		view.setSize(window_width, view_height);
	}
	view.setCenter(window_width / 2.f, window_height / 2.f);
	
	window.setView(view);
}

sf::Font sfml_game::load_font()
{
	sf::Font font;
	if (!font.loadFromFile(font_file_path))
	{
		throw("Failed to load font.");
	}

	return font;
}
