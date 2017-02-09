/*------------------------------------------------------------------

------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "LLStacks.h"
#include "LLQueue.h"
#include <cstdlib>

using namespace std;

string GetInputString();

Queue ParseInputString(string inputString);

int main () {
  // Declare some useful variables
  string temp;

  // Instantiate/construct a bucket object
  Stack stack;
  
  // Get the user's intention
  cout << "Enter Post-Fix equation to evaluate: ";
  string inputString = GetInputString();

  Queue queue = ParseInputString(inputString);


  while(!queue.IsEmpty()){
    queue.Dequeue(temp);
    cout << temp << endl;
  }

}

string GetInputString(){
  string response;
  cout << "\n> ";
  getline(cin, response);
  return response;
}

Queue ParseInputString(string inputString){
  Queue foo; 
  string temp;
  int location;

  while(!inputString.empty()){

    if(inputString.find(" ") != string::npos){

      location = inputString.find(" ");
      temp = inputString.substr(0, location);
      foo.Enqueue(temp);
      inputString.erase(0, location+1);
    }

    else{
      foo.Enqueue(inputString);
      inputString.clear();
    }
  }

  return foo;
}