

#include "Step_motor_control.h"

// Step motor class

Step_motor :: Step_motor(byte pins[4]){                // Takes array of four pins in entry
  for (int i=0; i<4; i++){
    this->pins[i] = pins[i];                           // Associates used pins to private variables
  }
  init();                                              // Calls initialising function
}

// Step motor class initialisation

void Step_motor :: init(){
  for (int i= 0; i<4; i++){
    pinMode(pins[i],OUTPUT);                           // Declares output pinouts with used pins            
  }
}

// Step motor turn function

void Step_motor :: turn(int num_steps, bool clockwise = true){                         // takes in entry the number of steps moved and the turning direction (true = clockwise;false = counterclockwise)
for (int i = 0; i< num_steps; i++){                                                    // for the number of steps desired, browse through the 8 possible output cases

    // The step motor has 8 different positions. To control it, 4 inputs are required. Cases 0 to 7 each corresponds to one of the eight polarisation possible with the 4 inputs. Together they create a 
    // rotating motion. Each index of the pins array corresponds to one of the step motor input. Lines with only one input associated with the "HIGH" position corresponds to quarter circle positions and  
    // the ones with a combination of two "HIGH" corresponds to the eighths of a circle positions.

    switch(step) { 
      case 0: digitalWrite(pins[0], HIGH); digitalWrite(pins[1], LOW); digitalWrite(pins[2], LOW); digitalWrite(pins[3], HIGH); break; 
      case 1: digitalWrite(pins[0], HIGH); digitalWrite(pins[1], LOW); digitalWrite(pins[2], LOW); digitalWrite(pins[3], LOW); break; 
      case 2: digitalWrite(pins[0], HIGH); digitalWrite(pins[1], HIGH); digitalWrite(pins[2], LOW); digitalWrite(pins[3], LOW); break; 
      case 3: digitalWrite(pins[0], LOW); digitalWrite(pins[1], HIGH); digitalWrite(pins[2], LOW); digitalWrite(pins[3], LOW); break; 
      case 4: digitalWrite(pins[0], LOW); digitalWrite(pins[1], HIGH); digitalWrite(pins[2], HIGH); digitalWrite(pins[3], LOW); break; 
      case 5: digitalWrite(pins[0], LOW); digitalWrite(pins[1], LOW); digitalWrite(pins[2], HIGH); digitalWrite(pins[3], LOW); break; 
      case 6: digitalWrite(pins[0], LOW); digitalWrite(pins[1], LOW); digitalWrite(pins[2], HIGH); digitalWrite(pins[3], HIGH); break; 
      case 7: digitalWrite(pins[0], LOW); digitalWrite(pins[1], LOW); digitalWrite(pins[2], LOW); digitalWrite(pins[3], HIGH); break; 
      default: digitalWrite(pins[0], LOW); digitalWrite(pins[1], LOW); digitalWrite(pins[2], LOW); digitalWrite(pins[3], LOW); break; }
      delayMicroseconds(v);

      // For the clockwise motion the step counter is augmented by one (to browse cases from 0 to 7). The position step variable is also updated.

      if (clockwise){step++; position.step ++;}

      // For the counterclockwise motion the step counter is augmented by one (to browse cases from 7 to 0). The position step variable is also updated.

      else {step--; position.step --;}

      if (step<0){
        step = 7;              // Resets the step counter to zero at each turn completed in a clockwise motion.
      } 
      else if(step>7){
        step = 0;              // Resets the step counter to seven at each turn completed in a counterclockwise motion.
      }

      if (position.step > 4095){
        position.lap++;              // For each completed turn of the step motion, the lap is updated
        position.step = 0;           // and the position step is rest to zero
      }
      else if(position.step < 0){
        position.lap--;              // For each completed turn of the step motion, the lap is updated
        position.step = 4095;        // and the position step is rest to 4095
      }
  }
}

// Step motor speed setup function

void Step_motor :: set_speed(int v){                      // Takes in entry the desired motor speed
  if (v<800){                                            // Verifies that the speed is compatible with the max speed of the motor (800)
    Serial.println("Error, maximum speed exceeded");
    this-> v = 0;
  }
  else {
    this-> v = v;                                        // If previous condition is met, the speed is set to the new value
  }
}

// Step motor speed getting function

int Step_motor :: get_speed(){
  return v;                           // gives out the motor speed
}

// Step motor position getting function

position_struct Step_motor :: get_position(){
  return position;
}

// Step motor go to a certain position value function

void Step_motor :: go_to(position_struct pos_f){                                // Takes in entry the final position wanted

  while (position.lap != pos_f.lap or position.step != pos_f.step){             // Function condition:  being currently not at the wanted position

    int depl;                                                                   // Define depl variable

    if(position.lap == pos_f.lap and position.step > pos_f.step){
      
      depl = position.step - pos_f.step;                                        // If the initial and final position are on the same lap: depl variables equal to the step difference
      turn(depl,false);                                                         // Turn for the number of steps wanted

    }
    else if(position.lap == pos_f.lap and position.step < pos_f.step){          // Idem

      depl = pos_f.step - position.step;
      turn(depl,true);

    }

    else if(position.lap > pos_f.lap){
      turn(64,false);                                                           // If the initial and final position are on the same lap : move for 64 steps               
    }
    else if(position.lap < pos_f.lap){
      turn(64,true);                                                            // Idem
    }
  }
}

