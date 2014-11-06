#include<iostream>
#include<string>
#include<vector>
#include "trie.h"

using namespace std;

//Dummy Constructor

Trie :: Trie() {
	root = NULL;
}

// TRIE constructor.
/* Inserts the pattern one by one into the TRIE.
** Constructs the failure links in a DEPTH FIRST MANNER. (Recursive).
** The final trie object has the all the patterns and their corresponding failure links
*/

Trie ::	Trie(vector<string> patterns) {
	root = NULL;
	for (size_t i = 0 ; i < patterns.size(); i++) {
		insert(patterns[i]);
	}	
	/*provide failure links as per the AC algorithm*/
	root->fail = root;
	for (int i = 0; i < BRANCH; i++) {
		if(!root->links[i])
			break;
		else
			failure(root->links[i]);
	}
}

// Insert a string into the TRIE
/* The string is parsed one character at a time.
** If the characters are already in the TRIE in a particular order from the root
** Insert the remaining characters to form another path.
** Insert '$' at the end to signal the end of the word.
*/

bool Trie :: insert(string s) {
	Node *tr = NULL;
	if(!root) {
		Node* new_node = new Node();
		root = new_node;
		new_node->parent = root;
	}
	tr = root;
	int  p = 0;
	for (int i = 0; i < BRANCH; i++) {
		if(!tr->links[i]) {
			break;
		}
		if(tr->links[i]->val == s[0]) {
			tr = tr->links[i];
			p = 1;
			break;
		}
	}
	for (; p < s.size()+1; p++) {
		for(int j = 0; j < BRANCH; j++) {	
			if(p == s.size() && !tr->links[j]) {
				Node* new_node = new Node('$', s);
				tr->links[j] = new_node;
				new_node->parent = tr;
				break;
			}
			if(!tr->links[j]) {
				char value = (char)s[p];
				Node* new_node = new Node(value);
				tr->links[j] = new_node;
				new_node->parent = tr;
				tr = tr->links[j];
				break;
			}
			if(tr->links[j]->val == (char)s[p]) {
				tr = tr->links[j];
				break;
			}
		}
	}
	if(p <s.size())
		return false;
	return true;
}

// Construct the failure links within the trie
/* For each and every node construct the failure links
** Based on the AHO-CORASIC algorithm
** Follow the failure link of ancestor to find the failure link of the current node.
** O(m+b) running time (m = number of nodes, b = branching factor of the node)
*/

bool Trie :: failure(Node *tr) {
	if(!tr)
		return false;
	if(tr->val == '$') {
		tr->fail = root;
		return true;
	}
	Node* prev = tr->parent;
	bool found = false;
	for(int i = 0; i < BRANCH; i++) {
		Node* temp = prev;
		found = false;
		while(!found && !tr->fail) {
			if(!temp->fail) {
				failure(temp);
			}
			temp = temp->fail;
			for(int j = 0; j < BRANCH; j++) {
				if(!temp->links[j])
					break;
				if(temp->links[j]->val == tr->val && tr!=temp->links[j]) {
					found = true;
					tr->fail = temp->links[j];
					break;
				}
			}
			if(!found) {
				if (temp == root) {
					tr->fail = root;
					break;
				}
			}
		}
		if(!tr->links[i])
			break;
		else
			failure(tr->links[i]);
	}
	return true;
}
// Display_method to get all the contents of the trie (Driver function for traverse and print)

void Trie :: display_all() {
	Node* tr = NULL;
	if(root) {
		tr = root;
	}
	else {
		cout <<"\n Trie doesn't exist";
		return;
	}
	string prefix = "";
	traverse_and_print(prefix, tr);
}

//Traverse through the trie to see all the values that the trie holds
/* Use a string to keep track of the word formed by traversing the TRIE.
** Display the contents of the string once the traversal hits a '$' (end of word).
** Replace the last character, because the displayed word could be a BRANCH of another PATH.
** Repeat it for the other branches if they are present.
*/
void Trie :: traverse_and_print(string prefix, Node* tr) {
	for (int i = 0; i < BRANCH; i++) {
		if (tr->links[i]) {
			if (tr->links[i]->val == '$') {
				cout << "\n" << prefix << "\n";
			}
			prefix += tr->links[i]->val;
			traverse_and_print(prefix, tr->links[i]);
		}
		else {
			break;
		}
		prefix.erase(prefix.end()-1, prefix.end());
	}	 
}

// Find the match in the given string with any of the patterns present in the trie 
/* The displaying of the matched characters is with the help of the string itself.
** The traversal is simple, Go to the next link if there is match else, go to the failure state.
** Display the word if the start and end index match an entire word inside the trie.
*/

bool Trie :: find(string word) {
	Node *tr = root;
	int start = -1, end = -1;
	bool match = false;
	for (int i = 0; i < word.size(); i++) {
		char value = word[i];
		match = false;
		for (int j = 0 ; j < BRANCH; j++) {
			if (!tr->links[j])
				break;
			if (tr->links[j]->val == word[i]) {
				if (start == -1)
					start = i;
				tr = tr->links[j];
				// Find if the node is the leaf node, and 
				// if the match is present 
				// then set the end index value in the word.
				for (int stop = 0; stop < BRANCH; stop++) {
					if (!tr->links[stop])
						break;
					if (tr->links[stop]->val == '$')
					{
						start = i - tr->links[stop]->word.size() + 1;
						end = i+1;
						tr = tr->links[stop];
						break;
					}
				}
				match = true;
				break;
			}
		}
		if (!match) {
			tr = tr->fail;
			if(tr == root) {
				if (start > -1)
					i = start;
				start = -1;
				end = -1;
			}
			else {
				i = i - 1;
				start = start + 1;
			}
		}
		if ((start > -1) && (end > -1)) {
			//cout << word << " : ";
			//cout << word.substr(start, end-start) << "\n";
			cout << word.substr(0, start);
			cout << "\033[1;31m" << word.substr(start, end-start)  << "\033[0m";
			cout << word.substr(end, word.size()-end) << "\n";
			// To get the matched within a perfect match
			tr = tr->fail;
			start = -1;
			end = -1;
		}
	}
	return true;
}
