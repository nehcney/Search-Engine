// IndexerImpl 

#ifndef INDEXERIMPL_H
#define INDEXERIMPL_H

#include "WordBag.h"
#include "MyMap.h"
#include <string>
#include <vector>

struct MATCH
{
	std::string url;
	int count;
};

class IndexerImpl
{
public:
	IndexerImpl() {}
	~IndexerImpl() {}
	void submit(WordBag &wb);
	bool save(const std::string &filename);
	bool load(const std::string &filename);
	std::vector<MATCH> getMatches(const std::string &term);

private:
	MyMap<std::string, int> urlToNumber;
	MyMap<int, std::string> numberToUrl;
	MyMap<std::string, std::vector<std::pair<int,int> > > wordToMatches;

private:
	IndexerImpl(const IndexerImpl& other);			// prevent copying
	IndexerImpl& operator=(const IndexerImpl& other);	// prevent copying
};


//////////////////////////////////////////////////////
// Non-member Functions
//////////////////////////////////////////////////////

inline bool saveToFile(std::ofstream &stream, std::vector<std::pair<int,int> > &v)
{
	stream << v.size() << std::endl;
	for (auto i : v)
		stream << i.first << ',' << i.second << std::endl;
	return true;
}

inline bool loadFromFile(std::ifstream &stream, std::vector<std::pair<int,int> > &v)
{
	v.clear();

	std::string s;
	if (!std::getline(stream, s))
		return false;
	int size = atoi(s.c_str());

	for (int i = 0; i < size; ++i)
	{
		std::pair<int,int> temp;
		std::getline(stream, s);
		int pos = s.find_first_of(',');
		temp.first = atoi((s.substr(0, pos)).c_str());
		temp.second = atoi((s.substr(pos + 1)).c_str());
		v.push_back(temp);
	}

	return true;
}

#endif // INDEXERIMPL_H
