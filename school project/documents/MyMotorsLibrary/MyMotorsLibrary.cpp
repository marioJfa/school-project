/* 
 *  MyMotoLibrary.h - Library for controlling motors
 *  (can be used with any H-Bridge just need to add a *not-gate* in order to get an inverting output if needed)
 *  Made By Mario Jeries 1/4/2021 for a school project
 *  
 *  examble code 
 *  
 *  MyMotoLibrary Motor_set_1(Motor_R_Speed_pin ,Motor_R_Dir_pin,Motor_L_Speed_pin ,Motor_L_Dir_pin)
 *  
 *  void loop(){
 *  Motor_set_1.TurnLeft();
 *  }
 */
 

#include "Arduino.h"
#include "MyMotorsLibrary.h"


MyMotorsLibrary::MyMotorsLibrary(int Motor_R_Speed_pin ,int  Motor_R_Dir_pin ,int Motor_R_Dir_pin_inv ,int Motor_L_Speed_pin ,int Motor_L_Dir_pin ,int  Motor_L_Dir_pin_inv)
{
  pinMode(Motor_R_Speed_pin, OUTPUT);
  pinMode(Motor_R_Dir_pin, OUTPUT);
  pinMode(Motor_R_Dir_pin_inv, OUTPUT);
  pinMode(Motor_L_Speed_pin, OUTPUT);
  pinMode(Motor_L_Dir_pin, OUTPUT);
  pinMode(Motor_L_Dir_pin_inv, OUTPUT);
  _Motor_R_Speed_pin = Motor_R_Speed_pin;
  _Motor_R_Dir_pin = Motor_R_Dir_pin;
  _Motor_R_Dir_pin_inv = Motor_R_Dir_pin_inv;
  _Motor_L_Speed_pin = Motor_L_Speed_pin;
  _Motor_L_Dir_pin = Motor_L_Dir_pin;
  _Motor_L_Dir_pin_inv = Motor_L_Dir_pin_inv;
  _throttle_forward_direction = throttle_forward_direction;
  _throttle_reverse_direction = throttle_reverse_direction;
  _turning_forward_direction = turning_forward_direction;
  _turning_reverse_direction = turning_reverse_direction;
}
void MyMotorsLibrary::Stop(){
  analogWrite(_Motor_R_Speed_pin, 0);
  digitalWrite(_Motor_R_Dir_pin, 0);
  digitalWrite(_Motor_R_Dir_pin_inv, 0);
  analogWrite(_Motor_L_Speed_pin, 0);
  digitalWrite(_Motor_L_Dir_pin, 0);
  digitalWrite(_Motor_L_Dir_pin_inv, 0);
}
//car turnning algorithms
void MyMotorsLibrary::Turn_Right(int Turn_Speed){
  analogWrite(_Motor_R_Speed_pin, Turn_Speed);
  digitalWrite(_Motor_R_Dir_pin, _turning_forward_direction);
  digitalWrite(_Motor_R_Dir_pin_inv, _turning_reverse_direction);
  analogWrite(_Motor_L_Speed_pin, Turn_Speed);
  digitalWrite(_Motor_L_Dir_pin, _turning_reverse_direction);
  digitalWrite(_Motor_L_Dir_pin_inv, _turning_forward_direction);
}
void MyMotorsLibrary::Turn_Left(int Turn_Speed){
  analogWrite(_Motor_R_Speed_pin, Turn_Speed);
  digitalWrite(_Motor_R_Dir_pin, _turning_reverse_direction);
  digitalWrite(_Motor_R_Dir_pin_inv, _turning_forward_direction);
  analogWrite(_Motor_L_Speed_pin, Turn_Speed);
  digitalWrite(_Motor_L_Dir_pin, _turning_forward_direction);
  digitalWrite(_Motor_L_Dir_pin_inv, _turning_reverse_direction);
}
void MyMotorsLibrary::Linear(int throttle , bool throttle_Dir , bool throttle_Dir_inv){
  analogWrite(_Motor_R_Speed_pin, throttle);
  digitalWrite(_Motor_R_Dir_pin, throttle_Dir);
  digitalWrite(_Motor_R_Dir_pin_inv, throttle_Dir_inv);
  analogWrite(_Motor_L_Speed_pin, throttle);
  digitalWrite(_Motor_L_Dir_pin, throttle_Dir);
  digitalWrite(_Motor_L_Dir_pin_inv, throttle_Dir_inv);
}