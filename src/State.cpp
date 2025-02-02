#include "State.h"
// #include <Arduino.h> // Add this line for Serial

State::State(){
  // No need to initialize transitions as std::list initializes itself
  // Serial.print("State created with index ");
  // Serial.println(index);
}

State::~State(){
  for (auto t : transitions) {
    delete t;
  }
  // Serial.print("State with index ");
  // Serial.print(index);
  // Serial.println(" destroyed");
}

void State::addTransition(std::function<bool()> conditionFunction, State* s){
  struct Transition* t = new Transition{conditionFunction, s->index};
  transitions.push_back(t);
  // Serial.print("Added transition to state ");
  // Serial.println(s->index);
}

void State::addTransition(std::function<bool()> conditionFunction, int stateNumber){
  struct Transition* t = new Transition{conditionFunction, stateNumber};
  transitions.push_back(t);
  // Serial.print("Added transition to state ");
  // Serial.println(stateNumber);
}

int State::evalTransitions(){
  // Serial.print("Evaluating transitions for state ");
  // Serial.println(index);
  for (auto t : transitions) {
    // Serial.print("Evaluating transition to state ");
    // Serial.println(t->stateNumber);
    if (t->conditionFunction()) {
      // Serial.print("Transition to state ");
      // Serial.print(t->stateNumber);
      // Serial.println(" is true");
      return t->stateNumber;
    }
  }
  // Serial.println("No transitions evaluated to true");
  return -1;
}

int State::execute(){
  // Serial.print("Executing state logic for state ");
  // Serial.println(index);
  stateLogic();
  return evalTransitions();
}

int State::setTransition(int index, int stateNumber){
  if (transitions.size() == 0) return -1;
  auto it = transitions.begin();
  std::advance(it, index);
  (*it)->stateNumber = stateNumber;
  // Serial.print("Set transition at index ");
  // Serial.print(index);
  // Serial.print(" to state ");
  // Serial.println(stateNumber);
  return stateNumber;
}