void setup()
    {
     pinMode(3,INPUT);
     Serial.begin(9600);
    }
    void loop()
    {
    int x =digitalRead(3);
//     if(x==1)
//     {
//      Serial.println("recv");
//     }
// 
//
//     else if(x==0){
//      Serial.println("not recv");
//     }
      Serial.print(x);
    }
