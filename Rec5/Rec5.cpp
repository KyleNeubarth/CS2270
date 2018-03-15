#include <iostream>
#include "doublyLL.cpp"
using namespace std;

int main() {
	doublyLL* list = new doublyLL(1);

	//make shit
	list->insertNodeAtEnd(1);
	list->insertNodeAtEnd(1);
	list->insertNodeAtEnd(1);
	list->insertNodeAtEnd(1);
	for (int i=2;i<17;i++) {
		list->insertNodeAtEnd(i);
	}
	cout << "Initial List\n\n";
	list->print();
	cout << "\nEdited list\n\n";

	int intList[100];
	int intCount[100];
	int intListLength = 0;
	for (int i=0;i<100;i++) {
		intCount[i] = 1;
	}

	Node* index = list->head;
	//count
	while(index) {
		//if it already exists, increment, else add
		bool found = false;
		for (int i=0;i<intListLength;i++) {

			if (index->id == intList[i]) {
				intCount[i]++;
				found = true;
			}
		}
		if (!found) {
			intList[intListLength] = index->id;
			intListLength++;
		}
		index = index->next;
	}

	int deleteList[100];
	int dListLength = 0;

	//check for multiplicity
	for (int i=0;i<intListLength;i++) {
		if (intCount[i] > 1) {
			deleteList[dListLength] = intList[i];
			dListLength++;
		}
	}
	for (int i=0;i<dListLength;i++) {
		list->deleteValue(deleteList[i]);
	}
	list->print();
}