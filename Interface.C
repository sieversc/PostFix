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

int Calculate(Queue input);

bool IsOperator(string character);

/***************************************************************************

****************************************************************************/

int main () {
  // Declare some useful variables
  string temp;

  // Instantiate/construct a bucket object
  Stack stack;
  
  // Get the user's intention
  cout << "Enter equation to evaluate: ";
 
  string inputString = GetInputString();
	
  //Queue queue = ;

  int retValue = Calculate(ParseInputString(inputString));

	cout << "result: " << retValue << endl;
/*********************************************************
testers
  

  
  while(!queue.IsEmpty()){
  	bool foo = queue.Dequeue(temp);
  	cout << IsOperator(temp) << endl;
  }
 
 *********************************************************/
}

/*****************************************************************************************************
Methods that I will call from main to do all the magic
******************************************************************************************************/

int Calculate(Queue input){
  int retValue;
 
  bool foo;
  Stack stack;
  string character;

  while(!input.IsEmpty()){

	  foo = input.Dequeue(character);

	  if(!IsOperator(character)){
	    stack.Push(character);
	  }

	  else{
	    string op = character;
	    foo = stack.Pop(character);
	    int a = stoi(character);

	    foo = stack.Pop(character);
	    int b = stoi(character);

	    if(op == "+"){
	      int c = a + b;
	      stack.Push(to_string(c));
 	 }
 	 	if(op == "-"){
	      int c = b - a;
	      stack.Push(to_string(c));
 	 }
 	 	if(op == "*"){
	      int c = a * b;
	      stack.Push(to_string(c));
 	 }
 	 	if(op == "/"){
 	 		int c = b/a;
 	 		stack.Push(to_string(c));
 	 	}
    }
 
  }
  foo = stack.Pop(character);
  retValue = stoi(character);
  return retValue;
}

bool IsOperator(string character){
  bool retValue = true;
  string ops = "+-/*%";
  if(ops.find(character) == string::npos){
    retValue = false;
  }

  return retValue;

}

string GetInputString(){
  string response;
  cout << "\n> ";
  getline(cin, response);
  return response;
}

Queue ParseInputString(string inputString){
  Queue tempQ; 
  string temp;
  int location;

  while(!inputString.empty()){

    if(inputString.find(" ") != string::npos){

      location = inputString.find(" ");
      temp = inputString.substr(0, location);
      tempQ.Enqueue(temp);
      inputString.erase(0, location+1);
    }

    else{
      tempQ.Enqueue(inputString);
      inputString.clear();
    }
  }

  return tempQ;
}

