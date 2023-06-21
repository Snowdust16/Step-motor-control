// ___Define class variable___ //

#ifndef SMC_H
#define SMC_H

// __Import Arduino module___ //

#include <Arduino.h>

// ___Create position datastructure for the step motor___ //

struct position_struct{
  int lap;
  int step;
};

// ___Create main Step motor class___ //

class Step_motor{

  // Declare private variables

  private:
    int step = 0;                            // counter variable for turn function
    byte pins[4];
    position_struct position  = {0,0};       // Initial position : 0 laps, 0 steps
    int v = 1000;                            // Default delay between each step = 1000 microseconds
    void init();                             // Class initialisation

  // Declare public variables

  public:
    Step_motor(byte pins[4]);                              // Step motor class 
    void turn(int num_steps, bool clockwise = true);       // function : turn clockwise or counterclockwise a predermined number of steps
    void set_speed(int v);                                 // function : Speed setting 
    int get_speed();                                       // function : return speed 
    position_struct get_position();                        // function : return position  
    void go_to(position_struct pos_f);                     // function : turn until a certain position is obtained
};



#endif