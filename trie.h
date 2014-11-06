#include<iostream>
#include<string>
#include<vector>
#include "node.h"

using namespace std;

// Multi- Pattern match trie
/* Trie constructed based on AHO-CORASIC algorithm.
** The failure links are constructed based on this algorithm.
*/

class Trie {
public:
	Trie ();
	Trie (vector<string> patterns);
	void display_all ();
	bool find (string word);
	~Trie(){delete root;}
private:
	Node *root;
	bool insert (string value);
	bool failure (Node* tr);
	void traverse_and_print (string prefix, Node* tr);
};
