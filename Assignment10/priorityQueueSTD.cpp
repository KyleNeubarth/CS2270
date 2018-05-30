#include <iostream>
#include <fstream>
#include <queue>

#include "patient.cpp"

using namespace std;

class Node {
    public:
    string name;
    int priority;
    int treatment;
    //number that accounts for priority and treatment
    float weighted;
    Node(string n, int p, int t) {
        name = n;
        priority = p;
        treatment = t;
        weighted = p + 0.5f - (treatment*0.5f)/0.5f;
    }
    bool compare(Node* one, Node* two) {
        //less weight = closer to top of list
        return one->weighted <= two->weighted;
    }
};
//take notes bitches
template <class Node> struct compare {
  bool operator() (Node one, Node two) {return one->weighted <= two->weighted;}
  typedef Node* first_argument_type;
  typedef Node* second_argument_type;
  typedef bool result_type;
};

int main(int argc, char *argv[]) {

    priority_queue <Node*,vector<Node*>,compare<Node*>> q;

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
        Node* node = new Node(name,priority,treatment);
        q.push(node);
    }
    cout << "\nElements popped off:\n";
    int i = 0;
    while (!q.empty()) {
        Node* popper = q.top();
        q.pop();
        cout << "\n" << i << "-" << popper->name << " " << popper->priority << " " << popper->treatment;
        i++;
        delete popper;
    }
}