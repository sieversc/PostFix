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

int GetOperatorWeight(string op);

Queue InfixToPostfix(Queue input);

/***************************************************************************
main method. gives the procedure of each input string

****************************************************************************/

int main () {

  // Get a string from the user to evaluate
  cout << "Enter equation to evaluate: " << endl;
 
  string inputString = GetInputString();

  //int retValue = Calculate(InfixToPostfix(ParseInputString(inputString)));

  Queue queue = InfixToPostfix(ParseInputString(inputString));

  while(!queue.IsEmpty()){
    string temp;
    bool foo = queue.Dequeue(temp);
    cout << temp << endl;
  }

  //cout << endl << "=  " << retValue << endl;
}

/*****************************************************************************************************
Below main are all the Methods that I will call from main to do all the magic
******************************************************************************************************/
Queue InfixToPostfix(Queue input){
  Queue postfix;
  string token;
  bool foo;
  Stack stack;

  while(!input.IsEmpty()){
    foo = input.Dequeue(token);

    if(!IsOperator(token)){
      postfix.Enqueue(token);
    }
    else{

      if(stack.IsEmpty()){
        stack.Push(token);
      }
      string top;
      foo = stack.Top(top);      
      if(GetOperatorWeight(token) > GetOperatorWeight(top)){
        stack.Push(token);
      }
      if(GetOperatorWeight(token) < GetOperatorWeight(top)){
        string temp;
        while(GetOperatorWeight(token) < GetOperatorWeight(top)){
          foo = stack.Pop(temp);
          postfix.Enqueue(temp);
          foo = stack.Top(top);
        }
        stack.Push(token);
      }
    }
  }
  while(!stack.IsEmpty()){
    foo = stack.Pop(token);
    postfix.Enqueue(token);
  }

  return postfix;
}
int GetOperatorWeight(string op){
  int weight;
  //assigns a weight based on the operator. % is higher than * or / 
  //because I'm not sure what weight it should actually have
  if(op == "+" || op == "-"){
    weight = 0;
  }
  if(op == "*" || op == "/"){
    weight = 1;
  }
  if(op == "%"){
    weight = 2;
  }
  
  return weight;
}
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

    //check if the dequeued element is an integer
	  if(!IsOperator(character)){
	    stack.Push(character);
	  }

    //if not an integer, it's an operator
    //pop twice and perform the operation. push result back onto stack
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
      if(op == "%"){
        c = b%a;
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

bool HasHigherPrecedence(string a, string b){
  bool retValue = false;

  

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
  Queue topQ; 
  string top;
  int location;

  while(!inputString.empty()){

    if(inputString.find(" ") != string::npos){

      location = inputString.find(" ");
      top = inputString.substr(0, location);
      topQ.Enqueue(top);
      inputString.erase(0, location+1);
    }

    else{
      topQ.Enqueue(inputString);
      inputString.clear();
    }
  }

  return topQ;
}

