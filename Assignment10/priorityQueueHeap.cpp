#include <iostream>
#include <fstream>

#include "BHeap.cpp"

using namespace std;

int main(int argc, char *argv[]) {

    BHeap* bh = new BHeap();

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

    	bh->push(name,priority,treatment);
    }
    cout << "Built heap in order:\n\n";
    for (int i=0;i<bh->num;i++) {
    	cout << bh->arr[i]->name << "--" << bh->arr[i]->priority << "--" << bh->arr[i]->treatment << "\n";
    }
    int temp = bh->num;
    cout << "\nElements popped off:\n";
    for (int i=0;i<temp;i++) {
        BHNode* popper = bh->pop();
        cout << "\n" << i << "-" << popper->name << " " << popper->priority << " " << popper->treatment;
        /*for (int i=0;i<bh->num;i++) {
            cout << bh->arr[i]->name << "--" << bh->arr[i]->priority << "--" << bh->arr[i]->treatment << "\n";
        }*/
    }
    //tidy up
    delete bh;
}