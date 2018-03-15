#include <iostream>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree() {

}
MovieTree::~MovieTree() {

}
void printHelper(MovieNodeBST* bst) {

	if (bst->leftChild) {
		printHelper(bst->leftChild);
	}
	MovieNodeLL* index = bst->head;
	cout << bst->head << "\n";
	//wtf
	while(index) {

		cout << "Movie:" << index->title;

		if (!index->next) {
			break;
		}
		index = index->next;
	}
	if (bst->rightChild) {
		printHelper(bst->rightChild);
	}
}
void MovieTree::printMovieInventory() {
	//cout << "fuck";
	printHelper(root);
}

void addMovieHelper(MovieNodeBST* bst, MovieNodeLL* ll,char c) {
	if (c == bst->letter) {
		MovieNodeLL* prev = nullptr;
		MovieNodeLL* index = bst->head;
		while (index) {

			if (index->title > ll->title) {
				ll->next = index;
				if (!prev) {
					bst->head = ll;
				} else {
					prev->next = ll;
				}
				break;
			}

			if (!index->next) {
				index->next = ll;
				break;
			}
			prev = index;
			index = index->next;
		}
	}

	if (c > bst->letter) {
		if (bst->rightChild) {
			addMovieHelper(bst->rightChild,ll,c);
		} else {
			MovieNodeBST* n = new MovieNodeBST(c);
			bst->rightChild = n;
			n->head = ll;
		}
	} else if (c < bst->letter) {
		if (bst->leftChild) {
			addMovieHelper(bst->leftChild,ll,c);
		} else {
			MovieNodeBST* n = new MovieNodeBST(c);
			bst->leftChild = n;
			n->head = ll;
		}
	}
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
	char first;
	for (int i=0;i<title.length();i++) {
		if (title[i]!= ' ' && title[i] != '\xa0') {
			first = title[i];
			break;
		}
	}
	MovieNodeLL* newMovie = new MovieNodeLL(ranking,title,releaseYear,quantity);

	if (!root) {
		MovieNodeBST* treeNode = new MovieNodeBST(first);
		treeNode->head = newMovie;
		root = treeNode;
	} else {
		addMovieHelper(root,newMovie,first);
	}


}
void deleteMovieLLHelper(MovieNodeBST* bst,string title) {
	MovieNodeLL* index = bst->head;
	MovieNodeLL* prev = nullptr;
	while (index) {
		if (title == index->title) {
			if (prev) {
				prev->next = index->next;
			} else {
				bst->head = index->next;
			}
			delete index;
			return;
		}
		prev = index;
		index = index->next;
	}
	cout << "Movie not found." << "\n";
}
void deleteMovieHelper(MovieNodeBST* bst, string title, char c) {
	if (c == bst->letter) {
		deleteMovieLLHelper(bst,title);
		return;
	}
	if (c < bst->letter) {
		if (bst->leftChild) {
			deleteMovieHelper(bst->leftChild,title,c);
		} else {
			cout << "Movie not found." << "\n";
			return;
		}
	} else {
		if (bst->rightChild) {
			deleteMovieHelper(bst->rightChild,title,c);
		} else {
			cout << "Movie not found." << "\n";
			return;
		}
	}
}
void MovieTree::deleteMovieNode(string title) {
	char first;
	for (int i=0;i<title.length();i++) {
		if (title[i]!=' ' && title[i] != '\xa0') {
			first = title[i];
			break;
		}
	}
	deleteMovieHelper(root,title,first);
}
MovieNodeBST* treeMinimumHelper(MovieNodeBST * node) {
	if (node->leftChild) {
		return treeMinimumHelper(node->leftChild);
	} else {
		return node;
	}
}
//find min
MovieNodeBST * MovieTree::treeMinimum(MovieNodeBST * node) {
	if (node->rightChild) {
		return treeMinimumHelper(node->rightChild);
	} else {
		cout << "no lower children\n";
		return NULL;
	}
}
MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, std::string value) {
	char first;
	for (int i=0;i<value.length();i++) {
		if (value[i] != ' ' && value[i] != '\xa0') {
			first = value[i];
			break;
		}
	}
	//cout << first << "; " << node->letter << "\n";
	if (first == node->letter) {
		return node;
	}
	if (first < node->letter) {
		if (node->leftChild) {
			return searchBST(node->leftChild,value);
		} else {
			return NULL;
		}
	} else {
		if (node->rightChild) {
			return searchBST(node->rightChild,value);
		} else {
			return NULL;
		}
	}
}
void MovieTree::findMovie(std::string title) {
	MovieNodeBST* bst = searchBST(root,title);
	if (!bst) {
		cout << "Movie not found.\n";
		return;
	}
	MovieNodeLL* index = bst->head;
	while (index) {

		if (index->title == title) {
			cout << "Movie Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << index->ranking << endl;
			cout << "Title:" << index->title << endl;
			cout << "Year:" << index->year << endl;
			cout << "Quantity:" << index->quantity << endl; 
			return;
		}

		index = index->next;
	}
	cout << "Movie not found.\n";
}
void MovieTree::rentMovie(std::string title) {
    MovieNodeBST* bst = searchBST(root,title);
	if (!bst) {
		cout << "Movie not found.\n";
		return;
	}
	MovieNodeLL* index = bst->head;
	while (index) {

		if (index->title == title) {
			if (index->quantity>0) {
				index->quantity -= 1;
				cout << "Movie has been rented." << endl;
				cout << "Movie Info:" << endl;
				cout << "===========" << endl;
				cout << "Ranking:" << index->ranking << endl;
				cout << "Title:" << index->title << endl;
				cout << "Year:" << index->year << endl;
				cout << "Quantity:" << index->quantity << endl; 
			} else {
				cout << "Movie not found.\n";
				deleteMovieNode(title);
			}

			return;
		}

		index = index->next;
	}
	cout << "Movie not found.\n";
}
void countMovieNodesHelper(MovieNodeBST *node, int *c) {
	if (!node) {
		return;
	}
	MovieNodeLL* index = node->head;
	while (index) {
		//hey that's my language
		(*c)++;

		index = index->next;
	}

	if (node->leftChild) {
		countMovieNodesHelper(node->leftChild,c);
	}
	if (node->rightChild) {
		countMovieNodesHelper(node->rightChild,c);
	}
}
int MovieTree::countMovieNodes() {
	int* c = 0;
	countMovieNodesHelper(root,c);
}