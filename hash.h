//hash.h

#ifndef HASH_H_EXISTS
#define HASH_H_EXISTS

#include <list>
#include <string>
#include <iostream>
#include <vector>

class Hash{
    private:
        //create a slot for all 26 letters of the alphabet
        static const int indexes = 26;
        //create 26 linked list of type string
        std::list<std::string> table[indexes];
    public:
        //create a function to determine which slot each word goes to
        int hashFunction(std::string word);
        //insert the word into the corresponding slot
        void insert(std::string word);
        //print the entire hashtable
        //for testing purposes
        void printHashTable();
        //check if the user's input is in the dictionary
        //if not, then check if the dictionary has any similar words
        std::string spellCorrection(std::string userInput);
        //create a function that takes a user inputed word and returns words that start with the same two letters
        void wordSuggestion(std::string word);
        //create a function to divide the word into grams
        void nGrams(std::string word, std::vector<std::string>& createdGrams);
        //create a function to compare how many grams are similar
        void intersection(std::vector<std::string> v1, std::vector<std::string> v2, std::vector<std::string>& v3);
        

};//end calss definition

#endif