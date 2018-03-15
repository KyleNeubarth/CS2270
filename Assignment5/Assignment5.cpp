#include <iostream>
#include <fstream>
#include "Queue.h"

using namespace std;

int main() {
	Queue* q = new Queue(10);
	bool playing = true;
	string input;
	string word;
	while (playing) {
		cout << "======Main Menu=====\n1. Enqueue word\n2. Dequeue word\n3. Print queue\n4. Enqueue sentence\n5. Quit\n";
		getline(cin,input);
		switch (stoi(input)) {
			case 1:
				cout << "word: ";
				getline(cin,word);
				q->enqueue(word);
				break;
			case 2:
				q->dequeue();
				break;
			case 3:
				q->printQueue();
				break;
			case 4:
				cout << "sentence: ";
				getline(cin,word);
				q->enqueueSentence(word);
				break;
			case 5:
				delete q;
				cout << "Goodbye!\n";
				playing = false;
				break;
		}
	}
}