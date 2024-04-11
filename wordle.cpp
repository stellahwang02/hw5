#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(std::string currWord, std::string floating, const std::set<std::string>& dict, int pos, std::set<std::string>& result) {
    if (pos == currWord.length()) {
        if (dict.find(currWord) != dict.end() && floating.length() == 0) {
            result.insert(currWord);
        }
        return;
    }

    if (currWord[pos] != '-') {
        // if not a blank, move on to the next position
        generateWords(currWord, floating, dict, pos+1, result);
        return;
    }

    // fill in with any character between a,z inclusive
    int numBlanks = 0;
    for (int k = pos; k < currWord.length(); k++) {
        numBlanks += (int) (currWord[k] == '-');
    }
    // if floating is shorter than the number of blanks
    if (floating.length() < numBlanks) {
        for (char c = 'a'; c <= 'z'; ++c) {
            currWord[pos] = c;
            generateWords(currWord, floating, dict, pos+1, result);
        }
    }
    // fill in with a floating character
    for (int k = 0; k < floating.length(); k++) { // floating letters -- try all combinations 
        std::string newFloating = floating.substr(0,k) + floating.substr(k+1);
        currWord[pos] = floating[k];
        generateWords(currWord, newFloating, dict, pos+1, result);
    }
}


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    std::string currWord = in;
    std::string currFloating = floating;
    generateWords(currWord, currFloating, dict, 0, result);

    return result;
}

// Define any helper functions here
