// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include <map>
#include <vector>
#include "random.h"

using namespace std;

class Ngrams{
    map<vector<string>, vector<string>> mapNgrams;
    vector<string> ngrams;
public:
    // Read input file and put into map
    string fileRead(ifstream &in, int grams){
        string word;
        vector<string> firstNgrams;
        for(int i =1; i<grams; i++){
            in >> word;
            // file has less words than N gram
            if(in.fail()){
                return "INVALID";
            }

            firstNgrams.push_back(word);
            ngrams = firstNgrams;
        }
        while(true){
            in >> word;
            // end of file
            if(in.fail())break;

            this->buildMap(word);
        }
        // For example, if you are computing 3-grams like the above example, perform 2 more
        //iterations to connect the last 2 prefixes in the end of the file
        // to the first 2 words at the start of the file.
        for(int i =0; i<firstNgrams.size(); i++){
            this->buildMap(firstNgrams[i]);
        }

        return "VALID";

    }

    // Helper function

    void buildMap(string &word){
        if(mapNgrams.find(ngrams) == mapNgrams.end()){
            vector<string> wordSuffix;
            wordSuffix.push_back(word);
            mapNgrams[ngrams] = wordSuffix;
        }
        else{
        // if prefix vector is already there, then add new word
            mapNgrams[ngrams].push_back(word);
        }
        // Update the window
        ngrams.erase(ngrams.begin());
        ngrams.push_back(word);
    }

    //Build the text using mapNgrams
    void buildText(int numWords){

         int wordsCount =0;
         map<vector<string>, vector<string> > ::iterator itr = mapNgrams.begin();
         int rand= randomInteger(0, mapNgrams.size()-1);
         advance(itr,rand);

         // Fetch the random key
         vector<string> ngramsCurr = itr->first;
         int ngramsSize = ngramsCurr.size();
         // Print the initial n-1 gram words
         cout<<"... ";
         for(int i =0; i<ngramsCurr.size(); i++){
             cout <<ngramsCurr[i]<<" ";
         }
         while(wordsCount < numWords - ngramsSize){
            wordsCount++;
            if(mapNgrams.find(ngramsCurr) != mapNgrams.end()){
               // cout<<" found Map ref"<<endl;
                vector<string> suffixes = mapNgrams.at(ngramsCurr);
               // cout<<" found suffix"<<endl;
                if(suffixes.size()> 0){
                    rand = randomInteger(0, suffixes.size()-1);
                    cout << suffixes[rand] << " ";
                    string nextWord = suffixes[rand];
//                    mapNgrams.at(ngramsCurr).erase(suffixes.begin()+rand);
//                itr  = mapNgrams.find(ngramsCurr);
//                itr->second.erase(suffixes.begin()+rand);
                   // suffixes.erase(suffixes.begin()+rand);

                   // mapNgrams[ngramsCurr] = suffixes;

                // Update the current vector
                ngramsCurr.erase(ngramsCurr.begin());
                ngramsCurr.push_back(nextWord);
                }

                else
                    cout<<" Exception: Suffix is empty"<<endl;
                //suffixes.clear();

            }
            else{
                cout<<"Could not find the map reference";
            }
         }
         cout<<"... "<<endl;
    }

};

int main() {

    while(true){

        string file;
        ifstream in;
        int NumGrams;
        int N;
        string ans;
        cout<<"Welcome to CS 106B Random Writer ('N-Grams')."<<endl;
        cout<<"This program makes random text based on a document."<<endl;
        cout<<"Give me an input file and an 'N' value for groups"<<endl;
        cout<<"of words, and I'll create random text for you."<<endl;

        Ngrams ngrams;

        // Input file reading
        while(true){
            cout<<"Input file name? ";
            cin >> file;
            // Opening the file
            in.open(file);

            if(!in.fail()) break;
                cout<<"Please provide the correct file name "<<endl;
        }

        while(true){
            cout<<"Value of N? ";
            cin >> NumGrams;

            if(N >=2){
                ans = ngrams.fileRead(in, NumGrams);

                if(ans == "VALID")break;

                cout<<"N is more than the number of words in file"<<endl;
            }
            else{
                cout<<"Please choose N greater than 1"<<endl;
            }
        }

        while(true){
            cout<<"# of random words to generate (0 to quit)? ";
            cin >> N;
            if(N == 0)break;
            else if(N < 0 )
                 cout<<"Please choose a positive number "<<endl;
            else if(N < NumGrams)
                 cout<<"Number of random words is less than N-grams "<<endl;
            else{
                ngrams.buildText(N);
                break;
            }
        }

        cout<<" Press q to exit and any other character to start again ";
        cin >> ans;

        if(ans == "q" || ans == "Q")break;
        cout<<endl;
        clearConsole();
    }


    return 0;
}

