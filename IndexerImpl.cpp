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
	MATCH temp_match;
	temp_match.url = wb.getMyURL();
	string word;
	bool gotWord = wb.getFirstWord(word, temp_match.count);
	while (gotWord)
	{
		vector<MATCH> *temp_vector = wordToMatches.find(word);
		if (temp_vector != nullptr) // word already exists
			temp_vector->push_back(temp_match);
		else // word is new, associate a new vector<MATCH>
			wordToMatches.associate(word, vector<MATCH>(1, temp_match));
		gotWord = wb.getNextWord(word, temp_match.count);
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
	vector<MATCH> *temp = wordToMatches.find(term);
	if (temp != nullptr)
		return *temp;
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