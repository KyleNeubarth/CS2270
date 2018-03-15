#ifndef doublyLL_H
#define doublyLL_H

using namespace std;

struct Node {
	int id=-1;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class doublyLL {
	private:
		Node* createNode(int,Node*,Node*);
	public:
		bool deleteValue(int value);
		bool insertNodeAtEnd(int);
		void print();
		Node* head = nullptr;
		Node* tail = nullptr;
		doublyLL();	//default constructor
		doublyLL(int);	//overloaded constructor
		~doublyLL();	//destructor
};

#endif