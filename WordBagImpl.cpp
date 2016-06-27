#include "WordBagImpl.h"
#include "Utility.h"
using namespace std;

WordBagImpl::WordBagImpl(const string& url, const string& stringOfWords)
{
	m_url = url;
	insertWordsIntoMap(stringOfWords);
}

string WordBagImpl::getMyURL() const
{
	return m_url;
}

bool WordBagImpl::getFirstWord(string &word, int &count)
{
	int* to = m_map.getFirst(word);
	if (to != nullptr)
		count = *to;
	return to != nullptr;
}

bool WordBagImpl::getNextWord(string &word, int &count)
{
	int* to = m_map.getNext(word);
	if (to != nullptr)
		count = *to;
	return to != nullptr;
}


//////////////////////////////////////////////////////
// Helper Functions
//////////////////////////////////////////////////////

void WordBagImpl::insertOrUpdateMap(string& word)
{
	lower(word);
	int* count = m_map.find(word);
	if (count == nullptr)
		m_map.associate(word, 1);
	else
		m_map.associate(word, 1 + *count);
}

void WordBagImpl::insertWordsIntoMap(const string& stringOfWords)
{
	vector<string> results = split(stringOfWords);
	for (auto i : results)
		insertOrUpdateMap(i);
}
