/*---------------------------------------------------------------------------------------------------
Implements linked list queues and stacks to perform mathematical operations. Takes input from the user
in postfix and infix notation. Outputs a single integer.
Supports:
  > +,-,*,/,%,^
    > + addition
    > - subtraction
    > * multiplication
    > / division
      > performs integer division. Will not show the remainder
    > % modulo
    > ^ exponentiation
  > parentheses
  > inputs in postfix notation          ex) 1 2 +   = 3
    > supports negative numbers as inputs
  > inputs in infix notation            ex) 1 + 2   = 3
    > supports negative numbers as inputs
  > Infix Inputs without spaces         ex) 1+2     = 3
    > does not support negative numbers as inputs
    > parentheses work though           ex) (1+2)*3 = 9


written by Chris Sievers

CSC 220 Data Structures - Dr. Goldweber
---------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "LLStacks.h"
#include "LLQueue.h"
#include <cstdlib>
#include <math.h>

using namespace std;

bool    IsOperator        (string character);       //will check a single string character to see if it is an operator or not
bool    SameCharType      (string a, string b);     //checks whether two strings are both operators or both integers. Compares the weight of both characters
int     Calculate         (Queue input);            //takes queue as input and performs the operations indicated in the input string
int     GetOperatorWeight (string op);              //here is where I assign precedences to the operators. This determines in what order they will be executed in InfixToPostFix()
Queue   InfixToPostfix    (Queue input);            //converts infix expression to postfix so that the calculate method can evaluate it
Queue   ParseInputString  (string inputString);     //splits the input string into substrings based on the spaces. ie) "12 14 +" becomes |12|14|+|
string  GetInputString    ();                       //allows user to input a string. This string must be in infix or postfix notation

/***************************************************************************
main method. gives the procedure each input string will follow in order to evaluate
the expression.
****************************************************************************/

int main () {

  // Get a string from the user to evaluate
  cout << "Enter equation to evaluate: " << endl;

  string inputString = GetInputString();
  
   //parse the equation, convert it to infix notation, then evaluate. Note if inputString is already in infix, it will still calculate just fine
  cout << endl << "=  " << Calculate(InfixToPostfix(ParseInputString(inputString))) << endl;

}

/*****************************************************************************************************
will check a single string character to see if it is an operator or not
preconditions: takes only strings of length 1
postconditions: returns true if it is an operator. False if not
******************************************************************************************************/
bool IsOperator(string character){
  bool retValue = true;
  string ops = "+-/*%()^";

  if(ops.find(character) == string::npos){
    retValue = false;
  }

  return retValue;
}

/********************************************************************
checks whether two strings are both operators or both integers. Compares the weight of both characters 
preconditions: none. just takes any two strings as arguments
postconditions: none. returns true or false based on a comparison. does not change values
*********************************************************************/
bool SameCharType(string a, string b){
  bool retValue = false;

  if(GetOperatorWeight(a) == GetOperatorWeight(b)){
    retValue = true;
  }
  return retValue;
}
/*****************************************************************************************************
takes queue as input and performs the operations indicated in the input string
preconditions: input queue must be in postfix notation
postconditions: all operations performed and returns a single integer
******************************************************************************************************/
int Calculate(Queue input){
  int retValue;
 
  bool foo;  
  Stack stack;      //used as an intermediary between input string and integer output
  string character; //place to store dequeued elements

  while(!input.IsEmpty()){
    foo = input.Dequeue(character);

    //check if the dequeued element is an integer
    if(!IsOperator(character)){
      stack.Push(character);
    }

    /*****
      if not an integer, it's an operator
      pop twice and perform the operation. push result back onto stack
    *****/
    else{
      string op = character;  //store the operator in another variable
      int c;                  //this will be our result. what we push back onto the stack
      foo = stack.Pop(character);
      int a = stoi(character);

      foo = stack.Pop(character);
      int b = stoi(character);

      //handles all the different cases for each operator
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
      if(op == "^"){
        c = pow(b, a);
      }
     stack.Push(to_string(c)); //whatever the operation, push the result
      }
  }
  foo = stack.Pop(character);   //get the top of the stack
  retValue = stoi(character);   //convert to integer
  return retValue;              //return the top of the stack(the result) as an integer
}

