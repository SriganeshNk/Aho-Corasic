#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
#include<vector>

#define BRANCH 500
using namespace std;

class Node {
public:
	Node();
	Node(char value);
	Node(char value, string word);
	~Node();
	char val;
	string word;
	Node* links[BRANCH];
	Node* parent;
	Node* fail;
};
