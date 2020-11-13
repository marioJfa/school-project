int led = 8;

void setup() {
pinMode(led,OUTPUT);
Serial.begin(9600);

}

void loop() {
  int x = Serial.read();
  if(x>0){
    if(x==1)
      digitalWrite(led,HIGH);
  }
  else
    digitalWrite(led,LOW);
}
