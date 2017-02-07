/*------------------------------------------------------------------
A test driver for the stack/bucket class.

Written by Mikeyg
------------------------------------------------------------------*/

#include <iostream>
#include "LLStacks.h"

using namespace std;

enum EntryCode {POP, PUSH, COUNT, TOP, PRINT, QUIT};


int main () {
  // Declare some useful variables
  int response;


  // Instantiate/construct a bucket object
  Stack slop;
  
  // Get the user's intention
  cout << "\nEnter 0: withdraw(pop)\n 1: deposit(push)\n 2: stack load(numberOfItems)\n 3: top\n 4: print stack\n enter code: ";
  cin >> response;
  
  cout << endl << endl;
  return(0);
}
