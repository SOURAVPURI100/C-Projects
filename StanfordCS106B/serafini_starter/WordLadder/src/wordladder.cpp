// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include <queue>

using namespace std;

class wordLadder{
    string word1,word2;
    Lexicon lex;
    Lexicon existWord;
//    stack<string> wordStack;
    queue<stack<string>> wordQueue;
public:
   // Function to build the word ladder
    void buildLadder(string &word1, string &word2){
    bool isLadderFound = false;
    stack<string> wordStack;
    wordStack.push(word1);
    // Buile the queue for first stack
    wordQueue.push(wordStack);

    while(!wordQueue.empty()){

        wordStack = wordQueue.front(); wordQueue.pop();
        string topWord = wordStack.top();

        // Check if this word is equal to the Word2
        if(topWord.compare(word2) == 0){
            printLadder(wordStack);
            isLadderFound = true;
            break;
        }

        Vector<string> newWords = buildNewWords(topWord);

        for(int i =0; i<newWords.size(); i++){
            stack<string> wordStackCopy = wordStack;
            wordStackCopy.push(newWords[i]);
            wordQueue.push(wordStackCopy);
        }

    }
    if(isLadderFound == false)
        cout<<"No Word letter found";

    }
    // Print the ladder
    void printLadder(stack<string> words){
        cout<<"Word ladder is"<<endl;
        while(!words.empty()){
             cout << words.top()<<" ";
             words.pop();
        }

    }
    //Build the dictionary
    void buildDictionary(string &fileName){
        lex = Lexicon(fileName);
    }

    // Check if word is valid or not (Dictionary + already used before)
    bool checkWordValid(string &word){
         if(lex.contains(word) && !existWord.contains(word)){
             existWord.add(word);
             return true;
         }
         return false;
    }


    Vector<string> buildNewWords(string &word){

        Vector<string> formedWords;
        for(int i =0; i<word.length(); i++){

            string newWord = word;
            for(int j =97; j<= 122; j++){
                char ch = j;

                if(ch == word[i])continue;

                newWord[i] = ch;
                // check if it is a valid word or not
                if(checkWordValid(newWord)){
                    formedWords.add(newWord);
                }

            }

        }

    return formedWords;
    }

};




int main() {
    string dict, word1, word2;
    ifstream in;
    cout << "Welcome to CS 106B Word Ladder."<<endl;
    cout << "Please give me two English words, and I will change the"<<endl;
    cout << "first into the second by changing one letter at a time."<<endl;

    // Dcitionary file reading
    while(true){
        cout<<"Dictionary file name? ";
        cin >> dict;
        // Opening the file
        in.open(dict);

        if(!in.fail()) break;
            cout<<"Please provide the correct file name "<<endl;
    }


    while(true){
        wordLadder ladder;
        ladder.buildDictionary(dict);
        cout << "Word #1 (or Enter to quit): "<<endl;
        cin >> word1;
        cout << "Word #2 (or Enter to quit): "<<endl;
        cin >> word2;
        word1 = toLowerCase(word1);
        word2 = toLowerCase(word2);
        ladder.buildLadder(word1, word2);
        cout<<endl;
        cout <<"press q to quit: or any other letter to continue: ";
        string ans;
        cin >> ans;

        if(ans == "q")
            break;
        cout<<endl;
    }


    return 0;
}
