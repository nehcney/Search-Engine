#include "SearcherImpl.h"
#include "MyMap.h"
#include "Utility.h"
using namespace std;

SearcherImpl::SearcherImpl()
{

}

SearcherImpl::~SearcherImpl()
{

}

bool SearcherImpl::load(const string &filename)
{
	return m_indexer.load(filename);
}

vector<string> SearcherImpl::search(const string &terms)
	// Assumptions:
	//	- No duplicate words
	//	- Can be upper/lower case
{
	MyMap<string, int> numUniqueTerms, totalNumTerms;
	vector<string> terms_split = split(terms);
	for (auto term : terms_split) // for each search term...
	{
		lower(term); // convert to lowercase
		vector<MATCH> temp_vector = m_indexer.getMatches(term); // find all matches for term
		for (auto k : temp_vector) // for each match...
		{
			// Enter # of matching URLs to numUniqueTerms, and
			// total # of terms found per URL to totalNumTerms
			int* count = numUniqueTerms.find(k.url);
			if (count == nullptr)
			{
				numUniqueTerms.associate(k.url, 1);
				totalNumTerms.associate(k.url, k.count);
			}
			else
			{
				numUniqueTerms.associate(k.url, 1 + *count);
				int* count2 = totalNumTerms.find(k.url);
				totalNumTerms.associate(k.url, k.count + *count2);
			}
		}
	}

	// T determines whether a URL is a match
	int T = terms_split.size() * .7;
	if (T < 1)
		T = 1;

	// Find all matching URLs and enter them into a vector<MATCH>
	vector<MATCH> match_results;
	string url;
	int *count = numUniqueTerms.getFirst(url);
	while (count != nullptr)
	{
		if (*count >= T)
		{
			MATCH temp_match;
			temp_match.url = url;
			temp_match.count = *totalNumTerms.find(url);
			match_results.push_back(temp_match);
		}
		count = numUniqueTerms.getNext(url);
	}

	// Sort the matches based on total # of terms found
	sort(match_results.begin(), match_results.end(), sortByCount);

	// Enter the sorted matches into a vector of strings, then return
	vector<string> results;
	for (auto i : match_results)
		results.push_back(i.url);
	return results;
}


//////////////////////////////////////////////////////
// Helper Functions
//////////////////////////////////////////////////////

bool SearcherImpl::sortByCount(MATCH &a, MATCH &b)
{
	return a.count > b.count; // descending order
}