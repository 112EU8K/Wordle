#ifndef WORDDATABASE_H
#define WORDDATABASE_H

#include <vector>
#include <random>


/*
WordDatabase class:
Manages a collection of words.
*/
class WordDatabase
{
public:
	// Initialises the word database with the associated file
	WordDatabase(std::default_random_engine& randomEngine);
	virtual ~WordDatabase() = default;

	// Returns true if the word specified is a word in the database
	bool isValidWord(const std::string& word) const;

	// Returns a random word from the database.
	std::string getRandomWord() const;

	// Loads the word list in and sorts in alphabetically
	void loadDatabase(size_t wordCount);

	int getCurrentWordLength() const;

private:
	// The database
	std::vector<std::string> _words;

	// So be it!
	int random_number();

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine& _randomEngine;

	// I think not!
	int _currentWordLength;

};


#endif // WORDDATABASE_H
