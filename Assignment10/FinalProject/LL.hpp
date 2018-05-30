#ifndef LL_HPP
#define LL_HPP
#include <iostream>

using namespace std;

struct LLNode {
	string name;
	int priority;
	int treatment;

	LLNode* next;
	LLNode(string n,int p,int t) {
		name = n;
		priority = p;
		treatment = t;
		next = nullptr;
	}
};

class LL {
	public:
		LL();
		~LL();
		void push(string,int,int);
		LLNode* pop();
		LLNode* find();

		LLNode* root = nullptr;
};
#endif