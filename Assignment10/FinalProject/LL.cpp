#include "LL.hpp"

using namespace std;

LL::LL() {}

LL::~LL() {
	LLNode* current = root;
	LLNode* prev = nullptr;
	while(current) {
		prev = current;
		current = current->next;

		LLNode* temp = prev;
		//is this right?
		delete temp;
	}
}

void LL::push(string s, int p, int t) {
	LLNode* node = new LLNode(s,p,t);
	LLNode* prev = nullptr;
	LLNode* current = root;
	
	bool running = true;
	while (running) {
		//you've reached the end
		if (!current) {
			if (prev) {
				prev->next = node;
			} else {
				root = node;
			}
			return;
		}

		if (node->priority < current->priority) {
			prev = current;
			current = current->next;
		} else if(node->priority > current->priority) {
			if (prev) {
				prev->next = node;
			} else {
				root = node;
			}
			node->next = current;
			return;
		} else {
			if (node->treatment > current->treatment) {
				prev = current;
				current = current->next;
			} else {
				if (prev) {
					prev->next = node;
				} else {
				root = node;
				}

				node->next = current;
				return;
			}
		}
	}
}

LLNode* LL::pop() {
	LLNode* r = root;
	root = root->next;
	return r;
}

LLNode* LL::find() {
	return root;
}