#include <iostream>
#include <fstream>

using namespace std;

struct city{
	string cityName;
	string message;
	city *next;
	city(){};
	city(string _name,city *_next,string _message) {
		cityName = _name;
		message = _message;
		next = _next;
	}
};

city* buildNetwork() {
    string names[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    city *current = NULL;
    for (int i=9;i>=0;i--) {
    	city *temp = new city(names[i],current,"");
    	current = temp;
    }
    return current;
}
city *addCity(city *head, city *previous, string cityName) {
	
	//previous == null, place at the front of chain
	if (!previous) {
		city* newNode = new city(cityName,head,"");
		head = newNode;
		return head;
	} else {
	    city* newNode = new city(cityName,previous->next,"");
	    previous->next = newNode;
	    return head;
	}
}
void transmitMsg(city *head) {
	ifstream inFile;
    inFile.open("messageIn.txt");
    if (!inFile.is_open()) {
        cout << "Input file was not opened";
        return;
    }
    string newest;
    //read each line in the book
    while (getline(inFile,newest)) {
    	int start = 0;
    	for (int i=0;i<int(newest.length());i++) {
    		//if we find a space
    		if (newest[i]==' ' || i == int(newest.length()-1)) {
    		    //get last character
    		    if (i == int(newest.length()-1)) {
    		        i++;
    		    }
    			string newOne = newest.substr(start,i-start);
    			start = i+1;
    			//if there is an extra space in the line for some reason
    			if (newOne == "") {
    				continue;
    			}
    			city *index = head;
    			while (index) {

    				cout << index->cityName << " received " << newOne << "\n"; 

    				index = index->next;
    			}
    		}
    	}
    }
}
void printPath(city* head) {
	if (!head) {
		cout << "Empty list" << endl;
	}
	cout << "===CURRENT PATH===\n";
	city *index = head;
    while (index) {

   		cout << index->cityName << " -> "; 

    	index = index->next;
    }
    cout << " NULL";
    cout << "\n==================\n";
}
int main(int argc, char *argv[]) {
	city *head = NULL;
	bool running = true;
	while (running) {
		cout << "======Main Menu======\n1. Build Network\n2. Print Network Path\n3. Transmit Message Coast-To-Coast\n4. Add City\n5. Quit\n";
		int input;
		cin >> input;
		//declare variables that will be used in switch
		string pString = "";
		string name = "";
		city* index;
		
		switch (input) {
			case 1:
				head = buildNetwork();
				break;
			case 2:
				printPath(head);
				break;
			case 3:
				transmitMsg(head);
				break;
			case 4:
				cout << "Enter a City Name\n";
				cin >> name;
				//getline(cin,name);
				cout << "Enter a previous City Name\n";
				cin >> pString;
				//getline(cin,pString);
				//search for a city with name pString
				index = head;
				while (index) {
					if (index->cityName == pString) {
						break;
					}
    				index = index->next;
    			}
				addCity(head,index,name);
				break;
			case 5:
				cout << "Goodbye!";
				return 0;
				break;
		}
	}
}