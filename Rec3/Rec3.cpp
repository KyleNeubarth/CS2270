#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "No file was opened, make sure argument matches file";
        return false;
    }
    int *stuff = new int[10];
    int stuffSize = 10;
    string newest;
    //read each line
    int line = 0;
    while (getline(file,newest)) {
    	stuff[line] = stoi(newest);
    	line++;
        if (line == stuffSize) {
            int *newStuff = new int[stuffSize*2];
            for (int j=0;j<stuffSize;j++) {
                newStuff[j] = stuff[j];
            }
            delete[] stuff;
            stuffSize *= 2;
            stuff = newStuff;
        }
    }

    for (int i=0;i<line;i++) {
    	cout << stuff[i] << "\n";
    }
}