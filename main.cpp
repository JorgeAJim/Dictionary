#include <iostream>
#include "hash.h"
#include<fstream>

int main(){
    //initialize the hash table
    Hash ht;

    /*Put all the words from the text file into the hash table*/

    //create an ifstream to read from the dictionary file
    std::ifstream inFile;
    //open the Dictionary file
    inFile.open("Dictionary.txt");
    //create a variable to hold the word
    std::string word;
    //loop through the text file, line by line, taking the word and putting it into the hash table
    //until you reach the final line of the text file, which should break the loop
    //this is assuming there is no whitespace anywhere in the text file
    while(!inFile.eof()){
        //get the word and put in into the variable
        std::getline(inFile, word);
        //add the word to the hash table
        ht.insert(word);
    }//end while
    //close the in-file stream
    inFile.close();
    
    //print the hash table for testing purposes
    //ht.printHashTable();

    //take user input
    std::string userInput = "";
    std::cout << "Search for word: " << std::endl;
    std::cin >> userInput;

    ht.wordSuggestion(userInput);

    return 0;

}//end main