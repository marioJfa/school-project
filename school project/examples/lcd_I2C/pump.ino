int lower_threshhold = 50;
int PumpPin = 8;
void setup() {
  pinMode(PumpPin, OUTPUT);

}

void loop() {
  for(int i=lower_threshhold;i<255; i++){
    analogWrite(PumpPin, i);
  }
  for(int i=254; lower_threshhold<i; i--){
    analogWrite(PumpPin, i);
  }
}
