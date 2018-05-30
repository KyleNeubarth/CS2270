#ifndef BHEAP_HPP
#define BHEAD_HPP

#include <iostream>
#include <vector>

using namespace std;

struct BHNode {
	string name;
	int priority;
	int treatment;
	BHNode(string n, int p, int t) {
		name = n;
		priority = p;
		treatment = t;
	}
};

class BHeap {
	public:
		BHeap();
		~BHeap();
		void push(string,int,int);
		BHNode* pop();
		BHNode* find();
		BHNode* arr[999]; 
		//num elements in arr
		int num = 0;
};

#endif