/*
Kyle Neubarth
Rhonda Hoenigman
Assignment 1
main file
*/
#include <iostream>
#include <fstream>

using namespace std;

//struct for processing message board requests, ex. I want chicken for $5
struct request {
    string item;
    bool want;
    int price;
    request() {

    }
    request(string _item,bool _want,int _price) {
        item = _item;
        want = _want;
        price = _price;
    }
};
int numRequests = 0;
request requests[100];

//If a match is found, delete it from the array, cout the correct statement, shift array back
void doMatch(int pos) {
    cout << requests[pos].item << " " << requests[pos].price << "\n";
    for (int i=pos;i<numRequests;i++) {
        requests[i] = requests[i+1];
    }
    numRequests--;
}

int main(int argc, char *argv[]) {

	ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "No file was opened, make sure argument matches file";
        return false;
    }
    //stores latest line
    string newest;
    //read each line
    while (getline(file,newest)) {
        //num used to keep track of what section of the line we are on
        int num = 0;
        string item;
        bool want;
        int price;
        //start gives the starting index of each section
        int start = 0;
        //goes through each line and finds the item, type of request, and price
        for (int i=0;i<newest.length();i++) {
            if (newest[i]==',') {
                if (num == 0) {
                    item = newest.substr(start,i);
                    start = i + 2;
                    num++;
                } else if(num == 1) {
                    //cout << newest.substr(start,i-start) << "||\n" << " for sale" << "||" << (newest.substr(start,i-start) == "for sale")<<"\n";
                    if (newest.substr(start,i-start) == "for sale") {
                        want = false;
                    } else {
                        want = true;
                    }
                    start = i + 2;
                    price = stoi(newest.substr(start));
                    break;
                }
            }
        }
        bool foundMatch = false;
        //we read the line, now let's see if it matches any existing requests
        for (int i=0;i<numRequests;i++) {
            if (requests[i].item == item) {
                if (requests[i].want != want) {
                    if (requests[i].want) {
                        if (requests[i].price >= price) {
                            //so that the price in the array is the price
                            //the item was sold for
                            requests[i].price = price;
                            doMatch(i);
                            foundMatch = true;
                            break;
                        }
                    } else {
                        if (requests[i].price <= price) {
                            doMatch(i);
                            foundMatch = true;
                            break;
                        }
                    }
                }
            }
        }
        //Didn't find match, so append to requests
        if (!foundMatch) {
            requests[numRequests] = request(item,want,price);
            numRequests++;
        }
    }
    cout << "#\n";
    //print all requests that have not been matched

    for (int i=0;i<numRequests;i++) {
            cout << requests[i].item << ", " << (requests[i].want? "wanted" : "for sale") << ", " << requests[i].price << "\n";
    }
    cout << "#\n";
    return 0;
}