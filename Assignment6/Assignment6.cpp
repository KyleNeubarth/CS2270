#include <iostream>
#include <fstream>
#include "Tree.cpp"

int main(int argc, char *argv[]) {

	Tree* t = new Tree();

	ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
        cout << "Input file was not opened, make sure argument matches file";
        return 1;
    }
    string newest;
    while (getline(inFile,newest)) {
    	string args[4];
    	int num = 0;

    	int start = 0;
    	for (int i=0;i<int(newest.length());i++) {
    		//if we find a space
    		if (newest[i]==',' || i == int(newest.length()-1)) {
    		    //get last character
    		    if (i == int(newest.length()-1)) {
    		        i++;
    		    }
    			string newOne = newest.substr(start,i-start);
				args[num] = newOne;
				num++;    			
    			start = i+1;
    			//if there is an extra space in the line for some reason
    			if (newOne == "") {
    				continue;
    			}
    		}
    	}
    	t->InsertMovie(stoi(args[0]),args[1],stoi(args[2]),stoi(args[3]));
    }
    return 0;
	bool playing = true;
	string input;
	while (playing) {
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Delete a movie" << endl;
		cout << "5. Count the movies" << endl;
		cout << "6. Quit" << endl;
		getline(cin,input);
		int intput = stoi(input);
		switch (intput) {
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:
				playing = false;
				cout << "Goodbye!" << endl;
				break;
		}
	}
	t->~Tree();
}