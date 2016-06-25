#include "IndexerImpl.h"
#include "Utility.h"
using namespace std;

void IndexerImpl::submit(WordBag &wb)
{
	// If a URL has already been submitted before, skip it.
	int* found = urlToNumber.find(wb.getMyURL());
	if (found != nullptr)
		return;
	
	// Add URL to the urlToNumber and numberToUrl maps
	int urlNum = hashString(wb.getMyURL());
	urlToNumber.associate(wb.getMyURL(), urlNum);
	numberToUrl.associate(urlNum, wb.getMyURL());

	// Add matches to the wordToMatches map
	pair<int,int> temp;
	temp.first = urlNum;
	string word;
	bool gotWord = wb.getFirstWord(word, temp.second);
	while (gotWord)
	{
		vector<pair<int,int> > *temp_vector = wordToMatches.find(word);
		if (temp_vector != nullptr) // word already exists
			temp_vector->push_back(temp);
		else // word is new, associate a new vector<pair>
			wordToMatches.associate(word, vector<pair<int,int> >(1, temp));
		gotWord = wb.getNextWord(word, temp.second);
	}
}

bool IndexerImpl::save(const string &filename)
{
	if (!urlToNumber.save(filename + ".u2n"))
		return false; 
	if (!numberToUrl.save(filename + ".n2u"))
		return false;
	if (!wordToMatches.save(filename + ".w2m"))
		return false;

	return true;
}

bool IndexerImpl::load(const string &filename)
{
	if (!urlToNumber.load(filename + ".u2n"))
		return false;
	if (!numberToUrl.load (filename + ".n2u"))
		return false;
	if (!wordToMatches.load(filename + ".w2m"))
		return false;

	return true;
}

vector<MATCH> IndexerImpl::getMatches(const string &term)
{
	vector<pair<int,int> > *temp = wordToMatches.find(term);
	if (temp != nullptr)
	{
		vector<MATCH> result;
		for (auto i : *temp)
		{
			string *s = numberToUrl.find(i.first);
			MATCH m;
			m.url = *s;
			m.count = i.second;
			result.push_back(m);
		}
		return result;
	}
	else
		return vector<MATCH>();
}


//////////// TEST
/*
void print(vector<MATCH> &v)
{
	for (auto i : v)
		cout << i.url << " : " << i.count << endl;
}

int main()
{
	string s = "- This, is!@ a test\n"
		"this, is...another! line?\n"
		"test\n"; 
	WordBag wb1("a.com", s);
	WordBag wb2("b.com", "<html>Nothing here</html>");
	WordBag wb3("c.com", "test,here?");

	IndexerImpl ii;
	ii.load("test");

	ii.submit(wb2);
	ii.submit(wb1);
	ii.submit(wb3);

	ii.save("test");

	vector<MATCH> answer;
	answer = ii.getMatches("this");
	print(answer);
	answer = ii.getMatches("here");
	print(answer);
	answer = ii.getMatches("asdf");
	print(answer);
}
*/
