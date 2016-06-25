#ifndef WEBCRAWLER_H
#define WEBCRAWLER_H

#include <string>
#include <vector>

#include "webcrawlerimpl.h"

class WebCrawler
{
public:
	WebCrawler()
	{
		m_impl = new WebCrawlerImpl;
	}

	~WebCrawler()
	{
		delete m_impl;
	}

	void submitURL(const std::string &url)
	{
		m_impl->submitURL(url);
	}

	int getURLCount() const
	{
		return m_impl->getURLCount();
	}

	bool load(const std::string &filename)
	{
		return m_impl->load(filename);
	}

	bool save(const std::string &filename)
	{
		return m_impl->save(filename);
	}

	void crawl(void(*callback)(const std::string &url, bool success))
	{
		return m_impl->crawl(callback);
	}

private:

	WebCrawler(const WebCrawler &);
	WebCrawler &operator=(const WebCrawler &);

	WebCrawlerImpl	*m_impl;
};

#endif // WEBCRAWLER_H