#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();

}

void loop()
{
    // Print a message to the LCD.
  lcd.setCursor(1,0);
  lcd.print("hello world");
  lcd.setCursor(1,1);
  lcd.print("Peace");
}
