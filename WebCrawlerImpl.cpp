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



///////////// TEST
/*
void status(const string &url, bool success)
{
	if (success)
		cout << "Successfully downloaded and indexed the page from: " << url << endl;
	else
		cout << "Unable to download the page from: " << url << endl;
}

int main()
{
	string s = "- This, is!@ a test\n"
		"this, is...another! line?\n"
		"test\n";

	//////////////////////////////

	HTTP().set("a.com", s);
	HTTP().set("b.com", "<html>Nothing here</html>");
	HTTP().set("c.com", "<>test,here?</>");

	WebCrawlerImpl wci;
	wci.load("wci_test");
	wci.submitURL("b.com");
	wci.submitURL("a.com");
	wci.submitURL("c.com");
	wci.submitURL("a92734ajfdsazzzz.com");

	wci.crawl(status);

	wci.save("wci_test");
}
*/