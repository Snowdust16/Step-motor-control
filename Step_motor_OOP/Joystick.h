// --- Importation of mouse module --- //

#include "Mouse.h"

// --- Define Variables --- 

const int x_pos = A15;
const int y_pos = A13;


// --- Setup --- //

void joystick_setup(){
  Serial.begin(9600);
  pinMode(x_pos, INPUT);
  pinMode(y_pos, INPUT);
}

// --- Main loop --- //

void joystick_loop(){
  int X = analogRead(x_pos);
  int Y = analogRead(y_pos);
  Serial.print(X);
  Serial.print("      ");
  Serial.println(Y);
}