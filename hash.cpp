#include "hash.h"
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include "TimeInterval.h"

int Hash::hashFunction(std::string word){
    //create an int to hold the calculated slot
    int slot = 0;

    //take only the first letter of the inputed word
    //then take the ascii value of that letter and store it
    //to make sure all words are stored in the same place, not matter the capitalizaton all the inputed words' first character is make into a capital letter
    slot = tolower(word[0]);
    //return the slot value mod the number of slots
    //this will make sure that the slot variable is between within the range of slots that the hash table has
    //in this case, the hash table has 26 slots, 0-25, so taking mod 26 will make sure that the calculated slot is between 0-25
    return slot % indexes;

}//end hashFunction

//insert the value into the calculated slot by adding it to the front of the linked list
void Hash::insert(std::string word){
  int slot = hashFunction(word);
  table[slot].push_front(word);

}//end insert

void Hash::printHashTable(){
  //check each of the linked list and print them one by one
  for(int i = 0; i < indexes; i++){
   //check if the linked list has any integers
   if(table[i].size() == 0){
     //continue without doing anything
     continue;
   };

   std::cout << i << ": ";

   //if the linked list has integers, then print them from the current head to the tail of the linked list
   //the use of the "auto" keyword is so that c++ can infer the data type by itself
    for(auto head = table[i].begin(); head != table[i].end(); head++){ //start with the first element of the linked list, and as long as that value doesn't equal the last value at the end of the linked list then the loop can keep going
      std::cout << *head << " "; //print the value at the current head

    }//end nested for loop
   std::cout << std::endl;

  }//end for

}//end printHashTable


//find the nGrams for the word and return the array
void Hash::nGrams(std::string word, std::vector<std::string>& createdGrams){
  //initial iterator
  int i = 0;
  int n = 1;

  //a while loop is used to divide the word into ngrams (in this case uni-grams)
  while(i <= (word.length() - 1)){

    std::string grams = word.substr(i, n);
    //since we are doing uni-grams, and some words start with a capital letter, we can force the 0th index of the unigram
    //will will be the current letter (this won't work for bi-grams or tri-grams, and "tolower" is causing some weird issues) lowercase
    //so america will result in America since America will become "america"
    grams = tolower(grams[0]);

    //insert the grams
    createdGrams.push_back(grams);
    //increase the value of i by n. This method is basically a for loop for uni-grams, but it was somewhat working for creating bi-grams
    i = i + n;
  }//end while loop


}//end nGrams

void Hash::intersection(std::vector<std::string> v1, std::vector<std::string> v2, std::vector<std::string>& v3){
  //find how many elements are in both vector 1 and vector 2
  //then place those elements into vector 3

  //sort them by alphabet
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  //find the start and end of the first two vectors
  //then insert all repeated elements into the third vector
  std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

}

std::string Hash::spellCorrection(std::string userInput){
  //assuming the first letter is correct, the program will only seach through the hash slot for that letter
  int slot = hashFunction(userInput);
  
  //divide the word into grams and store them into a vector
  std::vector<std::string> userGrams;
  //was going to use bi-grams for the bigger words, but right now I'll use unigrams for every word
  nGrams(userInput, userGrams);

  //create a threshold and see find which word has the best comparison
  float threshold = 0;

  //string to hold the bestword
  std::string bestWord = "";

  for(auto head = table[slot].begin(); head != table[slot].end(); head++){
    std::string temp = *head;
    //store the ngrams (unigrams) of the current word for later comparison
    //create the vector in the for loop so it becomes empty for every new word
    std::vector<std::string> hashGrams;
    nGrams(temp, hashGrams);

    //use a function to determine how many elements inside the vectors are the same
    //and store them inside a third vector
    std::vector<std::string> similarGrams;
    intersection(userGrams, hashGrams, similarGrams);

    //find the score by taking how many characters are the same by the overall amount of characters
    //the user's input had
    float score = (similarGrams.size()/userGrams.size());
    if( score >= threshold){
      //increase the threshold so only words just as good or better can be recommended
      threshold = score;
      //store the word if there is nothing better
      bestWord = temp;
    }//end if

  }//end for

  //return the bestword
  return bestWord;



}//end spellCorrection



void Hash::wordSuggestion(std::string word){
  //find which slot the inputed word should belong in
  int slot = hashFunction(word);

  //since the search is all lower case, make sure the user's input is all lower case
  transform(word.begin(), word.end(), word.begin(), ::tolower);

  //create a sub string to hold the first two letters of the inputed word
  std::string startingLetters = word.substr(0,2);

  //create a bool variable
  //it will turn true if there is ever a match
  //it will remain false if there is never a match
  bool match = false;

  //see if the word exist in the linked list to begin with
  //if there is match then return true
  for(auto head = table[slot].begin(); head != table[slot].end(); head++){
    //turn the current word into lower case
    std::string temp = *head;
    //turn the whole word to lowercase
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    if(word == temp){
      match = true;
    }//end if
  }//end for loop

  //if match never became true, then see if the user misspelled the word before assuming that it doesn't exist in the dictionary
  if(match == false){
    int userChoice;
    word = spellCorrection(word);
    std::cout << "Did you mean to type: " << word << " (1 for yes, 0 for no)" << std::endl;
    std::cin >> userChoice;
    if(userChoice == 1){
      match = true;
    } else {
      match = false;
    }//end if else
  }//end if

  //use boolalpha to make "match" print as true or false and not as 0 or 1
  std::cout << "The program responds: " << std::boolalpha << match << std::endl;

  //if the inputed word exist in the linked list then iterate through that linked list to find words that start with the same two letters
  //take the word at a given index and create a substring of it's two first letters
  //if the substring of the inputed word and the substring of the word in the linked list are the same then return those words
  if(match != false){
    //if the word does exist in the libary then we need to create a timer to show how long the search was
    TimeInterval time = TimeInterval();
    //start the timer
    time.start();
    //search through the corresponding slot
    for(auto head = table[slot].begin(); head != table[slot].end(); head++){
      //store the current word and make it lower case
      std::string temp = *head;
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
      //see if the first two letters of the user's input match the current word's first two letters
      if(startingLetters == temp.substr(0,2)){
        //if this is the case then print out this word as a suggestion
        std::cout << temp << std::endl;
      }//end if
    }//end for loop
    //stop the timer
    time.stop();
    //return the time it took to search 
    std::cout << time.GetInterval() << " micro-sec" << std::endl;
  }//end if

}//end wordSuggestion



