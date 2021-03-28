//LCD
//identifying LCD related variables
int LCD_Address = 0x27;
int LCD_Columns = 16;
int LCD_Rows = 2;
int LCD_status_updated = 0;
//end


//identifying motor system related variables

int Motor_R_Speed  = 5, Motor_R_Dir = 6, Motor_L_Speed =9, Motor_L_Dir = 10;
int turn[2]; //[turn_value, turn_Dir]
int turning_forward_direction = 0,turning_reverse_direction = 1;
int Max_turn_value = 180;
int Min_turn_value = 10;
int throttle[2]; //[throttle_value, throttle_Dir]
int throttle_forward_direction = 0,throttle_reverse_direction = 1;
int Max_throttle_value = 255;
int Min_throttle_value = 25; 
int v1, v2;

// end


//including essintial libraries

  #include <BlynkSimpleSerialBLE.h>
  //For LCD
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>

//end


//identifying essential connection variables

#define BLYNK_USE_DIRECT_CONNECT
char auth[] = "???";

//end


BLYNK_WRITE(V1) //turn
{
   v1 = (param.asInt()); // assigning incoming value from pin V1 to a variable
}

BLYNK_WRITE(V2) //throttle
{
   v2 = (param.asInt()); // assigning incoming value from pin V2 to a variable
}


//turning functions

int get_turn_val(int turn_input_val = v1){
  if(turn_input_val<500){
    turn[0] = map(turn_input_val,500,0,Min_turn_value,Max_turn_value);
    turn[1] = turning_forward_direction;
  }
  else if(524<turn_input_val && turn_input_val<=1024){
    turn[0] = map(turn_input_val,524,1024,Min_turn_value,Max_turn_value);
    turn[1] = turning_reverse_direction;
  }
  else{
    turn[0] =0;
  }
  return turn;
}

//end


//throttling functions

int get_throttle_value(int throttle_input_val = v2){
  if(throttle_input_val<500){
    throttle[0] = map(throttle_input_val,500,0,Min_throttle_value,Max_throttle_value);
    throttle[1] = throttle_forward_direction;
  }
  else if(524<throttle_input_val && throttle_input_val<=1024){
    throttle[0] = map(throttle_input_val,524,1024,Min_throttle_value,Max_throttle_value);
    throttle[1] = throttle_reverse_direction;
  }
  else{
    throttle[0] = 0;
  }
  return throttle;
}

void Stop(){
  analogWrite(Motor_R_Speed, 0);
  digitalWrite(Motor_R_Dir, 0);
  analogWrite(Motor_L_Speed, 0);
  digitalWrite(Motor_L_Dir, 0);
}
//car turnning algorithms
void Turn_Right(){
  analogWrite(Motor_R_Speed, throttle[0]-turn[0]);
  digitalWrite(Motor_R_Dir, throttle[1]);
  analogWrite(Motor_L_Speed, throttle[0]+turn[0]);
  digitalWrite(Motor_L_Dir, throttle[1]);
}
void Turn_Left(){
  analogWrite(Motor_R_Speed, throttle[0]+turn[0]);
  digitalWrite(Motor_R_Dir, throttle[1]);
  analogWrite(Motor_L_Speed, throttle[0]-turn[0]);
  digitalWrite(Motor_L_Dir, throttle[1]);
}
//end

void drive(){
  get_turn_val();
  get_throttle_value();
  if(throttle[0] == 0){
    Stop();
  }
  else if(turn[1] == 1){
    Turn_Right();
  }
  else if(turn[1] == 0){
    Turn_Left();
  }
}

//end

//LCD inetializiation 
LiquidCrystal_I2C lcd(LCD_Address,LCD_Columns,LCD_Rows);
//end

void LCD(){
  if(LCD_status_updated == 0){
   lcd.setCursor(1,1);
   lcd.print("Connected");
  }
}

void setup() {
  Serial.begin(38400);
  Blynk.begin(Serial, auth);
  pinMode(Motor_R_Speed, OUTPUT);   // initializing the motors
  pinMode(Motor_R_Dir, OUTPUT);
  pinMode(Motor_L_Speed, OUTPUT);
  pinMode(Motor_L_Dir, OUTPUT);
  lcd.init();                      // initializing the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Car Ready");
  lcd.setCursor(1,1);
  lcd.print("Awaiting connection...");
}

void loop() {
  Blynk.run();
  if (Blynk.connected(){
      LCD();
      drive();
  }
  else{
    LCD_status_updated = 0;
    lcd.setCursor(1,0);
    lcd.print("Disconnected");
    lcd.setCursor(1,1);
    lcd.print("Please reconnect...");
  }
}
