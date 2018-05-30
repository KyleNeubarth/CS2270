#include <iostream>
#include <fstream>

#include "LL.cpp"

using namespace std;

int main(int argc, char *argv[]) {

    LL* l = new LL();

	ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
        cout << "Input file was not opened, make sure argument matches file";
        return 1;
    }

    string newest;

    bool firstLine = true;

    while (getline(inFile,newest)) {
    	//skip first line
    	if (firstLine) {
    		firstLine = false;
    		continue;
    	}

    	int start = 0;
    	int numItems = 0;
    	string name;
    	int priority;
    	int treatment;

    	for (int i=0;i<int(newest.length());i++) {
    		//if we find a comma
    		if (newest[i] == ',' || i == int(newest.length()-1)) {
    		    //get last character
    		    if (i == int(newest.length()-1)) {
    		        i++;
    		    }
    			string newOne = newest.substr(start,i-start);
    			start = i+1;
    			switch(numItems) {
    				case 0:
    					name = newOne;
    				break;
    				case 1:
    					priority = stoi(newOne);
    				break;
    				case 2:
    					treatment = stoi(newOne);
    				break;
    			}
    			numItems++;
    		}
    	}
        l->push(name,priority,treatment);
    }

    LLNode* current = l->root;

    cout << "Built linked list in order:\n";

    while (current) {
        cout << current->name << "--" << current->priority << "--" << current->treatment << "\n";
        current = current->next;
    }
    cout << "\nElements popped off:\n";
    int i = 0;
    while (l->root) {
        LLNode* popper = l->pop();
        cout << "\n" << i << "-" << popper->name << " " << popper->priority << " " << popper->treatment;
        i++;
    }
    //tidy up
    delete l;
}