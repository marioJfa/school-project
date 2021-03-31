//LCD
//identifying LCD related variables
#define LCD_Address 0x3F
#define LCD_Columns 16
#define LCD_Rows 2
int LCD_status_updated = 0;
//end


//identifying motor system related variables

int Motor_R_Speed  = 5, Motor_R_Dir = 6, Motor_L_Speed =9, Motor_L_Dir = 10;
int turn[2]; //[turn_value, turn_Dir]
int turning_forward_direction = 0,turning_reverse_direction = 1;
int Max_turn_value = 50;
int Min_turn_value = 10;
int throttle[2]; //[throttle_value, throttle_Dir]
int throttle_forward_direction = 0,throttle_reverse_direction = 1;
int Max_throttle_value = 255;
int Min_throttle_value = 100; 
int v1, v2;

// end


//including essintial libraries

  //For LCD
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  #include <SoftwareSerial.h>

//end


//identifying essential connection variables

SoftwareSerial Bluetooth(2,3);

//end


//turning functions

int get_turn_val(int turn_input_val = turn[0]){
  if((turn_input_val%2)==0){
    turn[0] = map(turn_input_val,0,255,Min_turn_value,Max_turn_value);
    turn[1] = turning_forward_direction;
  }
  else if((turn_input_val%2)==1){
    turn[0] = map(turn_input_val,0,255,Min_turn_value,Max_turn_value);
    turn[1] = turning_reverse_direction;
  }
  else{
    turn[0] =2;
  }
  return turn;
}

//end


//throttling functions

int get_throttle_value(int throttle_input_val = throttle[0]){
  if((throttle_input_val%2)==1){
    throttle[0] = map(throttle_input_val,0,255,Min_throttle_value,Max_throttle_value);
    throttle[1] = throttle_forward_direction;
  }
  else if((throttle_input_val%2)==0){
    throttle[0] = map(throttle_input_val,0,255,Min_throttle_value,Max_throttle_value);
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
void Linear(){
  analogWrite(Motor_R_Speed, throttle[0]);
  digitalWrite(Motor_R_Dir, throttle[1]);
  analogWrite(Motor_L_Speed, throttle[0]);
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
  else if(turn[1] ==2){
    Linear();
  }
}

//end

//LCD inetializiation 
LiquidCrystal_I2C lcd(LCD_Address,LCD_Columns,LCD_Rows);
//end

void LCD(){
//  if(LCD_status_updated == 0){
   lcd.setCursor(1,1);
   lcd.print("Connected");
//  }
//  else{
    lcd.setCursor(1,0);
    lcd.print("Running");
//  }
}

void setup() {
  lcd.init();                      // initializing the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Car Ready");
  lcd.setCursor(1,1);
  lcd.print("connecting...");
  pinMode(Motor_R_Speed, OUTPUT);   // initializing the motors
  pinMode(Motor_R_Dir, OUTPUT);
  pinMode(Motor_L_Speed, OUTPUT);
  pinMode(Motor_L_Dir, OUTPUT);
  Bluetooth.begin(9600);
}

void loop() {
  while(Bluetooth.available()>=2){
    turn[0] = Bluetooth.read();
    delay(10);
    throttle[0] = Bluetooth.read();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(turn[0]);
    lcd.setCursor(1,1);
    lcd.print(throttle[0]);
    drive();
  }
}
