#ifndef WORDBAGIMPL_H
#define WORDBAGIMPL_H

#include "MyMap.h"
#include <string>

class WordBagImpl
{
public:
	WordBagImpl(const std::string& url, const std::string& stringOfWords);
	~WordBagImpl() {}
	bool getFirstWord(std::string &word, int &count);
	bool getNextWord(std::string &word, int &count);
	std::string getMyURL() const;

private:
	std::string m_url;
	MyMap<std::string, int> m_map;

private:
	WordBagImpl(const WordBagImpl& other);				// prevent copying
	WordBagImpl& operator=(const WordBagImpl& other);	// prevent copying
	void insertOrUpdateMap(std::string& word);
	void insertWordsIntoMap(const std::string& stringOfWords);
};

#endif // WORDBAGIMPL_H