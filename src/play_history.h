#ifndef PLAYHISTORY_H
#define PLAYHISTORY_H

#include <vector>
#include <string>

class play_history
{
public:

	play_history(const std::string &save_file_name);
	virtual ~play_history() = default;

	void insert_history(const size_t count_to_increment);

	void insert_history_loss();

	const std::vector<std::pair<int, int>> &get_history() const;

	int get_total_played() const;

	int get_current_streak() const;

	int get_max_streak() const;

	int get_win_percent() const;

private:
	std::vector<std::pair<int, int>> history;

	int total_played;

	int total_won;

	int current_streak;

	int max_streak;

	std::string save_file_name;

	void load_file();

	void save_file();

	void initialise_default();
};


#endif // PLAYHISTORY_H

