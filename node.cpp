#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
#include<vector>
#include "node.h"

using namespace std;

Node ::	Node() { 
	this->val = ' ';
	for(int i = 0; i < BRANCH; i++) {
		this->links[i] = NULL;
	}
	parent = NULL;
	fail = NULL;
}

Node :: Node(char value) {
	this->val = value;
	for(int i = 0; i < BRANCH; i++) {
		this->links[i] = NULL;
	}
	parent = NULL;
	fail = NULL;
};

// Constructor for the node, Node containes single digit ascii charaters 
Node :: Node(char value, string word) {
	this->val = value;
	this->word = word;
	for(int i = 0; i < BRANCH; i++) {
		this->links[i] = NULL;
	}
	parent = NULL;
	fail = NULL;
};

//Destructor for the nodes.
Node :: ~Node() {
	for(int i = 0; i < BRANCH; i++) {
		if(this->links[i]) {
			delete this->links[i];
		}
		else{
			break;
		}
	}
}