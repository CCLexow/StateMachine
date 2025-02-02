#include "StateMachine.h"
// #include <Arduino.h> // Add this line for Serial

StateMachine::StateMachine(){
  // No need to initialize stateList as std::list initializes itself
  // Serial.println("StateMachine created");
}

StateMachine::~StateMachine(){
  for (auto s : stateList) {
    delete s;
  }
  // Serial.println("StateMachine destroyed");
}

void StateMachine::run(){
  // Early exit, no states are defined
  if(stateList.size() == 0) return;

  // Initial condition
  if(currentState == -1){
    currentState = 0;
  }
  
  // Execute state logic and return transitioned
  // to state number. Remember the current state then check
  // if it wasn't changed in state logic. If it was, we 
  // should ignore predefined transitions.
  int initialState = currentState;
  auto it = stateList.begin();
  std::advance(it, currentState);
  int next = (*it)->execute();
  
  if(initialState == currentState){
    if(next == -1){
      executeOnce = false;
    } else {
      executeOnce = true;
      currentState = next;
    }
  } else {
    executeOnce = true;
  }

  // Serial.print("Current state: ");
  // Serial.print(currentState);
  // Serial.print(", Next state: ");
  // Serial.print(next);
  // Serial.print(", Execute once: ");
  // Serial.println(executeOnce);
}

State* StateMachine::addState(void(*functionPointer)()){
  State* s = new State();
  s->stateLogic = functionPointer;
  stateList.push_back(s);
  s->index = stateList.size() - 1;
  // Serial.print("Added state with index ");
  // Serial.println(s->index);
  return s;
}

State* StateMachine::addState(std::function<void(void)> stateFunction) {
  State* s = new State();
  s->stateLogic = [stateFunction]() { stateFunction(); };
  stateList.push_back(s);
  s->index = stateList.size() - 1;
  // Serial.print("Added state with index ");
  // Serial.println(s->index);
  return s;
}

State* StateMachine::transitionTo(State* s){
  this->currentState = s->index;
  this->executeOnce = true;
  // Serial.print("Transitioned to state ");
  // Serial.println(s->index);
  return s;
}

int StateMachine::transitionTo(int i){
  if(i < static_cast<int>(stateList.size())){
    this->currentState = i;
    this->executeOnce = true;
    // Serial.print("Transitioned to state ");
    // Serial.println(i);
    return i;
  }
  return currentState;
}