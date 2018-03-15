#include <iostream>
#include <fstream>

using namespace std;

struct node {
	string name;
	node* next;
	node(string _msg,node* _next) {
		name = _msg;
		next = _next;
	}
};

//declare dem variables
node* head;

void insert(string myName,string prevName) {
	//did I find an element?
	bool found = false;
	node* index = head;
	//look for a element with given name, idk why I'm using a string instead of a pointer
	//user friendliness I guess
	while (index) {
		if (index->name == prevName) {
			found = true;
			break;
	}
    	index = index->next;
	}
	if (found) {
		node* newNode = new node(myName,index->next);
		index->next = newNode;
	} else {
		node* newNode = new node(myName,head);
		head = newNode;
	}
}

void print() {
	node* index = head;
	while (index) {
		cout << index->name << ";";
		index = index->next;
	}
	cout << "\n";
}

int main(int argc, char *argv[]) {
	head = new node("first",NULL);
	print();
	insert("second","first");
	insert("FIRST!!!","nothing");
	print();
}