#include "motorslibrary.h"

Motor::Motor(int pin) {
      void led_off(int pin){ //functions
      digitalWrite(pin,LOW);
    }
    void led_on(int pin){
      digitalWrite(pin,HIGH);
    }
};
