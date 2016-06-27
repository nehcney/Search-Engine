// The SearcherImpl class is used to search through an index (created by the
// WebCrawlerImpl class and stored in an IndexerImpl object) for webpages that
// match a set of search terms. The results are stored in a vector of URLs.
// Search terms assumptions:
//    - No punctuation
//    - No duplicate words
//    - Can be upper or lowercase

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
