/* 
 *  MyMotoLibrary.h - Library for controlling motors
 *  (can be used with any H-Bridge just connect the correct outputs if 4 outputs are needed connect all if 2 just sacrifice 2)
 *  Made By Mario Jeries 1/4/2021 for a school project
 *  
 *  examble code 
 *  
 *  MyMotoLibrary Motor_set_1(Motor_R_Speed_pin ,Motor_R_Dir_pin ,Motor_R_Dir_pin_inv ,Motor_L_Speed_pin ,Motor_L_Speed_pin_inv ,Motor_L_Dir_pin)
 *  
 *  void loop(){
 *  Motor_set_1.TurnLeft();
 *  }
 */
 



#ifndef MyMotorsLibrary_h
#define MyMotorsLibrary_h

#include "Arduino.h"


class MyMotorsLibrary
{
  public:
    int throttle_forward_direction = 1,throttle_reverse_direction = 0; // reverse for reversing the throttling directions
    int turning_forward_direction = 0,turning_reverse_direction = 1; // reverse for reversing the turning directions
    MyMotorsLibrary(int Motor_R_Speed_pin ,int  Motor_R_Dir_pin ,int Motor_R_Dir_pin_inv ,int Motor_L_Speed_pin ,int Motor_L_Dir_pin ,int  Motor_L_Dir_pin_inv);
    void Linear(int throttle , bool throttle_dir , bool throttle_dir_inv);
    void Turn_Left(int Turn_Speed);
    void Turn_Right(int Turn_Speed);
    void Stop();
  private:
  int _Motor_R_Speed_pin;
  int _Motor_R_Dir_pin;
  int _Motor_R_Dir_pin_inv;
  int _Motor_L_Speed_pin;
  int _Motor_L_Dir_pin;
  int _Motor_L_Dir_pin_inv;
  int _Turn_Speed;
  int _throttle_forward_direction;
  int _throttle_reverse_direction;
  int _turning_reverse_direction;
  int _turning_forward_direction;
};

#endif
