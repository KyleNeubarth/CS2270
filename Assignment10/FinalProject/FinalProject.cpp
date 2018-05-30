#include <iostream>
#include <time.h>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Patient.cpp"

#include "LL.cpp"
#include "BHeap.cpp"
#include <queue>

using namespace std;
using namespace std::chrono;

int numTests  = 2000;

Patient* patients[999];
int numPatients = 0;

float LLAvgs[18];
float LLDevs[18];
float BHAvgs[18];
float BHDevs[18];
float STDAvgs[18];
float STDDevs[18];
float LLAvgsPop[18];
float LLDevsPop[18];
float BHAvgsPop[18];
float BHDevsPop[18];
float STDAvgsPop[18];
float STDDevsPop[18];
int numruns = 0;

void calcStats(int numRows) {

	float arr[numTests];
    float avg = 0;
    float stdDev = 0;

    float arrPop[numTests];
    float avgPop = 0;
    float stdDevPop = 0;

    cout << "\nLinked List: ";
    LL* linkedList = new LL();
    for (int j=0;j<numTests;j++) {
    	float time;
    	high_resolution_clock::time_point t1 = high_resolution_clock::now();

		for (int i=0;i<numRows;i++) {
			linkedList->push(patients[i]->name,patients[i]->priority,patients[i]->treatment);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<float, std::milli> timeSpan = t2-t1;
		time = timeSpan.count();

		avg += time;
		arr[j] = time;

		t1 = high_resolution_clock::now();
		for (int i=0;i<numRows;i++) {
			linkedList->pop();
		}
		t2 = high_resolution_clock::now();
		timeSpan = t2-t1;
		time = timeSpan.count();

		avgPop += time;
		arrPop[j] = time;
    }

    avg /= numTests;
    avgPop /= numTests;
    for (int j=0;j<numTests;j++) {
    	stdDev += pow(arr[j]-avg,2);
    	stdDevPop += pow(arrPop[j]-avgPop,2);
    }
    stdDev = sqrt(stdDev/numTests);
    stdDevPop = sqrt(stdDevPop/numTests);
	cout << "\nBuild: ran " << numTests << " tests with an average of " << avg << " milliseconds and a standard deviation of " << stdDev;
	cout << "\nPop: ran " << numTests << " tests with an average of " << avgPop << " milliseconds and a standard deviation of " << stdDevPop;
	LLAvgs[numruns] = avg;
    LLDevs[numruns] = stdDev;
    LLAvgsPop[numruns] = avgPop;
    LLDevsPop[numruns] = stdDevPop;

	avg = 0;
    stdDev = 0;

    cout << "\nBianary Heap: ";
    BHeap* BianaryHeap = new BHeap();
    for (int j=0;j<numTests;j++) {
    	float time;
    	high_resolution_clock::time_point t1 = high_resolution_clock::now();

		for (int i=0;i<numRows;i++) {
			BianaryHeap->push(patients[i]->name,patients[i]->priority,patients[i]->treatment);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<float, std::milli> timeSpan = t2-t1;
		time = timeSpan.count();
		avg += time;
		arr[j] = time;

		t1 = high_resolution_clock::now();
		for (int i=0;i<numRows;i++) {
			BianaryHeap->pop();
		}
		t2 = high_resolution_clock::now();
		timeSpan = t2-t1;
		time = timeSpan.count();
		avgPop += time;
		arrPop[j] = time;
    }

    avg /= numTests;
    avgPop /= numTests;
    for (int j=0;j<numTests;j++) {
    	stdDev += pow(arr[j]-avg,2);
    	stdDevPop += pow(arrPop[j]-avgPop,2);
    }
    stdDev = sqrt(stdDev/numTests);
    stdDevPop = sqrt(stdDevPop/numTests);
	cout << "\nBuild: ran " << numTests << " tests with an average of " << avg << " milliseconds and a standard deviation of " << stdDev;
	cout << "\nPop: ran " << numTests << " tests with an average of " << avgPop << " milliseconds and a standard deviation of " << stdDevPop;
	BHAvgs[numruns] = avg;
    BHDevs[numruns] = stdDev;
    BHAvgsPop[numruns] = avgPop;
    BHDevsPop[numruns] = stdDevPop;

	avg = 0;
    stdDev = 0;

    cout << "\nPriority Queue C++ Library: ";
    priority_queue <Patient*,vector<Patient*>,compare<Patient*>> STDPriorityQueue;
    for (int j=0;j<numTests;j++) {
    	float time;
    	high_resolution_clock::time_point t1 = high_resolution_clock::now();

		for (int i=0;i<numRows;i++) {
			STDPriorityQueue.push(patients[i]);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<float, std::milli> timeSpan = t2-t1;
		time = timeSpan.count();
		avg += time;
		arr[j] = time;

		t1 = high_resolution_clock::now();
		for (int i=0;i<numRows;i++) {
			STDPriorityQueue.pop();
		}
		t2 = high_resolution_clock::now();
		timeSpan = t2-t1;
		time = timeSpan.count();
		avgPop += time;
		arrPop[j] = time;
    }
	
	avg /= numTests;
    avgPop /= numTests;
    for (int j=0;j<numTests;j++) {
    	stdDev += pow(arr[j]-avg,2);
    	stdDevPop += pow(arrPop[j]-avgPop,2);
    }
    stdDev = sqrt(stdDev/numTests);
    stdDevPop = sqrt(stdDevPop/numTests);
	cout << "\nBuild: ran " << numTests << " tests with an average of " << avg << " milliseconds and a standard deviation of " << stdDev;
	cout << "\nPop: ran " << numTests << " tests with an average of " << avgPop << " milliseconds and a standard deviation of " << stdDevPop;
	STDAvgs[numruns] = avg;
    STDDevs[numruns] = stdDev;
    STDAvgsPop[numruns] = avgPop;
    STDDevsPop[numruns] = stdDevPop;

	numruns++;

	delete linkedList;
	delete BianaryHeap;
}

int main(int argc, char *argv[]) {

	ifstream inFile;
    inFile.open("patientData2270.csv");
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

    	patients[numPatients] = new Patient(name,priority,treatment);
    	numPatients++;
    }

    for (int i=50;i<numPatients;i+=50) {
    	cout << "\nResults for file of size " << i << ":";
    	calcStats(i);
    }
    cout << "\nResults for file of size " << 880 << ":";
    calcStats(880);

    ofstream file;
    file.open ("Graphs/data.txt");

    cout << "\nAvgs for LL:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << LLAvgs[i];
    	if (i==17) {
    		file << 880 << "," << LLAvgs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << LLAvgs[i] << "\n";
    }
	file << "---\n";
	cout << "\nAvgs for BH:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << BHAvgs[i];
    	if (i==17) {
    		file << 880 << "," << BHAvgs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << BHAvgs[i] << "\n";
    }
    file << "---\n";
    cout << "\nAvgs for STD:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << STDAvgs[i];
    	if (i==17) {
    		file << 880 << "," << STDAvgs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << STDAvgs[i] << "\n";
    }
    file << "~~~\n";
    cout << "\nDevs for LL:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << LLDevs[i];
    	if (i==17) {
    		file << 880 << "," << LLDevs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << LLDevs[i] << "\n";
    }
    file << "---\n";
    cout << "\nDevs for BH:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << BHDevs[i];
    	if (i==17) {
    		file << 880 << "," << BHDevs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << BHDevs[i] << "\n";
    }
    file << "---\n";
    cout << "\nDevs for STD:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << STDDevs[i];
    	if (i==17) {
    		file << 880 << "," << STDDevs[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << STDDevs[i] << "\n";
    }
	file << "~~~\n";
    cout << "\nAvgs for LLPop:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << LLAvgsPop[i];
    	if (i==17) {
    		file << 880 << "," << LLAvgsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << LLAvgsPop[i] << "\n";
    }
	file << "---\n";
	cout << "\nAvgs for BHPop:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << BHAvgsPop[i];
    	if (i==17) {
    		file << 880 << "," << BHAvgsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << BHAvgsPop[i] << "\n";
    }
    file << "---\n";
    cout << "\nAvgs for STD:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << STDAvgsPop[i];
    	if (i==17) {
    		file << 880 << "," << STDAvgsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << STDAvgsPop[i] << "\n";
    }
    file << "~~~\n";
    cout << "\nDevs for LL:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << LLDevsPop[i];
    	if (i==17) {
    		file << 880 << "," << LLDevsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << LLDevsPop[i] << "\n";
    }
    file << "---\n";
    cout << "\nDevs for BH:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << BHDevsPop[i];
    	if (i==17) {
    		file << 880 << "," << BHDevsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << BHDevsPop[i] << "\n";
    }
    file << "---\n";
    cout << "\nDevs for STD:";
    for (int i=0;i<18;i++) {
    	cout << "\n" << STDDevsPop[i];
    	if (i==17) {
    		file << 880 << "," << STDDevsPop[i] << "\n";
    		break;
    	}
    	file << (i+1)*50 << "," << STDDevsPop[i] << "\n";
    }
    file << "~~~\n";
    cout << "\nTotal Avgs for LLPop:";
    for (int i=0;i<18;i++) {
        cout << "\n" << LLAvgsPop[i] + LLAvgs[i];
        if (i==17) {
            file << 880 << "," << LLAvgsPop[i] + LLAvgs[i] << "\n";
            break;
        }
        file << (i+1)*50 << "," << LLAvgsPop[i] + LLAvgs[i] << "\n";
    }
    file << "---\n";
    cout << "\nTotal Avgs for BHPop:";
    for (int i=0;i<18;i++) {
        cout << "\n" << BHAvgsPop[i] + BHAvgs[i];
        if (i==17) {
            file << 880 << "," << BHAvgsPop[i] + BHAvgs[i] << "\n";
            break;
        }
        file << (i+1)*50 << "," << BHAvgsPop[i] + BHAvgs[i] << "\n";
    }
    file << "---\n";
    cout << "\nTotal Avgs for STD:";
    for (int i=0;i<18;i++) {
        cout << "\n" << STDAvgsPop[i] + STDAvgs[i];
        if (i==17) {
            file << 880 << "," << STDAvgsPop[i]+ STDAvgs[i] << "\n";
            break;
        }
        file << (i+1)*50 << "," << STDAvgsPop[i]+ STDAvgs[i] << "\n";
    }
    file.close();
}