#ifndef WEBCRAWLERIMPL_H
#define WEBCRAWLERIMPL_H

#include "Indexer.h"
#include <string>
#include <vector>

class WebCrawlerImpl
{
public:
	WebCrawlerImpl() {}
	~WebCrawlerImpl() {}
	void submitURL(const std::string &url);
	int getURLCount() const;
	bool load(const std::string &filename);
	bool save(const std::string &filename);
	void crawl(void(*callback)(const std::string &url, bool success));

private:
	Indexer m_indexer;
	std::vector<std::string> m_urls;

private:
	WebCrawlerImpl(const WebCrawlerImpl& other);			// prevent copying
	WebCrawlerImpl& operator=(const WebCrawlerImpl& other);	// prevent copying
};

#endif // WEBCRAWLERIMPL_H
