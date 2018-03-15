#include <iostream>
#include <fstream>
#include "BST.cpp"

int main() {

	BST* bst = new BST(50);

	bool playing = true;

	string input;
	while(playing) {
		cout << "type a number to insert, \"print\" to print to print the tree, \"search\" to find a value, and \"quit\" to exit\n";
		getline(cin,input);
		if (input == "quit") {
			cout << "bye";
			playing = false;
			continue;
		} else if (input == "print") {
			bst->printTree();
		} else if (input == "search") {
			cout << "Enter a search value\n";
			getline(cin,input);
			int value = stoi(input);
			bool found = bst->searchKey(value);
			if (found) {
				cout << "found value\n";
			} else {
				cout << "could not find\n";
			}
		} else {
			int insert = stoi(input);
			bst->insertNode(insert);
		}
	}
	bst->~BST();
}