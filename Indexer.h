// Wrapper class for IndexerImpl

#ifndef INDEXER_H
#define INDEXER_H

#include "IndexerImpl.h"
#include <string>

class Indexer
{
public:
	Indexer()
	{
		m_impl = new IndexerImpl;
	}

	~Indexer()
	{
		delete m_impl;
	}

	void submit(WordBag &wb)
	{
		m_impl->submit(wb);
	}

	bool save(const std::string &filename)
	{
		return m_impl->save(filename);
	}

	bool load(const std::string &filename)
	{
		return m_impl->load(filename);
	}

	std::vector<MATCH> getMatches(const std::string &term)
	{
		return m_impl->getMatches(term);
	}

private:
	Indexer(const Indexer &);				// prevent copying
	Indexer &operator=(const Indexer &);	// prevent copying

	IndexerImpl		*m_impl;
};

#endif // INDEXER_H
