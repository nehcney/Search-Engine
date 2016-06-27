#include "WebCrawlerImpl.h"
#include "WordBag.h"
#include "HTTP.h"
using namespace std;

void WebCrawlerImpl::submitURL(const string &url)
{
	m_urls.push_back(url);
}

int WebCrawlerImpl::getURLCount() const
{
	return m_urls.size();
}

bool WebCrawlerImpl::load(const string &filename)
{
	return m_indexer.load(filename);
}

bool WebCrawlerImpl::save(const string &filename)
{
	return m_indexer.save(filename);
}

void WebCrawlerImpl::crawl(void(*callback)(const string &url, bool success))
{
	for (auto url : m_urls)
	{
		bool success = false;
		string page;
		if (HTTP().get(url, page))
		{
			WordBag wb(url, page);
			m_indexer.submit(wb);
			success = true;
		}
		callback(url, success);
	}
}
