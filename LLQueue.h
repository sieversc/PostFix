#ifndef _LLQueue_H#define _LLQueue_H#include <string>#include <cstdlib>#include <iostream>/*------------------------------------------------------------The Linked List header filewritten by Chris Sievers-------------------------------------------------------------*///definition of what the queue can storetypedef int qType;struct queueNode{  qType value;  queueNode *next;};class Queue { public:  /* Constructors/Destructors */  // This constructor initializes the instance variables  Queue ();    // The destructor   ~Queue ();  //Returns the number of queueNodes we currently have. Analagous to the length of the ArrayList  //Preconditions: none  //Postconditions: none  int Size() const;  //adds a new queueNode to the end of the queue  //Preconditions: none  //Postconditions: queueSize++  void Enqueue(qType value);//returns the oldest element in the queue and removes it from queue//Preconditions: size > 0//Postconditions: queueSize--bool Dequeue(qType &value);//determines whether or not the stack is empty//preconditions none//postconditions nonebool IsEmpty() const;//returns the oldest element without removing it//preconditions: size > 0//postconditions: nonebool Next(qType &value) const;//clears the queue of all queueNodes//preconditions: none//postcondions: nonevoid Clear(); private:  /* Instance variables */  int queueSize;    queueNode *tail; };#endif