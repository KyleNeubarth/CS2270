#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord = false;
};


class Trie {
    public:
        Trie();
        ~Trie();
        void insert(string);
        int search(string);
        struct TrieNode* root;
};


Trie::Trie() {
    root = new TrieNode();
    /*for(int i=0;i<26;i++) {
        root->children[i] = new TrieNode();
    }*/
}

Trie::~Trie() {
}


void Trie::insert(string word) {

    /* Start from the root  */
    struct TrieNode* current = root;
    /* Iterate over all letters in the word  */
    if (word == "\n" || word == "") {
        return;
    }
    //cout << word << "\n";
    for (int i = 0; i < word.length(); i++) {
        int num = word[i]-'a';
        if (num > 25 || num < 0) {
            return;
        }
        if (!current->children[num]) {
            current->children[num] = new TrieNode();
        }
        current = current->children[num];
    }
    current->isEndOfWord = true;
}

int Trie::search(string word) {
    TrieNode* current = root;
 
    /*
    Starting from the root,
    we iterate over all the letters of this word.
    */
    bool found = true;
    for (int i = 0; i < word.length(); i++){
        int num = word[i]-'a';
        if (current->children[num]) {
            current = current->children[num];
        } else {
            found = false;
            break;
        }

    }
    if (found) {
        return current->isEndOfWord;
    }
    /*
    At this point, we finish iterating the word.
    Does that mean we've found this word?
    What additional condition should we check?
    */

}


void array_insert(string word, vector<string>& vocabulary, vector<int>& counter) {

    if (word == "\n" || word == "") {
        return;
    }
    for (int i = 0; i < vocabulary.size(); ++i) {
        if (word == vocabulary[i]) {
            counter[i] += 1;
            return;
        }
    }

    vocabulary.push_back(word);
    counter.push_back(1);
    return;
}


int array_search(string word, vector<string>& vocabulary, vector<int>& counter) {

    for (int i = 0; i < vocabulary.size(); ++i) {
        if (word == vocabulary[i]) {
            return counter[i];
        }
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    
    // Create a trie  
    Trie the_trie;
    //the_trie.insert("hello");
    //cout << the_trie.search("hello");
    //Read in file
    ifstream handle;
    handle.open("HungerGames_edit.txt");
    string line;
    string word;
    int a =0;
    while(getline(handle, line, '\n')) {
        stringstream sp(line);
        while (getline(handle, word, ' ')) {
            the_trie.insert(word);
        }
    }

    handle.close();
    
    clock_t t1, t2;
    t1 = clock();
    cout << "      the: " << the_trie.search("the");
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;

    t1 = clock();
    cout << "    there: " << the_trie.search("there");
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;

    t1 = clock();
    cout << "therefore: " << the_trie.search("therefore");
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;


    // Array implementation 

    handle.open("HungerGames_edit.txt");
    vector<string> vocab;
    vector<int> counter;

    while(getline(handle, line, '\n')) {

        stringstream sp(line);
        while (getline(handle, word, ' ')) {
            if (word[0] == '\n') word = word.substr(1);
            array_insert(word, vocab, counter);
        }
    }

    handle.close();

    t1 = clock();
    cout << "      the: " << array_search("the", vocab, counter);
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;

    t1 = clock();
    cout << "    there: " << array_search("there", vocab, counter);
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;

    t1 = clock();
    cout << "therefore: " << array_search("therefore", vocab, counter);
    t2 = clock();
    cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;

    return 0;
}