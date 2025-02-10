#ifndef WORDDATABASE_H
#define WORDDATABASE_H

#include <vector>
#include <random>


class word_data_base
{
public:
	word_data_base(std::default_random_engine &random);
	virtual ~word_data_base() = default;

	bool is_valid_word(const std::string &word) const;

	std::string get_random_word() const;

    void set_word_length(size_t word_length);

	void load_data_base(size_t word_count);

	int get_current_word_length() const;


private:
	std::vector<std::string> words;

	int random_number();

	std::default_random_engine &random_engine;

	size_t current_word_length;

};


#endif // WORDDATABASE_H

