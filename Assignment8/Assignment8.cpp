#include <iostream>
#include <fstream>
#include "Graph.cpp"

using namespace std;
int main(int argc, char *argv[]) {

	Graph* g = new Graph();
    /*for (unsigned int i=0;i<argc;i++) {
        cout << argv[i] << ";\n";
    }*/
	ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
        cout << "Input file was not opened, make sure argument matches file";
        return 1;
    }

    string newest;

    string cities[100];
    int numCities = 0;
    int lineNum = 0;
    while (getline(inFile,newest)) {
    	int numItems = 0;
    	string lineName;
    	int start = 0;
    	for (int i=0;i<int(newest.length());i++) {
    		//if we find a space
    		if (newest[i]==',' || i == int(newest.length()-1)) {
    		    //get last character
    		    if (i == int(newest.length()-1)) {
    		        i++;
    		    }
    			string newOne = newest.substr(start,i-start);

    			if (numItems > 0) {
	    			if (lineNum==0) {
	    				g->addVertex(newOne);
	    				cities[numCities] = newOne;
	    				numCities++;
	    			} else {
	    				if (newOne == "0") {
	    					i = newest.length();
	    					continue;
	    				} else if(newOne != "-1") {
	    					g->addEdge(lineName,cities[numItems-1],stoi(newOne));
	    					g->addEdge(cities[numItems-1],lineName,stoi(newOne));
	    				}
	    			}
    			} else {
    				lineName = newOne;
    			}

    			numItems++;
    			start = i+1;
    			//if there is an extra space in the line for some reason
    			if (newOne == "") {
    				continue;
    			}
    		}
    	}
    	lineNum++;
    }


    bool playing = true;
	string input;
	string input2;
	while (playing) {
		cout << "======Main Menu======" << endl;
		cout << "1. Print vertices" << endl;
		cout << "2. Vertex adjacent" << endl;
		cout << "3. Quit" << endl;
		getline(cin,input);
		int intput = stoi(input);
		switch (intput) {
			case 1:
				g->displayEdges();
				break;
			case 2:
				cout << "Enter first city:" << endl;
				getline(cin,input);
				cout << "Enter second city:" << endl; 
				getline(cin,input2);
				if (g->isAdjacent(input,input2)) {
					cout << "True\n";
				} else {
					cout << "False\n";
				}
				break;
			case 3:
				playing = false;
				cout << "Goodbye!" << endl;
				break;
		}
	}
}