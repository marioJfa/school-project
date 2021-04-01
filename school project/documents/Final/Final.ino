/*
 * DATA:
 * 
 * 3 = forward
 * 4 = backwards
 * 5 = left
 * 6 = right
 * 7 = spray
 * 8 = Stop
 */



//including essintial libraries

  //For Motors
  #include <MyMotorsLibrary.h>

  //For LCD
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  #include <SoftwareSerial.h>

//end

// important variables
//LCD
//identifying LCD related variables
#define LCD_Address 0x3F
#define LCD_Columns 16
#define LCD_Rows 2
int LCD_status_updated = 0;
//end


//identifying motor system related variables

int Motor_R_Speed  = 5, Motor_R_Dir[] = {6,7}, Motor_L_Speed =9, Motor_L_Dir[] = {10,11};
int turn_Dir;
int turn_Speed = 200; //change to change the turning speed
int throttle_Speed = 240; 
// end


//Data
int DATA;

//end


//LCD inetializiation 
LiquidCrystal_I2C lcd(LCD_Address,LCD_Columns,LCD_Rows);
//end

// Motors inetialization
MyMotorsLibrary Motors(Motor_R_Speed , Motor_R_Dir[0] , Motor_R_Dir[1] , Motor_L_Speed , Motor_L_Dir[0] , Motor_L_Dir[1]);
//end


//identifying essential connection variables

SoftwareSerial Bluetooth(2,3);

//end

void drive(){
  Serial.println("drive");
    if(DATA == 8){
      Motors.Stop();
    }
    else if(DATA == 3){
      Motors.Linear(throttle_Speed,1,0);
    }
    else if(DATA == 4){
      Motors.Linear(throttle_Speed,0,1);
    }
    else if(DATA == 6){
      Motors.Turn_Right(turn_Speed);
    }
    else if(turn_Dir == 5){
      Motors.Turn_Left(turn_Speed);
    }
}

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
  delay(10);
  if(Bluetooth.available()>=2){
      Serial.println("Bluetooth");
      DATA = Bluetooth.read();
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(DATA);
//      drive(throttle_val[0],turn_val);
    }
//      else{
//      Motors.Stop();
//    }
}
