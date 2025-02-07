#include "WordDatabase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

WordDatabase::WordDatabase(std::default_random_engine & randomEngine)
    : _randomEngine(randomEngine)
{
    _currentWordLength = random_number();
    std::cerr << "New WordDatabase created with default word length: " << _currentWordLength << std::endl;
    loadDatabase(_currentWordLength);
}

bool WordDatabase::isValidWord(const std::string & word) const
{
    return std::find(_words.begin(), _words.end(), word) != _words.end();
}

int WordDatabase::getCurrentWordLength() const
{
    return _currentWordLength;
}

std::string WordDatabase::getRandomWord() const
{
    if (_words.empty()) {
        std::cerr << "Error: No words available for length " << _currentWordLength << std::endl;
        return "";
    }
    std::cerr << "Current word length: " << _currentWordLength << std::endl;
    return _words.at(_randomEngine() % _words.size());
}

void WordDatabase::loadDatabase(size_t wordCount)
{
    _currentWordLength = wordCount;
    _words.clear();

    std::ifstream file("FILEWORDS/merged.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open merged.txt" << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        // Convert to uppercase
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        // Only store words of the correct length
        if (word.length() == _currentWordLength) {
            _words.emplace_back(word);
        }
    }

    std::cerr << "Loaded " << _words.size() << " words for " << wordCount << "-letter words" << std::endl;

    if (_words.empty()) {
        std::cerr << "Error: No words found for length " << wordCount << std::endl;
        return;
    }

    std::sort(_words.begin(), _words.end());
}

int WordDatabase::random_number()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3, 12);
    return dist(gen);
}
