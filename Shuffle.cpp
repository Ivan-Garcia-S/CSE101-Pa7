/*********************************************************************************
 * * * * Ivan Garcia-Sanchez, igarci33
 * * * * 2020 Spring CSE101 PA7
 * * * * Shuffle.cpp
 * * * *********************************************************************************/
#include<fstream>
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

#define MAX_LEN 300

void shuffle(List& D){
   List halfOne;
   List halfTwo;
   D.moveFront();
   for(int k = 0; k < D.size()/2; k++){
      halfOne.insertBefore(D.moveNext());  
   }
     for(int j = D.size()/2; j < D.size(); j++){
      halfTwo.insertBefore(D.moveNext());
   }
   D.clear();
   halfOne.moveFront();
   halfTwo.moveFront();
   while(halfOne.position() != halfOne.size() || halfTwo.position() != halfTwo.size()){
      if(halfTwo.position() != halfTwo.size()){
         D.insertBefore(halfTwo.moveNext());
      }
      if(halfOne.position() != halfOne.size()){
         D.insertBefore(halfOne.moveNext());
      }
   }
} 

int main(int argc, char * argv[]){
   int deckCount = stoi(argv[1]);
   List deck;
   
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <int>" << endl;
      return(EXIT_FAILURE);
   }
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   
   for(int i = 1; i <= deckCount; i++){
      int numShuffles = 0;
      deck.moveBack();
      deck.insertBefore(i-1);
      List empty;
      List originalDeck = deck;
       
      shuffle(deck);
      numShuffles++;
      
      while(!originalDeck.equals(deck)){
         shuffle(deck);
         numShuffles++;
      }
      if(i / 100 > 0){
         cout << " " << i << "             " << numShuffles << endl;
      }
      else if(i / 10 > 0){
         cout << " " << i << "              " << numShuffles << endl;
      }
      else{
         cout << " " << i << "               " << numShuffles << endl;
      }
   }

   return(0);
}
