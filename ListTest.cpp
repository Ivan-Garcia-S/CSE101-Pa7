/*********************************************************************************
 * * * Ivan Garcia-Sanchez, igarci33
 * * * 2020 Spring CSE101 PA7
 * * * ListTest.cpp
 * * * *********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){

   int i = 1;
   List A, B, C, D, E, F;

   cout << "A is empty: " << (A.isEmpty()?"true":"false") << endl;
    
   for(int j=1; j <=i; j++){
      B.insertAfter(i);
   }
   i += 3;
   for(int j=1; j <=i; j++){
      C.insertAfter(i);
      C.insertAfter(i+2);
   }
   i += 3;
   for(int j=1; j <=i; j++){
      D.insertBefore(i);
      D.insertBefore(i+1);
      D.insertBefore(i);
   }
   i += 3;
   for(int j=1; j <=i; j++){
      E.insertBefore(i);
      E.insertAfter(i+5);
      E.insertBefore(i-5);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "first 4: " << C.findNext(4) << endl;
   cout << "second 4: " << C.findNext(4) << endl;
   C.moveFront();
   
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   for(int j = 0; j < B.size(); j++){
      B.eraseBefore();
   } 
   cout << "B after erasing all: " << B << endl;
   
   int size = C.size();
   for(int j = 0; j < size; j++){
      C.eraseAfter();
   }
   cout << "C after erasing all: " << C << endl;
   
   cout << "Size of C: " << C.size() << endl;
 
   D.cleanup();
   cout << "D after cleanup(): " << D << endl;
   
   F = A;
   cout << "F after setting to empty A: " << F << endl;
   
   F = E;
   cout << "F after setting to E: " << F << endl;
  
   F.clear();
   
   cout << "empty A equals empty F: " << (A.equals(F)?"true":"false") << endl;
   
   E.insertAfter(1);
   E.insertAfter(2);
   E.insertAfter(3);

   B.concat(C);
   cout << "B after joining with C: " << B << endl;
   D.concat(E);
   cout << "D after joining with E: " << B << endl;

   
   return(0);
}
