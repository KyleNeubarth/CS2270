#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue(int size) {
	queueSize = size;
	arrayQueue = new string[size];
	queueHead = 0;
	queueTail = 0;
	queueCount = 0;
}

Queue::~Queue() {
	delete [] arrayQueue;
	arrayQueue = nullptr;
}
void Queue::enqueue(string word) {
	if (queueCount==queueSize) {
		cout << "Queue is full\n";
		return;
	}
	arrayQueue[queueTail] = word;
	queueCount++;
	if (queueTail == queueSize-1) {
		queueTail = 0;
	} else {
		queueTail++;
	}
	cout << "E: " << word << "\nH: " << queueHead << "\nT: " << queueTail << "\n";
	return;
}
void Queue::dequeue() {
	if (queueCount == 0) {
		cout << "Queue is empty\n";
		return;
	}
	queueCount--;
	int temp = queueHead;
	if (queueHead == queueSize-1) {
		queueHead = 0;
	} else {
		queueHead++;
	}
	cout << "H: " << queueHead << "\nT: " << queueTail << "\nword: " << arrayQueue[temp] << "\n";
}
void Queue::printQueue() {
	if (queueCount == 0) {
		cout << "Empty\n";
		return;
	}
	int temp;
	if (queueHead >= queueTail) {
		temp = queueSize;
	} else {
		temp = queueTail;
	}
	for (int i=queueHead;i<temp;i++) {
		cout << i << ": " << arrayQueue[i] << "\n";
	}
	if (queueHead >= queueTail) {
		for (int i=0;i<queueTail;i++) {
			cout << i << ": " << arrayQueue[i] << "\n";
		}
	}
	return;
}
bool Queue::queueIsFull() {
	if (queueCount==queueSize) {
		return true;
	}
	return false;
}
bool Queue::queueIsEmpty() {
	if (queueCount==0) {
		return true;
	}
	return false;
}
void Queue::enqueueSentence(string s) {
	int start = 0;
	for (int i=0;i<(int)(s.length());i++) {
		if (s[i] == ' ') {
			enqueue(s.substr(start,i-start));
			start = i+1;
		}
		if (i == (int)(s.length())-1) {
			i++;
			enqueue(s.substr(start,i-start));
		}
	}
}