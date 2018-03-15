#include <iostream>
#include "doublyLL.h"
using namespace std;

doublyLL::doublyLL() {

}

doublyLL::doublyLL(int nodeID) {
	//create head node
	head = createNode(nodeID, nullptr, nullptr);
	tail = head;
}

doublyLL::~doublyLL() {

}


Node* doublyLL::createNode(int nodeID, Node* nodePrev, Node* nodeNext) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nodeNext;
	newNode->prev = nodePrev;

	return newNode;
}

bool doublyLL::deleteValue(int value) {
	Node* index;
	index = head;
	while (index) {
		//cout << ";"<< index->id << ";" << value <<";||";
		if (index->id == value) {
			//cout << index->id;
			if (index->prev) {
				if (index->next) {
					index->prev->next = index->next;
				} else {
					index->prev->next = nullptr;
					tail = index->prev;
				}
			}
			if (index->next) {
				if (index->prev) {
					index->next->prev = index->prev;
				} else {
					index->next->prev = nullptr;
					head =index->next;
				}
			}
			delete index;

			index = head;
			continue;
		}
		index = index->next;
	}
	return true;
}

void doublyLL::print() {
	Node* index = head;
	while (index) {
		cout << index->id << ";";
		index = index->next;
	}
	cout << "\n";
}

bool doublyLL::insertNodeAtEnd(int nodeID) {
	if (head == nullptr) {
		//nothing in the list
		head = createNode(nodeID, nullptr, nullptr);
		tail = head;
	}
	else {
		Node* newNode = createNode(nodeID, tail, nullptr);
		tail->next = newNode;
		tail = newNode;
	}
	return true;
}









