int led = 8;

void setup() {
pinMode(led,OUTPUT);
Serial.begin(9600);

}

void loop() {
  int x = Serial.read();
  while(x>0){
    if(x==1)
      digitalWrite(led,HIGH);
  }
    digitalWrite(led,LOW);
}
