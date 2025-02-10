#include "guess_grid.h"
#include <sstream>


guess_grid::guess_grid(const sf::IntRect& bounds, const sf::Font& font, const std::string& so,
                     const int max_guesses, std::default_random_engine& random, word_data_base& data)
    : window_interface(bounds),
      message_box(font),
      random_engine(random),
      data_base(data),
      solution(so)
{
    initialise_all_guesses(font, solution.length(), max_guesses);
    solved = false;
    current_word_index = 0;
    insert_position = 0;
    used_key_check = false;
}


void guess_grid::draw(sf::RenderWindow & render_window) const
{
	for (const auto& row : guess_letters) {
		for (const auto& letter : row) {
			letter.draw(render_window);
		}
	}
	 message_box.draw(render_window);
}

void guess_grid::handle_key_input(const sf::Keyboard::Key key)
{
     if (key != sf::Keyboard::Enter) {
        message_box.hide();
    }
	int key_code = static_cast<int>(key);
	if (key_code >= 0 && key_code <= 25) {
		try_insert_letter(static_cast<char>(key_code + 'A'));
	}
	else if (key == sf::Keyboard::Backspace) {
		back_space();
	}
	else if (key == sf::Keyboard::Enter) {
		check_solution();
		used_key_check = true;
	}
}

void guess_grid::try_insert_letter(const char letter)
{
	if (static_cast<size_t>(current_word_index) == guess_letters.size() || solved || static_cast<size_t>(insert_position) == guess_letters[current_word_index].size())
		return;

	guess_letters[current_word_index][insert_position].set_letter(letter);
	insert_position++;
}

void guess_grid::back_space()
{
	if (solved || insert_position == 0 || static_cast<size_t>(current_word_index) == guess_letters.size())
		return;

	insert_position--;
	guess_letters[current_word_index][insert_position].set_letter(' ');
}

void guess_grid::check_solution()
{
	if (solved) return;

    std::string guessed_word;
    for (const auto& letter : guess_letters[current_word_index]) {
        if (letter.get_letter() != ' ') {
            guessed_word += letter.get_letter();
        }
    }

    std::transform(guessed_word.begin(), guessed_word.end(), guessed_word.begin(), ::toupper);


    if (guessed_word.size() < static_cast<size_t>(data_base.get_current_word_length())) {
        message_box.show_message("TOO SHORT");
        return;
    } else if (!data_base.is_valid_word(guessed_word)) {
        message_box.show_message("WORD NOT FOUND!");
        return;
    }

	int solve_count = 0;
	for (size_t i = 0; i < solution.length(); i++) {
		char guess = guess_letters[current_word_index][i].get_letter();
		if (guess == solution.at(i)) {
			guess_letters[current_word_index][i].set_solution_state(puzzle_letter::solution_state::CORRECT);
			solve_count++;
		}
		else {
			int required_letter_count = std::count(solution.begin(), solution.end(), guess);
			if (required_letter_count > 0) {
				int correct_position_this_letter = 0;
				std::vector<int> out_of_position_positions;
				for (size_t j = 0; j < guess_letters[current_word_index].size(); j++) {
					if (guess == guess_letters[current_word_index][j].get_letter()) {
						if (guess == solution[j]) {
							correct_position_this_letter++;
						}
						else {
							out_of_position_positions.emplace_back(j);
						}
					}
				}
				while (correct_position_this_letter + out_of_position_positions.size() > static_cast<size_t>(required_letter_count)) {
					out_of_position_positions.pop_back();
				}
				if (std::find(out_of_position_positions.begin(), out_of_position_positions.end(), i) != out_of_position_positions.end()) {
					guess_letters[current_word_index][i].set_solution_state(puzzle_letter::solution_state::WRONG_POS);
				}
				else {
					guess_letters[current_word_index][i].set_solution_state(puzzle_letter::solution_state::NO_STATE);
				}
			}
			else {
				guess_letters[current_word_index][i].set_solution_state(puzzle_letter::solution_state::NO_STATE);
			}
		}
	}

	current_word_index++;
	insert_position = 0;
	if (static_cast<size_t>(solve_count) == solution.length()) {
		solved = true;
	}
}

bool guess_grid::is_solved() const
{
	return solved;
}

bool guess_grid::has_more_guesses() const
{
	return static_cast<size_t>(current_word_index) < guess_letters.size();
}

std::vector<std::string> guess_grid::get_all_rules() const
{
	std::vector<std::string> rules;

	for (int i = 0; i < current_word_index; i++) {
		std::stringstream rule_stream;
		for (size_t j = 0; j < solution.length(); j++) {
			if (guess_letters[i][j].get_solution_state() == puzzle_letter::solution_state::CORRECT) {
				rule_stream << "*";
			}
			else if (guess_letters[i][j].get_solution_state() == puzzle_letter::solution_state::WRONG_POS) {
				rule_stream << "#";
			}
			rule_stream << guess_letters[i][j].get_letter();
		}
		rules.emplace_back(rule_stream.str());
	}

	return rules;
}

bool guess_grid::get_key_check_reset()
{
	bool result = used_key_check;
	used_key_check = false;
	return result;
}

std::string guess_grid::get_solution() const
{
	return solution;
}

std::string guess_grid::get_share_string() const
{
	std::stringstream message;
	message << "Wordle Game" << std::endl << "\"" << solution << "\": ";
	message << (solved ? "Solved: " : "Did not solve: ") << (current_word_index) << " / 6" << std::endl << std::endl;

	for (int i = 0; i < current_word_index; i++) {
		std::stringstream rule_stream;
		for (size_t j = 0; j < solution.length(); j++) {
			if (guess_letters[i][j].get_solution_state() == puzzle_letter::solution_state::CORRECT) {
				message << ":green_square:";
			}
			else if (guess_letters[i][j].get_solution_state() == puzzle_letter::solution_state::WRONG_POS) {
				message << ":yellow_square:";
			}
			else {
				message << ":black_large_square:";
			}
		}
		message << std::endl;
	}

	return message.str();
}

void guess_grid::initialise_all_guesses(const sf::Font & font, const int word_length, const int max_guesses)
{
    const int element_height = 60;
	const int element_width = 60;

	const int left_side = bounds.left + bounds.width / 2 - ((element_width + 10) * word_length) / 2;
    int pos_y = bounds.top + 30;
	int pos_x = left_side;

	for (int i = 0; i < max_guesses; i++, pos_y += element_height + 10, pos_x = left_side) {
		std::vector<puzzle_letter> row;

		for (int j = 0; j < word_length; j++, pos_x += element_width + 10) {
			row.emplace_back(puzzle_letter(sf::IntRect(pos_x, pos_y, element_height, element_width), font));
		}

		guess_letters.emplace_back(row);
	}
}

