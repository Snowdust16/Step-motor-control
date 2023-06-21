// __Import Arduino module___ //

#ifndef JOY_H
#define JOY_H
#include <Arduino.h>

// ___Create position datastructure for the joystick___ //

struct joystick_position{
  int x;
  int y;
};

// ___Create main Joystick class___ //

class Joystick{

  // Declare private variables

  private:

  int pins[2];
  void init();                    // Class initialisation
  joystick_position J_pos;        // Joystick position variable

  // Declare public variables

  public:
  Joystick(int pins[2]);          // Joystick class
  void read_joystick();           // function : read joystick data

};

#endif