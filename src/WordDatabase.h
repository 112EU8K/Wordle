#ifndef WORDDATABASE_H
#define WORDDATABASE_H

#include <vector>
#include <random>

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
	void loadDatabase(int wordCount);

private:
	// The database
	std::vector<std::string> _words;

	// Shared randomEngine used for all the randomisation.
	std::default_random_engine& _randomEngine;


};
#endif // WORDDATABASE_H
