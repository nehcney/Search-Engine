/*
// TEST MAIN
#include "WordBag.h"
#include "IndexerImpl.h"
#include "WebCrawlerImpl.h"
#include "HTTP.h"
#include "SearcherImpl.h"
#include <iostream>
using namespace std;

void status(const string &url, bool success)
{
	if (success)
		cout << "Successfully downloaded and indexed the page from: " << url << endl;
	else
		cout << "Unable to download the page from: " << url << endl;
}

int main()
{
	HTTP().set("a.com", "a, f??a#");
	HTTP().set("b.com", "<html>b,b,a</html>");
	HTTP().set("c.com", "<>c!!!!!b</>");

	WebCrawlerImpl wci;
	wci.load("test");
	wci.submitURL("b.com");
	wci.submitURL("a.com");
	wci.submitURL("c.com");
	wci.submitURL("a92734ajfdsazzzz.com");
	wci.crawl(status);
	wci.save("test");

	///////////////////////////////

	SearcherImpl si;
	if (!si.load("test"))
		return 1;

	string query;
	do
	{
		getline(cin, query);
		vector<string> matches = si.search(query);
		if (matches.size() > 0)
		{
			cout << "Your search found " << matches.size() << " matching web pages!\n";
			for (auto i : matches)
				cout << i << endl;
		}
		else
			cout << "No pages matched your search terms.\n";
	} while (query.empty() == false);

	return 0;
}
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include "WebCrawler.h"
#include "Searcher.h"

using namespace std;

void printUsage(char *argv[])
{
	cout << "usage:\n";
	cout << "\t" << argv[0] << " -c index.dat urllist.dat\n";
	cout << "\t" << argv[0] << " -s index.dat\n";
}

void crawlCallback(const std::string &url, bool success)
{
	if (success)
		cout << "Successfully processed " << url << endl;
	else
		cout << "Error processing " << url << endl;
}

int crawl(int argc, char *argv[])
{
	WebCrawlerImpl		wc;

	if (wc.load(argv[2]) == false)
		cout << "Unable to load index file - file does not exist or is corrupt.\n";
	else
		cout << "Successfully loaded index file.\n";

	ifstream stream(argv[3]);
	if (!stream)
	{
		cout << "Error: unable to load list of URLs to crawl. Aborting.\n";
		return -1;
	}

	while (!stream.eof())
	{
		std::string url;
		getline(stream, url);
		if (url.length() > 0)
			wc.submitURL(url);
	}

	stream.close();

	cout << "Crawling and indexing " << wc.getURLCount() << " URLs...\n";

	wc.crawl(crawlCallback);		// crawl the pages

									// now save our index
	if (wc.save(argv[2]) == false)
		return -1;

	return 0;
}

int search(int argc, char *argv[])
{
	Searcher searcher;

	if (searcher.load(argv[2]) == false)
	{
		cout << "Unable to load index file - file does not exist or is corrupt.\n";
		return -1;
	}

	cout << "Successfully loaded index file.\n";
	std::string query;

	for (;;)
	{
		cout << "Enter your search terms: ";
		getline(cin, query);
		if (query.empty())
			break;

		auto results = searcher.search(query);
		if (results.size() == 0)
			cout << "No results found\n";
		else
		{
			cout << "\n" << results.size() << " matches found:\n";
			for (size_t i = 0; i<results.size(); i++)
				cout << results[i] << endl;
		}
		cout << endl;
	}

	return 0;
}

#include "HTTP.h"

int main(int argc, char *argv[])
{
	//HTTP().set("http://a.com", "aaaa bbbb cccc dddd dddd");
	//HTTP().set("http://b.com", "bbbb cccc cccc dddd eeee");
	//HTTP().set("http://c.com", "dddd eeee ffff ffff gggg");

	cout << "Oogle - the amazing search engine\n\n";
	if (argc < 2)
	{
		printUsage(argv);
		return -1;
	}

	if (strcmp(argv[1], "-c") == 0 && argc == 4)
		return crawl(argc, argv);
	else if (strcmp(argv[1], "-s") == 0 && argc == 3)
		return search(argc, argv);
	else
	{
		printUsage(argv);
		return -1;
	}
	
	return 0;
}
