#include "WordDatabase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <random>

WordDatabase::WordDatabase(std::default_random_engine & randomEngine)
	: _randomEngine(randomEngine)
{
	loadDatabase(4);
}

bool WordDatabase::isValidWord(const std::string & word) const
{
	return std::find(_words.begin(), _words.end(), word) != _words.end();
}

std::string WordDatabase::getRandomWord() const
{
	return _words.at(_randomEngine() % _words.size());
}

void WordDatabase::loadDatabase(int wordCount)
{
    std::ifstream file("FILEWORDS/words" + std::to_string(wordCount) + ".txt");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to load words for " << wordCount << "..." << std::endl;
        return;
    }

    _words.clear();
    std::string word;
    while (std::getline(file, word)) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        _words.emplace_back(word);
    }

    if (_words.empty()) {
        std::cerr << "Error: Word list loaded empty..." << std::endl;
        return;
    }

    std::sort(_words.begin(), _words.end());
}

