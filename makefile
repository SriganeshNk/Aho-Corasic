all: mygrep

mygrep: ahoc.o trie.o node.o
	g++ ahoc.o trie.o node.o -o mygrep

ahoc.o: ahoc.cpp
	g++ -c ahoc.cpp

trie.o: trie.cpp
	g++ -c trie.cpp

node.o: node.cpp
	g++ -c node.cpp

clean:
	rm -rf *o mygrep