/****************************************************************************************************
here is where I assign precedences to the operators. This determines in what order they will be executed in InfixToPostFix(). This is also used by SameCharType()
to compare 2 strings

preconditions: none any string is accepted and will return a number
postconditions: outputs an integer corresponding to the input. 
******************************************************************************************************/
int GetOperatorWeight(string op){
  int weight = -2;
  //assigns a weight based on the operator. % is higher than * or / 
  //because I'm not sure what weight it should actually have
  if(op == "(" || op == ")"){
    weight = -1;
  }
  if(op == "+" || op == "-"){
    weight = 0;
  }
  if(op == "*" || op == "/"){
    weight = 1;
  }
  if(op == "%" || op == "^"){
    weight = 2;
  }
  
  return weight;
}

/*****************************************************************************************************
>  Enqueue integers as soon as they're dequeued
>  If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack
>  If the incoming symbol is a left parenthesis, push it on the stack
>  If the incoming symbol is a right parenthesis, pop the stack and enqueue all operators until you see a left parenthesis. Discard the pair of parentheses
>  If the incoming symbol has higher precedence than the top of the stack, push it on the stack
>  If the incoming symbol has equal precedence with the top of the stack, use association
>  If the incoming symbol has lower precedence than the symbol on the top of the stack, pop the stack and enqueue the popped operator. Then test the incoming operator against the new top of stack
>  at end of inputString, pop and print all operators on the stack
>  compare output from this method to result from online calculator: http://www.meta-calculator.com/learning-lab/how-to-build-scientific-calculator/infix-to-postifix-convertor.php

Preconditions: takes a string in Infix notation
Postconditions: outputs string in Postfix notation
******************************************************************************************************/
Queue InfixToPostfix(Queue input){
  Queue postfix;  //queue that will hold the postfix conversion
  string token;   //dequeued elements from input queue
  bool foo;       //dummy boolean
  Stack stack;    //intermediary stack between input and output queues

  while(!input.IsEmpty()){
    foo = input.Dequeue(token);

    //first check whether the dequeued item is a number. if it is, it immediately goes on the new queue
    if(!IsOperator(token)){
      postfix.Enqueue(token);
    }

    else{
      //we want to push ( onto the stack as if it were empty. this is important because order of operation depends on this
      if(stack.IsEmpty() || token == "("){
        stack.Push(token);
      }

      //if stack isn't empty, comparisons between incoming operator and operators already on stack need to be made as specified above
      else{

        string top; //place to store the value of the top of the stack. sometimes popped from stack sometimes just top()
        
        //keep an eye out for ) it needs to be handled before anything else
        if(token == ")"){
          foo = stack.Pop(top);

          while(top != "("){
            postfix.Enqueue(top);
            foo = stack.Pop(top);
          }
        }

        else{
          foo = stack.Top(top);
          //grab the weights of each operator 
          int tokenWeight = GetOperatorWeight(token);
          int topWeight = GetOperatorWeight(top);

          //checks the relationship between the incoming operator and the current operator at the top of the stack. 
          //different actions necessary for different relationships
          //if tokenWeight > topWeight, we just want to push it onto the stack. No other action necessary.
          if(tokenWeight == topWeight){
            foo = stack.Pop(top);
            postfix.Enqueue(top);
            stack.Push(token);
          }

          if(tokenWeight < topWeight){
            string temp;
            //below takes care of left to right association and makes sure you don't push a lower-weighted operator
            //on top of a higher-weighted one.
            while(!stack.IsEmpty() && GetOperatorWeight(token) <= GetOperatorWeight(top)){ 
              foo = stack.Pop(temp);
              postfix.Enqueue(temp);
              foo = stack.Top(top);
            }
          }
            //in every case, a push needs to be made 
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

/*****************************************************************************************************
splits the input string into substrings based on the spaces. ie) "12 14 +" becomes |12|14|+|
preconditions: none. this will work on any string
postconditions: outputs a linked list queue
******************************************************************************************************/
Queue ParseInputString(string inputString){
  Queue parsedQ; 
  string top;
  int location;

  //can parse a string delimited by spaces and one that is not. First Check which one was passed in as inputString
  //if not delimited by spaces, there will be no spaces throughout the whole string
  if(inputString.find(" ") == string::npos){
    string elem;
    string nextElem;

    /*****************************************************************************
      > Look at each element in the input string.
      > for any given element, if the next character is of a different type --> enqueue it
        > so 3+5 gets enqueued as |3|+|5|
      > if they are the same weight, we have a multiple digit integer. Keep checking the following characters 
        until you find a character of a different type and get a substring
        with all the digits of this integer then enqueue the whole substring as one queue entry
      > Note parentheses are not a problem here even though I've defined them as operators because SameCharType() 
        compares the weights of each character and parentheses are of weight -1, integers are -2, all other operators > -1
    *****************************************************************************/
    for(int i = 0; i < inputString.length(); i++){
      elem = inputString.at(i);

      /*
        nextElem is going to hold the next element of the list(if there is one)
        initialize it to something that won't be in the inputString
        a string of letters should do the job - we won't be entering words into a calculator
      */
      nextElem = "null";    

      //make sure you're not about to grab an element in a location longer than the inputString
      //prevents null pointer
      if(i+1 < inputString.length()){
        nextElem = inputString.at(i+1);
      }

      //if element in question is not the same type of character as its predecessor (integer followed by an operator or vice versa)
      //or it is the end of the inputString, enqueue the element
      if(!SameCharType(elem, nextElem) || nextElem == "null"){
        parsedQ.Enqueue(elem);
      }

      // multiple digit integer. Keep checking the following characters until you find a character of a different type
      if(SameCharType(elem, nextElem) && nextElem != "null"){
        int length; //substring method in c++ needs the length of the substring you want to create
        int j = 1;  //let's make a new index 
        nextElem = inputString.at(i+j); //nextElem starts with the character adjacent to element in question

        while(i+j < inputString.length() && SameCharType(elem, nextElem)){
          length = j+1;   //increase the length as condition continues to be met and j is incremented
          j++;
          nextElem = inputString.at(i+j); //grab the next element 
        }

        string token = inputString.substr(i, length); //now lets cut out the appropriate substring from inputString
        parsedQ.Enqueue(token);

            //pick up in the for loop indexed by i just after the multiple digit integer we just enqueued
            //-1 because this is the end of the for loop indexed by i and will increment immediately after.
        i = length + i - 1;     
      }
    }
  }

//This is a much simpler parsing job. this takes a string delimited by spaces and breaks it up that way
  else{
    while(!inputString.empty()){

      if(inputString.find(" ") != string::npos){

        location = inputString.find(" ");
        top = inputString.substr(0, location);
        parsedQ.Enqueue(top);
        inputString.erase(0, location+1);
      }

      //if test above returns false, we have reached the end of the inputString. Enqueue remaining characters and clear the string
      else{
        parsedQ.Enqueue(inputString);
        inputString.clear();
      }
    }
  }

  return parsedQ;
}

/*****************************************************************************************************
allows user to input a string. This string must be in infix or postfix notation otherwise the parse method may
not know what to do with it

preconditions: string must be in infix or postfix notation
postconditions: returns a string exactly as the user typed it in
******************************************************************************************************/
string GetInputString(){
  string response;
  cout << "\n> ";
  getline(cin, response);
  return response;
}