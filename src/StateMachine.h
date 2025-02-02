#include <list> // Add this line
#include "State.h"
#include <functional>

#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

class StateMachine
{
  public:
    // Methods
    
    StateMachine();
    ~StateMachine();
    void init();
    void run();

    // When a stated is added we pass the function that represents 
    // that state logic
    State* addState(std::function<void(void)> stateFunction);
    State* addState(void (*functionPointer)());

    State* transitionTo(State* s);
    int transitionTo(int i);
    
    // Attributes
    std::list<State*> stateList; // Change LinkedList to std::list
    bool executeOnce = true; 	//Indicates that a transition to a different state has occurred
    int currentState = -1;	//Indicates the current state number
};

#endif