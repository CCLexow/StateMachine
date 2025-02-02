#include <list> // Add this line

#ifndef _STATE_H
#define _STATE_H
#include <functional>

/*
 * Transition is a structure that holds the address of 
 * a function that evaluates whether or not not transition
 * from the current state and the number of the state to transition to
 */
struct Transition{
  std::function<bool()> conditionFunction;
  int stateNumber;
};

/*
 * State represents a state in the statemachine. 
 * It consists mainly of the address of the function
 * that contains the state logic and a collection of transitions 
 * to other states.
 */
class State{
  public:
    State();
    ~State();

    void addTransition(std::function<bool()> c, State* s);
    void addTransition(std::function<bool()> c, int stateNumber);
    int evalTransitions();
    int execute();
    int setTransition(int index, int stateNumber);	//Can now dynamically set the transition
    
    // stateLogic is the pointer to the function
    // that represents the state logic
    std::function<void()> stateLogic;
    std::list<struct Transition*> transitions; // Change LinkedList to std::list
    int index;
};

#endif