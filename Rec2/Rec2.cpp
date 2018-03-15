#include <iostream>
#include <fstream>

using namespace std;

struct CarData{
	string model;
 	string make;
 	string year;
 	CarData() {}
 	CarData(string mo, string ma, string y) {
	 	model = mo;
	 	make = ma;
	 	year = y;
 	}
};

int numCars = 0;
CarData cars[100];

int main(int argc, char *argv[]) {
	ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
        cout << "Input file was not opened, make sure argument matches file";
        return false;
    }
    ofstream outFile;
    outFile.open(argv[3]);
    if (!outFile.is_open()) {
        cout << "Output file does not exist, making a new file";
        outFile = ofstream (argv[3]);
        return false;
    }

    string newest;
    //read each line
    while (getline(inFile,newest)) {
        //num used to keep track of what section of the line we are on
        int num = 0;
        string model;
        string make;
        string year;
        //start gives the starting index of each section
        int start = 0;
        //goes through each line and finds the item, type of request, and price
        for (int i=0;i<newest.length();i++) {
            if (newest[i]==' ') {
                if (num == 0) {
                    model = newest.substr(start,i);
                    start = i + 1;
                    num++;
                } else if (num == 1) {
                    make = newest.substr(start,i-start);
                    start = i + 1;
                    year = newest.substr(start);
                    break;
                }
            }
        }
        cars[numCars] = CarData(model,make,year);
        numCars++;
    }
    for (int i=0;i<numCars;i++) {
    	outFile << cars[i].model << "\t" << cars[i].make << "\t" << cars[i].year << endl;
    	//cout << cars[i].model << "\t" << cars[i].make << "\t" << cars[i].year << endl;
    }
}