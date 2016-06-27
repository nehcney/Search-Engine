// The WebCrawlerImpl class is used to download webpages from the internet
// and add their content to an index (through the Indexer class). New URLs
// are submitted through the submitURL method, stored in a vector (m_urls),
// and then when the crawl method is called the URL contents are downloaded
// and indexed into the Indexer object (m_indexer), which can then be saved
// to disk and later loaded.

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
	WebCrawlerImpl& operator=(const WebCrawlerImpl& other);		// prevent copying
};

#endif // WEBCRAWLERIMPL_H
