#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "trie.h"
#include "string.h"

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> pattern;
	string data;
	string words;
	string filename;
	bool fileinput = true;
	int pattern_index = 0;
	if (argc < 2 || argc == 3) {
		cout << "Wrong Usage... \n";
		cout << "Read the README.md file \n";
		return 0;
	}
	if (argc > 2) {
		char* ch = argv[2];
		while(*ch != '\0') {
			if(*ch == '|') {
				fileinput = false;
				pattern_index = 2;
				break;
			}
			ch++;
		}	
		if (fileinput) {
			ifstream patternfile (argv[2], ios::binary);
			if (patternfile.is_open())
   	 		{
	   	 	    while (!patternfile.eof() )
       		 	{
    			    getline (patternfile, data);
   			        /*find the matching of those patterns in the file*/
   		    	    pattern.push_back(data);
	    	    }
	    	    patternfile.close();
				data.clear();
   		 	}
		}
	}
	else {
		fileinput = false;
		pattern_index = 1;
	}
	if(!fileinput) {
		char *ch = argv[pattern_index];
		while (*ch != '\0') {
			if(*ch == '|') {
				pattern.push_back(words);
				words.clear();
				ch++;
			}
			else {
				words += *ch;
				ch++;
			}
		}
		pattern.push_back(words);
	}
	/*construct Trie*/
	Trie t(pattern);
	
	/*display the contents one by one in a trie*/
	//t.display_all();
	
	/* open a file in read mode. */
	if (argc > 2) {
		ifstream myfile (argv[3], ios::binary);
		if (myfile.is_open())
		{
			while (!myfile.eof() )
			{
				getline (myfile, data);
				/*find the matching of those patterns in the file*/
				t.find(data);
			}
			myfile.close();
		}
	}
	else {
		cout << "\n Enter the string\n";
		while(cin) {
			getline(cin, data);
			t.find(data);
		}
	}
	return 0;	
}	
