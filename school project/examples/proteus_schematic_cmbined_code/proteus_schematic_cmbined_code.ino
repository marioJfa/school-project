#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); // define lcd

int lower_threshhold = 55; // define pump values
int PumpPin = 3;
int i = lower_threshhold;
int speeding = 1;

int echoPin = 2; // define ultrasonic sensor values
int trigPin = 4;
long duration;
int distance;

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  pinMode(PumpPin, OUTPUT); // define pump pin mode

  pinMode(trigPin, OUTPUT); // define ultrasonic sensor pin modes
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
    // Print a message to the LCD.
  lcd.setCursor(1,0); // lcd start
  lcd.print("hello world");
  lcd.setCursor(1,1);
  lcd.print("Peace"); // lcd end
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; //speed of sound is 343m/s => 0.034cm/s
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(i==lower_threshhold){// pump start
    analogWrite(PumpPin, i);
    speeding = 1;
    i += 10;
  }
  else if(i==255){
    analogWrite(PumpPin, i);
    speeding = 0;
    i -=10;
  }
  else if(speeding == 1){
    analogWrite(PumpPin, i);
    i += 10;
  }
  else if(speeding == 0){
    analogWrite(PumpPin, i);
    i -= 10;
  }
  for(int i=254; lower_threshhold<i; i--){
    analogWrite(PumpPin, i); // pump end
  }
}
