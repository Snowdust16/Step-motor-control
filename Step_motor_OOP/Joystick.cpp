
#include "Joystick_OOP.h"

// Joystick class 

Joystick :: Joystick(int pins[2]){                 // Takes array of two pins in entry
  for (int i=0; i<2; i++){
    this->pins[i] = pins[i];                       // Associates used pins to private variables
  }
  init();                                          // Calls initialising function
}

// Joystick class initialisation

void Joystick :: init(){
  for (int i= 0; i<2; i++){
    pinMode(pins[i],INPUT);                        // Declares input pinouts with used pins
  }
}

// Joystick position reading function

void Joystick :: read_joystick(){
  J_pos.x = analogRead(pins[0]);                   // Read x position
  J_pos.y = analogRead(pins[1]);                   // Read y éposition
  return J_pos;
}

