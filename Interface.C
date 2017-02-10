/*------------------------------------------------------------------
Implements linked list queues and stacks to perform mathematical operations

written by Chris Sievers
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
main method. gives the procedure of each input string
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

	cout << "= " << retValue << endl;
/*********************************************************
testers

 
 *********************************************************/
}

/*****************************************************************************************************
Methods that I will call from main to do all the magic
******************************************************************************************************/

/*****************************************************************************************************
takes queue as input and performs the operations indicated in the input string
preconditions: input queue must be in postfix notation
postconditions: all operations performed and returns a single integer
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
	    int c;
	    foo = stack.Pop(character);
	    int a = stoi(character);

	    foo = stack.Pop(character);
	    int b = stoi(character);

	    if(op == "+"){
	      c = a + b;    
 	 }
 	 	if(op == "-"){
	      c = b - a;
 	 }
 	 	if(op == "*"){
	      c = a * b;
 	 }
 	 	if(op == "/"){
 	 		c = b/a;
 	 	} 
 	 stack.Push(to_string(c));
    }
  }
  foo = stack.Pop(character);
  retValue = stoi(character);
  return retValue;
}

/*****************************************************************************************************
will check a single string character to see if it is an operator or not
preconditions: takes only strings of length 1
postconditions: returns true if it is an operator. False if not
******************************************************************************************************/
bool IsOperator(string character){
  bool retValue = true;
  string ops = "+-/*%";
  if(ops.find(character) == string::npos){
    retValue = false;
  }

  return retValue;

}

/*****************************************************************************************************
allows user to input a string
preconditions: none
postconditions: returns a string exactly as the user typed it in
******************************************************************************************************/
string GetInputString(){
  string response;
  cout << "\n> ";
  getline(cin, response);
  return response;
}

/*****************************************************************************************************
splits the input string into substrings based on the spaces. ie) "12 14 +" becomes |12|14|+|
preconditions: none. this will work on any string
postconditions: outputs a linked list queue
******************************************************************************************************/
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

