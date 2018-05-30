#include "BHeap.hpp"

using namespace std;

BHeap::BHeap() {

}

BHeap::~BHeap() {
	for (int i=0;i<num;i++) {
		delete arr[i];
	}
}

bool greaterP(BHNode* one, BHNode* two) {
	if (one->priority < two->priority) {
		return false;
	} else if (one->priority > two->priority) {
		return true;
	} else {
		if (one->treatment > two->treatment) {
			return false;
		} else if (one->treatment < two->treatment) {
			return true;
		} else {
			//if both are identical return false anyway
			return false;
		}
	}
}

int parent(int i) {
	return (i+1)/2;
}

void BHeap::push(string n, int p, int t) {
	BHNode* node = new BHNode(n,p,t);

	if (num == 0) {
		arr[0] = node;
		num++;
		return;
	}

	int index = num;
	num++;
	while (!greaterP(arr[(index+1)/2-1],node)) {
		//cout << arr[(index+1)/2-1]->priority << "||" << node->priority << "||";
		int temp = index;
		index = (index+1)/2-1;
		arr[temp] = arr[index];

		if (index == 0) {
			break;
		}
	}
	arr[index] = node;
}

BHNode* BHeap::pop() {
	BHNode* toReturn = arr[0];
	//is left child greater than right child?
	arr[0] = arr[num-1];
	num--;
	BHNode* node = arr[0];
	int index = 0;
	//true if existing and bigger than parent
	bool left = (2*(index+1)-1 > num)?false:(!greaterP(node,arr[2*(index+1)-1]))?true:false;
	bool right = (2*(index+1) > num)?false:(!greaterP(node,arr[2*(index+1)]))?true:false;
	
	//while top is less than either child
	while(left || right) {
		//cout << "__ " << left << ";" << arr[index] << ";" << right << "__\n";
		if (left && right) {
			//find biggest child
			bool big = (greaterP(arr[2*(index+1)-1],arr[2*(index+1)]))?true:false;
			if (big) {
				right = false;
			} else {
				left = false;
			}
		}

		if (left) {
			arr[index] = arr[2*(index+1)-1];
			arr[2*(index+1)-1] = node;
			index = 2*(index+1)-1;
		}
		if (right) {
			arr[index] = arr[2*(index+1)];
			arr[2*(index+1)] = node;
			index = 2*(index+1);
		}
		left = (2*(index+1)-1 > num)?false:(!greaterP(node,arr[2*(index+1)-1]))?true:false;
		right = (2*(index+1) > num)?false:(!greaterP(node,arr[2*(index+1)]))?true:false;
	}

	return toReturn;
}
BHNode* BHeap::find() {
	num--;
	return arr[0];
}