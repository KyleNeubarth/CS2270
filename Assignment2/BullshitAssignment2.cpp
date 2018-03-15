/*
Kyle Neubarth
Rhonda Hoenigman
Assignment 2
main file
*/

/*

int getTotalNumberNonStopWords() is not necessary in my program
int numwords (line 31) increments as each word is added

arraySort() and printTopN() are not necessary in my program
instead of sorting the whole words array, I find the top n words and store them, see lines 154-170

*/
#include <iostream>
#include <fstream>

using namespace std;

struct word{
	string name;
	int count;
	word() {}
	word(string _name) {
		name = _name;
		count = 1;
	}
};

word *words;
int numwords = 0;
int size = 100;

string *commonWords;
int numCommonWords = 0;

int numDoubles = 0;
int uniqueWords = 0;
int totalWords = 0;

//functions you want, for missing functions see line 8-16
void getStopWords(ifstream *commonFile) {
	string newest;
	while (getline(*commonFile,newest)) {
    	commonWords[numCommonWords] = newest.substr(0,newest.length());
    	numCommonWords++;
	}
}
bool isStopWord(string quarry/*array is global var*/) {
	for (int i=0;i<numCommonWords;i++) {
		if (commonWords[i] == quarry) {
			return true;
		}
	}
	return false;
}

//my functions
void doubleWords() {
	//the new array is a pointer of type word
	//but of double size
	word *newWords = new word[size*2];
	//copy over contents
    for (int j=0;j<size;j++) {
    	newWords[j] = words[j];
    }
    //size is a global var for how big the current array is, we are doubling it
   	size *= 2;
   	//delete stuff at old pointer address
   	delete [] words;
   	//set old pointer to our new doubled array
    words = newWords;
    //we doubled! Keep track of that
    numDoubles++;
}
//used to see if word already exists in words array
//returns position, or -1 if not found
int lookForWord(string quarry) {
	for (int i=0;i<numwords;i++) {
		if (words[i].name == quarry) {
			return i;
		}
	}
	return -1;
}
//used to see if a word is already in the top words array
bool isTopWord(string quarry,int numTopWords,word *topWords) {
	for (int i=0;i<numTopWords;i++) {
		if (topWords[i].name == quarry) {
			return true;
		}
	}
	return false;
}

int main(int argc, char *argv[]) {
	//allocate words array
	words = new word[100];
	commonWords = new string[50];

	/*
	argv[1] = number of top words to display
	arg[2] = file name of input file
	arg[3] = file name of words to ignore
	*/
	ifstream inFile;
    inFile.open(argv[2]);
    if (argc != 4) {
    	cout << "Wrong number of arguments, cannot read";
    	return 1;
    }
    if (!inFile.is_open()) {
        cout << "Input file was not opened, make sure argument matches file";
        return 1;
    }
    ifstream commonFile;
    commonFile.open(argv[3]);
    if (!commonFile.is_open()) {
        cout << "Common words file was not opened, make sure argument matches file";
        return 1;
    }
    string newest;

    //add all the common words to the array
    /*while (getline(commonFile,newest)) {
    	commonWords[numCommonWords] = newest.substr(0,newest.length());
    	numCommonWords++;
    }*/
    //alright you wanted a fuction for some reason so here you go
    getStopWords(&commonFile);

    //read each line in the book
    while (getline(inFile,newest)) {
    	int start = 0;
    	for (int i=0;i<newest.length();i++) {
    		//if we find a space
    		if (newest[i]==' ') {
    			string newOne = newest.substr(start,i-start);
    			start = i+1;
    			//if there is an extra space in the line for some reason
    			if (newOne == "") {
    				continue;
    			}
    			//make sure word is not common
    			if (!isStopWord(newOne)) {
    				totalWords++;
    				//look for word in list, if found increment count
    				//lookForWord() returns index of match, otherwise -1
    				int foundWord = lookForWord(newOne);
    				if (foundWord != -1) {
	    				words[foundWord].count++;
	    			} else {
	    				uniqueWords++;
	    				//else check if there is room
						if (numwords >= size) {
		    				doubleWords();
		    			}
		    			//then add the word
		    			words[numwords] =  *new word(newOne);
		    			numwords++;
	    			}
    			}
    		}
    	}
    }
    //allocate topWords, array which will hold the top n words in words[]
    word *topWords;
	int numTopWords = 0;
	topWords = new word[atoi(argv[1])];
	//loop once for each spot in the top words array
	//each loop will find the next most frequent word in words[]
	for (int i=0;i<atoi(argv[1]);i++) {
		int top = 0;
		word *topWord;
		for (int j=0;j<numwords;j++) {
			//is it bigger? is it not already in the list? is it uncommon?
			if (words[j].count>top && !isTopWord(words[j].name,numTopWords,topWords) &&!isStopWord(words[j].name)) {
				topWord = &words[j];
				top = topWord[0].count;
				numTopWords++;
			}
		}
		topWords[i] = *topWord;
	}
	//print stuff
	for (int i=0;i<atoi(argv[1]);i++) {
		cout << topWords[i].count << " - " << topWords[i].name << "\n";
	}
	cout << "#\nArray doubled: " << numDoubles;
	cout << "\n#\nUnique non-common words: " << uniqueWords;
	cout << "\n#\nTotal non-common words: " << totalWords;

	//tidy up
	delete [] words;
	delete [] commonWords;
	delete [] topWords;
}