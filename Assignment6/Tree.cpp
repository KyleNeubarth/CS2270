#include <iostream>
#include "Tree.h"
using namespace std;

Tree::Tree() {

}
Tree::Tree(float _f,string _s,int _y,int _q) {
	root = new node(_f,_s,_y,_q);
}
Tree::~Tree() {
	DestroyNode(root);
}
void Tree::DestroyNode(node* n) {
	if(n) {
         DestroyNode(n->left);
         DestroyNode(n->right);
         delete n;
         n = nullptr;
    }
}

void Tree::InsertMovie(float rating,string title,int year,int quantity) {
	return;
}