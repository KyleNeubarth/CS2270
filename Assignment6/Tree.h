#ifndef TREE_H
#define TREE_H

#include <iostream>

using namespace std;

struct node {
	int rank;
	string title;
	int year;
	int quantity;

	node* left;
	node* right;

	node(int _r,string _t,int _y,int _q) {
		rank = _r;
		title = _t;
		year = _y;
		quantity = _q;
	}
};

class Tree {
private:
	node* root;
	void DestroyNode(node*);
public:
	Tree();
	Tree(int,string,int,int);
	~Tree();
	void InsertMovie(int,string,int,int);
	void FindMovie(string name);
};
#endif