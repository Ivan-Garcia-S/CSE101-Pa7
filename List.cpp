/*********************************************************************************
 *  * * Ivan Garcia-Sanchez, igarci33
 * * * 2020 Spring CSE101 PA7
 * * * List.cpp
 * * * *********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

#define START -1
#define END -2

using namespace std;


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(START);
   backDummy = new Node(END);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = new Node(START);
   backDummy = new Node(END);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this
   Node* N = L.frontDummy->next;
   while( N != L.backDummy ){
      this->insertBefore(N->data);
      N = N->next;
   }
   this->moveFront();
}

// Destructor
List::~List(){
   if( !isEmpty() ){
      this->clear();
   }
   delete frontDummy;
   delete backDummy;
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if List is empty, otherwise returns false.
bool List::isEmpty(){
   return(num_elements==0);
}


// size()
// Returns the length of List.
int List::size(){
   return(num_elements);
}

int List::position(){
   return(pos_cursor);
}

// Manipulation procedures ----------------------------------------------------

void List::moveFront(){
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
}

void List::moveBack(){
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = num_elements;
}

int List::peekNext(){
   if( position() >= num_elements ){
      cerr << "List Error: calling peekNext() with no next element" << endl;
      exit(EXIT_FAILURE);
   }
   return afterCursor->data;
}

int List::peekPrev(){
   if( position() == 0 ){
      cerr << "List Error: calling peekPrev() with no previous element" << endl;
      exit(EXIT_FAILURE);
   }
   return beforeCursor->data;
}

int List::moveNext(){
   if( position() >= num_elements ){
      cerr << "List Error: calling moveNext() with no next element" << endl;
      exit(EXIT_FAILURE);
   }
   pos_cursor++;
   
   afterCursor = afterCursor->next;
   beforeCursor = beforeCursor->next;
   return beforeCursor->data;
}

int List::movePrev(){
   if( position() == 0 ){
      cerr << "List Error: calling movePrev() with no previous element" << endl;
      exit(EXIT_FAILURE);
   }
   pos_cursor--;
   beforeCursor = beforeCursor->prev;
   afterCursor = afterCursor->prev;
   return afterCursor->data;
}

void List::insertBefore(int x){
   Node* N = new Node(x);
   N->prev = beforeCursor;
   beforeCursor->next = N;
   N->next = afterCursor;
   afterCursor->prev = N;
   beforeCursor = N;
   pos_cursor++;
   num_elements++;
}

void List::insertAfter(int x){
   Node* N = new Node(x);
   N->prev = beforeCursor;
   beforeCursor->next = N;
   N->next = afterCursor;
   afterCursor->prev = N;
   afterCursor = N;
   num_elements++;
}

void List::eraseAfter(){
   if(pos_cursor >= num_elements){
      cerr << "List Error: calling eraseAfter() with no next element" << endl;
      exit(EXIT_FAILURE);
   }
   Node* remove = afterCursor;
   afterCursor = afterCursor->next;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;
   
   delete remove;
   num_elements--;
}

void List::eraseBefore(){
   if(pos_cursor == 0){
      cerr << "List Error: calling eraseBefore() with no previous element" << endl;
      exit(EXIT_FAILURE);
   }
   Node* remove = beforeCursor;
   beforeCursor = beforeCursor->prev;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;
   delete remove;
   num_elements--;
   pos_cursor--;
   
}

int List::findNext(int x){
   while(afterCursor != backDummy){
      if(afterCursor->data == x){
         this->moveNext();
         return pos_cursor;
      }
      this->moveNext();
   }
   return -1;
}

int List::findPrev(int x){
   while(beforeCursor != frontDummy){
      if(beforeCursor->data == x){
         this->movePrev();
         return pos_cursor;
      }
      this->movePrev();
   }
   return -1;
}

void List::cleanup(){
   Node* oldBefore = beforeCursor;
   Node* oldAfter = afterCursor;
   this->moveFront();
   if(!isEmpty()){
      moveNext();
   }
   while(afterCursor != backDummy){
      if(position() < size()){
         int checkNum = beforeCursor->data;
         int place = this->position();
         while(this->findNext(checkNum) != -1){
            if(beforeCursor == oldBefore){
               oldBefore = oldBefore->prev;
            }
            else if(beforeCursor == oldAfter){
               oldAfter = oldAfter->next;
            }
            this->eraseBefore();
         }
         moveFront();
         while(position() != place  && position() != size()){
            moveNext();
         }
         if(position() != size()){
            moveNext();
         }
      }
      else{
         moveBack();
      }
   }
   moveFront();
   while(beforeCursor != oldBefore){
      moveNext();
   }
}

void List::clear(){
   this->moveFront();
   while(!isEmpty()){
      this->eraseAfter();
   }
}

List List::concat(const List& L){
   List joinedList;
   Node *M = this->frontDummy->next;
   while(M != this->backDummy){
      joinedList.insertBefore(M->data);
      M = M->next;
   }
   Node* N = L.frontDummy->next;
   while(N != L.backDummy){
      joinedList.insertBefore(N->data);
      N = N->next;
   }
   joinedList.moveFront();

   return joinedList;   
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of List consisting of a space separated 
// list of data values.
string List::to_string(){
   Node* N = nullptr;
   string s = "(";

   for(N=frontDummy->next; N!=backDummy && N!= backDummy->prev; N=N->next){
      s += std::to_string(N->data)+", ";
   }
   if(N == backDummy->prev){
      s += std::to_string(N->data);
   }
   s += ")";
   return s;
}

// equals()
// Returns true if and only if this is the same integer sequence as Q.
bool List::equals(const List& L){
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->size() == L.num_elements );
   N = this->frontDummy->next;
   M = L.frontDummy->next;
   while( eq && N != this->backDummy ){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
ostream& operator<< ( ostream& stream,  List& L ) {
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B.
bool operator== (List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of Q.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor,temp.pos_cursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor,temp.afterCursor);
   }

   // return this with the new data installed
   return *this;
}
