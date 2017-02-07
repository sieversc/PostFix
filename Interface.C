/*------------------------------------------------------------------
A test driver for the stack/bucket class.

Written by Mikeyg
------------------------------------------------------------------*/

#include <iostream>
#include "LLStacks.h"
#include "LLQueue.h"

using namespace std;

int main () {
  // Declare some useful variables
  int response;
  int temp;

  // Instantiate/construct a bucket object
  Stack slop;
  LLQueue queue;
  
  // Get the user's intention
  cout << "Enter Post-Fix equation to evaluate: ";
  cin >> response;

  queue.Enqueue(response);

  queue.Dequeue(temp);

  cout << temp;
  return(0);
}

