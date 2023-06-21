//////////////////////////////////////////////
//////////___Step_motor_control___////////////
///////___Nicolas_Saucier-Magistry___/////////
//////////////////////////////////////////////


// ___Import Classes___ //

#include "Step_motor_control.h"
#include "Joystick_OOP.h"

// ___Define Arduino pins used___ //

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define JX A15
#define JY A13
#define BUZZER 7

// ___Create variable types for each part of the code___ //

int num_steps = 4096;     // 28BYJ-48 motor has 4096 steps for each lap

byte pins[4] = {IN1,IN2,IN3,IN4};      // Declare datatype for step motor pins
int J_pins[2] = {JX,JY};               // Declare datatype for joystick pins
int buzzer = BUZZER;                   // Declare datatype for buzzer pins

int v = 1000;            // Default step motor speed

Step_motor motor(pins);               // Create step motor object
Joystick Joystick(J_pins);            // Create Joystick object
  
position_struct pos_f = {0,0};        // Declare datatype for in class data structure - final position wanted
position_struct pos;                  // Declare datatype for in class data structure
joystick_position J_pos;              // Declare datatype for in class data structure

// ___Setup the Arduino___ //

void setup() {

  Serial.begin(9600);
  pinMode(32, INPUT);
  pinMode(36, INPUT);
  pinMode(buzzer, OUTPUT);
  motor.set_speed(v);
  motor.go_to(pos_f);
  pos = motor.get_position();
    Serial.print("tour :");
    Serial.print(pos.lap);
    Serial.print("        pas:");
    Serial.println(pos.step);
}


// ___Create the main loop___ //

void loop() {
  // motor.go_to(pos_f);
  // position_struct x = motor.get_position();
  //   Serial.print("tour :");
  //   Serial.print(x.lap);
  //   Serial.print("        pas:");
  //   Serial.println(x.step);

  // position_struct x = motor.get_position();
  // Serial.print(x.lap);
  // Serial.println(x.step);
  // delay(1000);
  
  // Joystick.read_joystick();

  bool B_1 = digitalRead(32);
  bool B_2 = digitalRead(36);

  if (B_1 and B_2){
      digitalWrite(buzzer,HIGH);
  }
  else if (B_1){
    digitalWrite(buzzer,LOW);
    motor.turn(64,true);
    pos = motor.get_position();
    Serial.print("tour :");
    Serial.print(pos.lap);
    Serial.print("        pas:");
    Serial.println(pos.step);
  }
  else if (B_2){
    digitalWrite(buzzer,LOW);
    motor.turn(64,false);
    pos = motor.get_position();
    Serial.print("tour :");
    Serial.print(pos.lap);
    Serial.print("        pas:");
    Serial.println(pos.step);
  }
  else{
    digitalWrite(buzzer,LOW);
  }

}

// code pour imprimer position

//       Serial.print("tour :");
//      Serial.print(position.lap);
//      Serial.print("        pas:");
//      Serial.println(position.step);
