// MyMap is a templated BST map class.

#ifndef MYMAP_H
#define MYMAP_H

#include <queue>
#include <string>
#include <fstream>

template <class mapFrom, class mapTo>
class MyMap
{
public:
	MyMap();
	~MyMap();
	void reset();
	void associate(const mapFrom &from, const mapTo &toItem);
	mapTo *find(const mapFrom &from);
	// The spec specifies LEVEL-ORDER retrieval for getFirst & getNext
	mapTo *getFirst(mapFrom &s);
	mapTo *getNext(mapFrom &s);
	int getNumItems() const;
	bool save(const std::string &filename);
	bool load(const std::string &filename);

private:
	struct Node
	{
		Node(mapFrom f, mapTo t)
			: from(f), to(t), left(nullptr), right(nullptr) {}
		mapFrom from;
		mapTo to;
		Node* left;
		Node* right;
	};

	Node* m_head;
	int m_size;
	std::queue<Node*> m_queue;

private:
	MyMap(const MyMap& other);		// prevent copying
	MyMap& operator=(const MyMap& other);	// prevent copying
	void deleteAllNodes(Node* root);
};


//////////////////////////////////////////////////////
// Non-member Functions
//////////////////////////////////////////////////////

inline bool saveToFile(std::ofstream &stream, int i)
{
	stream << i << std::endl;
	return true;
}

inline bool loadFromFile(std::ifstream &stream, int &i)
{
	std::string s;
	if (!std::getline(stream, s))
		return false;
	i = atoi(s.c_str());
	return true;
}

inline bool saveToFile(std::ofstream &stream, const std::string &s)
{
	stream << s << std::endl;
	return true;
}

inline bool loadFromFile(std::ifstream &stream, std::string &s)
{
	s.clear();
	if (!std::getline(stream, s))
		return false;
	return true;
}


//////////////////////////////////////////////////////
// Inline Implementations
//////////////////////////////////////////////////////

template <class mapFrom, class mapTo>
inline MyMap<typename mapFrom, typename mapTo>::MyMap()
{
	m_head = nullptr;
	m_size = 0;
}

template <class mapFrom, class mapTo>
inline MyMap<typename mapFrom, typename mapTo>::~MyMap()
{
	reset();
}

template <class mapFrom, class mapTo>
inline void MyMap<typename mapFrom, typename mapTo>::reset()
{
	deleteAllNodes(m_head);
	m_size = 0;
}

template <class mapFrom, class mapTo>
inline int MyMap<typename mapFrom, typename mapTo>::getNumItems() const
{
	return m_size;
}


//////////////////////////////////////////////////////
// Non-inline Implementations
//////////////////////////////////////////////////////

template <class mapFrom, class mapTo>
void MyMap<typename mapFrom, typename mapTo>::associate(const mapFrom &from, const mapTo &toItem)
{
	if (m_head == nullptr)
	{
		m_head = new Node(from, toItem);
		m_size++;
		return;
	}

	Node* cur = m_head;
	for (;;)
	{
		if (from == cur->from)
		{
			cur->to = toItem;
			return;
		}
		else if (from < cur->from)
		{
			if (cur->left)
				cur = cur->left;
			else
			{
				cur->left = new Node(from, toItem);
				m_size++;
				return;
			}
		}
		else // (from > cur->from)
		{
			if (cur->right)
				cur = cur->right;
			else
			{
				cur->right = new Node(from, toItem);
				m_size++;
				return;
			}
		}
	}
}

template <class mapFrom, class mapTo>
mapTo *MyMap<typename mapFrom, typename mapTo>::find(const mapFrom &from)
{
	if (m_head == nullptr)
		return nullptr;

	Node* cur = m_head;
	while (cur != nullptr)
	{
		if (from == cur->from)
			return &cur->to;
		else if (from < cur->from)
			cur = cur->left;
		else // (from > cur->from)
			cur = cur->right;
	}
	return nullptr;
}

// Because getFirst() and getNext() must retrieve items in a
// LEVEL-ORDER ordering, we need to employ the use of a queue.
template <class mapFrom, class mapTo>
mapTo *MyMap<typename mapFrom, typename mapTo>::getFirst(mapFrom &s)
{
	if (m_head == nullptr)
		return nullptr;
		
	// Empty the queue
	while (!m_queue.empty())
		m_queue.pop();

	// Add the children of the root node to the queue
	if (m_head->left)
		m_queue.push(m_head->left);
	if (m_head->right)
		m_queue.push(m_head->right);
	s = m_head->from;
	return &m_head->to;
}

template <class mapFrom, class mapTo>
mapTo *MyMap<typename mapFrom, typename mapTo>::getNext(mapFrom &s)
{
	if (m_queue.empty())
		return nullptr;

	Node* cur = m_queue.front();
	m_queue.pop();
	if (cur->left)
		m_queue.push(cur->left);
	if (cur->right)
		m_queue.push(cur->right);
	s = cur->from;
	return &cur->to;
}

template <class mapFrom, class mapTo>
bool MyMap<typename mapFrom, typename mapTo>::save(const std::string &filename)
{
	ofstream ofs(filename);
	if (!ofs)
		return false;

	// Save # of nodes to the 1st line of the file
	ofs << m_size << endl;

	// Save the rest of the data
	mapFrom from;
	mapTo* to = getFirst(from);
	for (; to != nullptr; to = getNext(from))
	{
		if (!saveToFile(ofs, from) || !saveToFile(ofs, *to))
		{
			ofs.close();
			return false;
		}
	}
	ofs.close();
	return true;
}

template <class mapFrom, class mapTo>
bool MyMap<typename mapFrom, typename mapTo>::load(const std::string &filename)
{
	reset();

	ifstream ifs(filename);
	if (!ifs)
		return false;

	// Load # of nodes
	int numNodes;
	if (!loadFromFile(ifs, numNodes))
		return false;

	// Load the rest of the data
	mapFrom from;
	mapTo to;
	for (int i = 0; i < numNodes; ++i)
	{
		if (!loadFromFile(ifs, from) || !loadFromFile(ifs, to))
		{
			ifs.close();
			return false;
		}
		associate(from, to);
	}
	ifs.close();
	return true;
}


//////////////////////////////////////////////////////
// Helper Functions
//////////////////////////////////////////////////////

template <class mapFrom, class mapTo>
void MyMap<typename mapFrom, typename mapTo>::deleteAllNodes(Node* root)
{
	if (root == nullptr)
		return;
	deleteAllNodes(root->left);
	deleteAllNodes(root->right);
	delete root;
}


//////// TEST
/*
int main()
{
MyMap<int, int> test;
test.load("test.txt");

int a, *b;
b = test.getFirst(a);
test.associate(3, 30);
test.associate(1, 10);
test.associate(4, 40);
test.associate(2, 20);
b = test.getFirst(a);
b = test.getNext(a);
b = test.getNext(a);
b = test.getNext(a);
b = test.getNext(a);
b = test.find(4);
test.save("test.txt");

MyMap<string, int> test2;
test2.associate("abc", 1);
}
*/

#endif // MYMAP_H
