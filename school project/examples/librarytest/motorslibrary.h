#ifndef tl
#define tl

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
class Motor {
  public: // use anywhere
    Motor(int pin); // constructor
    void led_off(int pin){ //functions
      digitalWrite(pin,LOW);
    }
    void led_on(int pin){
      digitalWrite(pin,HIGH);
    }
  private:
};

#endif
