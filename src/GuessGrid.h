#ifndef GUESSGRID_H
#define GUESSGRID_H


#include "window_interface.h"
#include "puzzle_letter.h"
#include "message_box.h"
#include "word_data_base.h"


class guess_grid :
	public window_interface
{
public:
	guess_grid(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution, const int max_guesses, std::default_random_engine& random_engine, word_data_base& data_base);
	virtual ~guess_grid() = default;

	virtual void update(const float delta_time) override {};

	virtual void draw(sf::RenderWindow & render_window) const override;

	virtual void handle_key_input(const sf::Keyboard::Key key) override;

	void try_insert_letter(const char letter);

	void back_space();

	void check_solution();

	bool is_solved() const;

	bool has_more_guesses() const;

	std::vector<std::string> get_all_rules() const;

	bool get_key_check_reset();

	std::string get_solution() const;

	std::string get_share_string() const;

private:
	std::vector<std::vector<puzzle_letter>> guess_letters;

	massage_box message_box;

    	std::default_random_engine& random_engine;

    	word_data_base &data_base;

	int insert_position;

	int current_word_index;

	bool solved;

	bool used_key_check;

	const std::string solution;

	void initialise_all_guesses(const sf::Font &font, const int word_length, const int max_guesses);
};


#endif // GUESSGRID_H

