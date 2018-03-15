#include <iostream>
#include <fstream>

using namespace std;

struct city{
	string cityName;
	string message;
	city *next;
	city *previous;
	city(){};
	city(string _name,city *_next,city *_prev,string _message) {
		cityName = _name;
		message = _message;
		next = _next;
		previous = _prev;
	}
};

city* head;
city* tail;

void buildNetwork() {
    string names[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    city *current = NULL;
    for (int i=9;i>=0;i--) {
    	city *temp = new city(names[i],current,NULL,"");
    	if (i==9) {
    		tail = temp;
    	}
  		if (i==0) {
  			head = temp;
  		}
    	if (temp->next) {
    		//set previous of the element after to temp
    		temp->next->previous = temp;
    	}
    	current = temp;
    }
}
void addCity(string cityName,string pCityName) {
	if (pCityName == "First") {
		city* newNode = new city(cityName,head,NULL,"");
		head->previous = newNode;
		head = newNode;
		return;
	}
	if (pCityName == "") {
		city* newNode = new city(cityName,NULL,tail,"");
		tail->next = newNode;
		tail = newNode;
		return;
	}
	city *index = head;
    bool found = false;
    while (index) {
    	if (pCityName == index->cityName) {
    		city* newNode = new city(cityName,index->next,index,"");
    		if (index->next) {
    			index->next->previous = newNode;
    		}
	    	index->next = newNode;
	    	found = true;
	    	break;
    	}
    	index = index->next;
    }
    if (!found) {
    	cout << pCityName << " not found\n";
    }
}
void deleteCity(string cityName) {

	city *index = head;
    bool found = false;
    while (index) {
    	
    	if (cityName == index->cityName) {
    		if (index->previous) {
    			index->previous->next = index->next;
    		} else {
    			head = index->next;
    		}
    		if (index->next) {
    			index->next->previous = index->previous;
    		} else {
    			tail = index->previous;
    		}
    		delete index;
	    	found = true;
	    	break;
    	}
    	index = index->next;
    }
    if (!found) {
    	cout << cityName << " not found\n";
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
    			index = tail->previous;
    			while (index) {

    				cout << index->cityName << " received " << newOne << "\n"; 

    				index = index->previous;
    			}
    		}
    	}
    }
}
void printPath(city* head) {
	if (!head) {
		cout << "Empty list" << endl;
	}
	cout << "===CURRENT PATH===\nNULL <- ";
	city *index = head;
    while (index) {

   		cout << index->cityName; 
   		if (index->next) {
   			cout << " <-> ";
   		}

    	index = index->next;
    }
    cout << " -> NULL";
    cout << "\n==================\n";
}
void deleteNetwork() {
	city *index = head;
	while (index) {
		city* temp = index;
		cout<<"deleting "<<temp->cityName<<"\n";	
    	index = index->next;
    	delete temp;
    }
    head = NULL;
    tail = NULL;
}
int main(int argc, char *argv[]) {
	head = NULL;
	tail = NULL;
	bool running = true;
	while (running) {
		cout << "======Main Menu======\n1. Build Network\n2. Print Network Path\n3. Transmit Message Coast-To-Coast-To-Coast\n4. Add City\n5. Delete City\n6. Clear Network\n7. Quit\n";
		int input;
		string sInput;
		getline(cin,sInput);
		input = stoi(sInput);
		//declare variables that will be used in switch
		string pString = "";
		string name = "";
		city* index;
		
		switch (input) {
			case 1:
				buildNetwork();
				printPath(head);
				break;
			case 2:
				printPath(head);
				break;
			case 3:
				transmitMsg(head);
				break;
			case 4:
				cout << "Enter a city name:\n";
				getline(cin,name);
				cout << "Enter a previous city name:\n";
				getline(cin,pString);
				addCity(name,pString);
				break;
			case 5:
				cout << "Enter a city name:\n";
				getline(cin,name);
				deleteCity(name);
				break;
			case 6:
				deleteNetwork();
				break;
			case 7:
				cout << "Goodbye!\n";
				deleteNetwork();
				return 0;
				break;
			default:
				cout << "input not recognized: "<< input << "\n";
				return 1;
				break;
		}
	}
}