// WordBag is a wrapper class for WordBagImpl

#ifndef WORDBAG_H
#define WORDBAG_H

#include "WordBagImpl.h"
#include <string>

class WordBag
{
public:
	WordBag(const std::string &url, const std::string &stringOfWords)
	{
		m_impl = new WordBagImpl(url, stringOfWords);
	}

	~WordBag()
	{
		delete m_impl;
	}

	bool getFirstWord(std::string &word, int &count)
	{
		return m_impl->getFirstWord(word, count);
	}

	bool getNextWord(std::string &word, int &count)
	{
		return m_impl->getNextWord(word, count);
	}

	std::string getMyURL() const
	{
		return m_impl->getMyURL();
	}

private:
	WordBag(const WordBag &);		// prevent copying
	WordBag &operator=(const WordBag &);	// prevent copying

	WordBagImpl *m_impl;
};


#endif // WORDBAG_H
