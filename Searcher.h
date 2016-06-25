#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <vector>

#include "searcherimpl.h"

class Searcher
{
public:
	Searcher()
	{
		m_impl = new SearcherImpl;
	}

	~Searcher()
	{
		delete m_impl;
	}

	bool load(const std::string &filename)
	{
		return m_impl->load(filename);
	}

	std::vector<std::string> search(const std::string &terms)
	{
		return m_impl->search(terms);
	}

private:

	Searcher(const Searcher &);
	Searcher &operator=(const Searcher &);

	SearcherImpl		*m_impl;
};

#endif // SEARCHER_H