#include<LiquidCrystal.h>
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2 ;
const int in=8,out=9,buzzer=7;
int temp=0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  
lcd.begin(16,2);
pinMode(in,INPUT);
pinMode(out,INPUT);
pinMode(buzzer, OUTPUT);
lcd.print("Visitor Counter");

}

void loop() {
if(digitalRead(in)==1)
  { 
    temp=temp+1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Counting");
    lcd.setCursor(0,1);
     lcd.print(temp);
     {
      if (temp==30)
      {
        digitalWrite(buzzer, HIGH);
      }
      else
      {
        digitalWrite(buzzer, LOW);
      }
     }
     delay(500);
  }
else if(digitalRead(out)==1)
{
   temp=temp-1;
   lcd.clear();
    lcd.setCursor(0,0);
     lcd.print("Counting");
   lcd.setCursor(0,1);
   lcd.print(temp);
   {
      if (temp==30)
      {
        digitalWrite(buzzer, HIGH);
      }
      else
      {
        digitalWrite(buzzer, LOW);
      }
     }
      delay(500);
}

}
