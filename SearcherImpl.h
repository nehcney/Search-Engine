#ifndef SEARCHERIMPL_H
#define SEARCHERIMPL_H

#include "Indexer.h"
#include <string>
#include <vector>

class SearcherImpl
{
public:
	SearcherImpl();
	~SearcherImpl();
	bool load(const std::string &filename);
	std::vector<std::string> search(const std::string &terms);

private:
	Indexer m_indexer;

private:
	static bool sortByCount(MATCH &a, MATCH &b);
};

#endif // SEARCHERIMPL_H