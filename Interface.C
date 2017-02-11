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
A summary of the rules follows:

1.  Print operands as they arrive.

2.  If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.

3.  If the incoming symbol is a left parenthesis, push it on the stack.

4.  If the incoming symbol is a right parenthesis, pop the stack and print the operators until you see a left parenthesis. Discard the pair of parentheses.

5.  If the incoming symbol has higher precedence than the top of the stack, push it on the stack.

6.  If the incoming symbol has equal precedence with the top of the stack, use association. If the association is left to right, pop and print the top of the stack and then push the incoming operator. If the association is right to left, push the incoming operator.

7.  If the incoming symbol has lower precedence than the symbol on the top of the stack, pop the stack and print the top operator. Then test the incoming operator against the new top of stack.

8.  At the end of the expression, pop and print all operators on the stack. (No parentheses should remain.)

compare output from this method to http://www.meta-calculator.com/learning-lab/how-to-build-scientific-calculator/infix-to-postifix-convertor.php
******************************************************************************************************/
Queue InfixToPostfix(Queue input){
  Queue postfix;
  string token;
  bool foo;
  Stack stack;

  while(!input.IsEmpty()){
    foo = input.Dequeue(token);

    //first check whether the dequeued item is a number. if it is, it immediately goes on the new queue
    if(!IsOperator(token)){
      postfix.Enqueue(token);
    }
    else{

      if(stack.IsEmpty() || token == "("){
        stack.Push(token);
      }


      else{
        string top;
        foo = stack.Top(top); 
        int tokenWeight = GetOperatorWeight(token);
        int topWeight = GetOperatorWeight(top);

        if(token == ")"){
          foo = stack.Pop(token);
          while(token != "("){
            if(!IsOperator(token)){
              postfix.Enqueue(token);
            }
            if(tokenWeight == tokenWeight){
              foo = stack.Pop(token);
              postfix.Enqueue(token);
              stack.Push(token);
            }
            if(tokenWeight > tokenWeight){
              stack.Push(token);
            }
            if(tokenWeight < tokenWeight){
              string temp;
              while(!stack.IsEmpty() && (tokenWeight < tokenWeight || tokenWeight == tokenWeight)){//this takes care of left to right association 
                foo = stack.Pop(temp);
                postfix.Enqueue(temp);
                foo = stack.Top(token);
              }
            }
          }
        }





          //checks the relationship between the incoming operator and the current operator at the top of the stack. 
          //different actions necessary for different relationships
          if(tokenWeight == tokenWeight){
            foo = stack.Pop(token);
            postfix.Enqueue(token);
            stack.Push(token);
          }
          if(tokenWeight > tokenWeight){
            stack.Push(token);
          }
          if(tokenWeight < tokenWeight){
            string temp;
            while(!stack.IsEmpty() && (tokenWeight < tokenWeight || tokenWeight == tokenWeight)){//this takes care of left to right association 
              foo = stack.Pop(temp);
              postfix.Enqueue(temp);
              foo = stack.Top(top);
            }
            stack.Push(token);
        }
      }
    }
  }

  //enqueue anything left in the stack
  while(!stack.IsEmpty()){
    foo = stack.Pop(token);
    postfix.Enqueue(token);
  }

  return postfix;
}
int GetOperatorWeight(string op){
  int weight = -1;
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
  string ops = "+-/*%()";
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

