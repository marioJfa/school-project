//LCD
//identifying LCD related variables
#define LCD_Address 0x3F
#define LCD_Columns 16
#define LCD_Rows 2
int LCD_status_updated = 0;
//end


//identifying motor system related variables

int Motor_R_Speed  = 5, Motor_R_Dir[] = {6,7}, Motor_L_Speed =9, Motor_L_Dir[] ={10,11};
int turn[2]; //[turn_value, turn_Dir]
int turn_val[2]; //used inside functions
int turning_forward_direction = 0,turning_reverse_direction = 1; // reverse for reversing the turning directions
int Max_turn_value = 45;
int Min_turn_value = 10;
int throttle[2]; //[throttle_value, throttle_Dir]
bool throttle_Dir[2];
int throttle_val[2];//used inside functions
int throttle_forward_direction = 0,throttle_reverse_direction = 1; // reverse for reversing the throttling directions
int Max_throttle_value = 255;
int Min_throttle_value = 185; 

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

void get_turn_val(int turn_input_val){
  Serial.println("Turn_Value");
  if((turn_input_val%2)==1){
    turn[0] = map(turn_input_val,0,255,Min_turn_value,Max_turn_value);
    turn[1] = turning_forward_direction;
  }
  else if((turn_input_val%2)==0){
    turn[0] = map(turn_input_val,0,255,Min_turn_value,Max_turn_value);
    turn[1] = turning_reverse_direction;
  }
}

//end

//throttling functions

void get_throttle_value(int throttle_input_val){
  Serial.println("Throttle_Value");
  if((throttle_input_val%2)==1){
    throttle[0] = map(throttle_input_val,0,255,Min_throttle_value,Max_throttle_value);
    throttle[1] = throttle_forward_direction;
  }
  else if((throttle_input_val%2)==0){
    throttle[0] = map(throttle_input_val,0,255,Min_throttle_value,Max_throttle_value);
    throttle[1] = throttle_reverse_direction;
  }
}
void get_throttle_Dir(){
    if(throttle[1] == 1){
      throttle_Dir[0] =true;
      throttle_Dir[1] =false;
    }
    else if(throttle[1] == 0){
      throttle_Dir[0] =false;
      throttle_Dir[1] =true;
    }
}
void Stop(){
  Serial.println("stop");
  analogWrite(Motor_R_Speed, 0);
  digitalWrite(Motor_R_Dir, 0);
  analogWrite(Motor_L_Speed, 0);
  digitalWrite(Motor_L_Dir, 0);
}
//car turnning algorithms
void Turn_Right(){
  Serial.println("Turn_Right");
  analogWrite(Motor_R_Speed, (throttle[0]-turn[0]));
  digitalWrite(Motor_R_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_R_Dir[1], throttle_Dir[1]);
  analogWrite(Motor_L_Speed, (throttle[0]+turn[0]));
  digitalWrite(Motor_L_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_L_Dir[1], throttle_Dir[1]);
}
void Turn_Left(){
  Serial.println("Turn_Left");
  analogWrite(Motor_R_Speed, (throttle[0]+turn[0]));
  digitalWrite(Motor_R_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_R_Dir[1], throttle_Dir[1]);
  analogWrite(Motor_L_Speed, (throttle[0]-turn[0]));
  digitalWrite(Motor_L_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_L_Dir[1], throttle_Dir[1]);
}
void Linear(){
  Serial.println("Linear");
  analogWrite(Motor_R_Speed, throttle[0]);
  digitalWrite(Motor_R_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_R_Dir[1], throttle_Dir[1]);
  analogWrite(Motor_L_Speed, throttle[0]);
  digitalWrite(Motor_L_Dir[0], throttle_Dir[0]);
  digitalWrite(Motor_L_Dir[1], throttle_Dir[1]);
}
//end

void drive(int throt,int turnn){
  Serial.println("drive");
  get_turn_val(turnn);
  get_throttle_value(throt);
  get_throttle_Dir();
  if(throttle[0] == 0){
    Stop();
  }
  else if(turn[1] == 1){
    if(turn_val[0]<=30){
      Linear();
    }
    else if(turn_val[0]>30){
      Turn_Right();
    }
  }
  else if(turn[1] == 0){
    if(turn_val[0]<=30){
      Linear();
    }
    else if(turn_val[0]>30){
      Turn_Left();
    }
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
  Bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(Bluetooth.available()>=2){
      Serial.println("Bluetooth");
      turn_val[0] = Bluetooth.read();
      delay(5);
      throttle_val[0] = Bluetooth.read();
      if(throttle_val[0]>0){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(turn_val[0]);
        lcd.setCursor(1,1);
        lcd.print(throttle_val[0]);
      drive(throttle_val[0],turn_val[0]);
    }
      else{
      Stop();
    }
}
}
