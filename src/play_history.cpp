#include "play_history.h"
#include <iostream>
#include <fstream>

play_history::play_history(const std::string & file_name)
	: save_file_name(file_name)
{
	load_file();
}

void play_history::insert_history(const size_t increment)
{
	if (increment < 0 || increment >= history.size()) {
		std::cerr << "ERROR: Failed to insert " << increment << " into history." << std::endl;
		return;
	}

	total_won++;
	total_played++;
	current_streak++;
	if (current_streak > max_streak) {
		max_streak = current_streak;
	}
	history[increment].second++;
	save_file();
}

void play_history::insert_history_loss()
{
	total_played++;
	current_streak = 0;
	save_file();
}

const std::vector<std::pair<int, int>>& play_history::get_history() const
{
	return history;
}

int play_history::get_total_played() const
{
	return total_played;
}

int play_history::get_current_streak() const
{
	return current_streak;
}

int play_history::get_max_streak() const
{
	return max_streak;
}

int play_history::get_win_percent() const
{
	return total_won * 100 / total_played;
}

void play_history::load_file()
{
	std::ifstream file(save_file_name);
	if (!file.is_open()) {
		std::cout << "Failed to open a save file. Using default values." << std::endl;
		initialise_default();
		return;
	}

	int key, value;
	for (int i = 0; i < 6; i++) {
		file >> key >> value;
		if (file.fail()) {
			std::cout << "Failed to read expected data from save file (histogram data). Using default values." << std::endl;
			initialise_default();
			file.close();
			return;
		}
		history.emplace_back(std::pair<int, int>(key, value));
	}
	file >> total_played >> total_won >> current_streak >> max_streak;

	if (file.fail()) {
		std::cout << "Failed to read expected data from save file (streak history). Using default values." << std::endl;
		initialise_default();
	}

	file.close();
}

void play_history::save_file()
{
	std::ofstream file(save_file_name);
	if (!file.is_open()) {
		std::cout << "Failed to open file to save your win. Will not save." << std::endl;
		return;
	}

	for (const auto &element : history) {
		file << element.first << " " << element.second << " ";
	}
	file << total_played << " " << total_won << " " << current_streak << " " << max_streak;

	file.close();
}

void play_history::initialise_default()
{
	for (int i = 0; i < 6; i++) {
		history.emplace_back(std::pair<int, int>(i + 1, 0));
	}
	max_streak = 0;
	current_streak = 0;
	total_played = 0;
	total_won = 0;
}
