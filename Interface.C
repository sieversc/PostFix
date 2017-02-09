/*------------------------------------------------------------------

------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "LLStacks.h"
#include "LLQueue.h"
#include <cstdlib>

using namespace std;

string GetInputString();

int main () {
  // Declare some useful variables
  int temp;
  int response =1;

  // Instantiate/construct a bucket object
  Stack stack;
  Queue queue;
  
  // Get the user's intention
  cout << "Enter Post-Fix equation to evaluate: ";
  string inputString = GetInputString();
 
  queue.Enqueue(response);
  stack.Push(response);

  stack.Pop(temp);
  queue.Dequeue(temp);

  cout << temp;
}

string GetInputString(){
  string response;
  cout << "\n> ";
  getline(cin, response);
  return response;
}