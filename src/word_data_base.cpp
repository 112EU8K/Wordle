#include "word_data_base.h"
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

word_data_base::word_data_base(std::default_random_engine &random)
    : random_engine(random)
{
    current_word_length = random_number();
    load_data_base(current_word_length);
}

bool word_data_base::is_valid_word(const std::string &word) const
{
    return std::find(words.begin(), words.end(), word) != words.end();
}

int word_data_base::get_current_word_length() const
{
    return current_word_length;
}

std::string word_data_base::get_random_word() const
{
    if (words.empty()) {
        std::cerr << "Error: No words available for length " << current_word_length << std::endl;
        return "";
    }
    std::cerr << "Current word length: " << current_word_length << std::endl;
    return words.at(random_engine() % words.size());
}

void word_data_base::load_data_base(size_t word_count)
{
    current_word_length = word_count;
    words.clear();
    std::ifstream file("FILEWORDS/words" + std::to_string(current_word_length) + ".txt");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open txt file" << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == current_word_length) {
            words.emplace_back(word);
        }
    }

    std::cerr << "Loaded " << words.size() << " words for " << word_count << "-letter words" << std::endl;

    if (words.empty()) {
        std::cerr << "Error: No words found for length " << word_count << std::endl;
        return;
    }

    std::sort(words.begin(), words.end());
}

void word_data_base::set_word_length(size_t word_length)
{
    current_word_length = word_length;
    load_data_base(current_word_length);
}

int word_data_base::random_number()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3, 12);
    return dist(gen);
}

