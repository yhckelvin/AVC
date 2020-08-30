#include <LiquidCrystal.h>
const int trigPin=7, echoPin=8 ;
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2 ;
const int buttonPin=6;  //recently added
const int ledPin=13;    //recently added
int counter = 0;
int currentState1 = 0;
int previousState1 = 0;
int currentState2 = 0;
int previousState2 = 0;
int inside = 0;
int outside = 0;
int buttonState=0;      //recently added

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup()
{
 // initialize the LCD
Serial.begin (9600);
lcd.begin(16,2);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(ledPin, OUTPUT);    //recently added
pinMode(buttonPin, INPUT);  //recently added
}

void loop()
{
lcd.setCursor(0, 0);
lcd.print("IN: ");
lcd.setCursor(8, 0);
lcd.print("OUT: ");
lcd.setCursor(0, 1);
lcd.print("Total Inside: ");
long duration, distance;
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (counter >= 30)
{
digitalWrite(ledPin, HIGH); //recently added
delay(300);                //recently added
digitalWrite(ledPin, LOW);  //recently added
lcd.setCursor(0, 1);
lcd.print("exceed limit");
Serial.print("exceed limit");       //added by me
Serial.print(counter);              //added by me
}
if (distance <= 9)      //adjust distance
{
currentState1 = 1;
digitalWrite(ledPin, HIGH); //recently added
delay(100);                //recently added
digitalWrite(ledPin, LOW);  //recently added
}
else 
{
currentState1 = 0;
}
delay(100);
if(currentState1 != previousState1)
{
if(currentState1 == 1)
{
counter = counter + 1;
}
lcd.setCursor(14, 1);
lcd.print(counter);
Serial.print(" : Total Inside");  //added by me
Serial.print(counter);              //added by me
inside = inside +1;
}
lcd.setCursor(4, 0);
lcd.print(inside);
if (distance > 9 && distance <= 18) //added recently
{
currentState2 = 1;
digitalWrite(ledPin, HIGH); //recently added
delay(100);                //recently added
digitalWrite(ledPin, LOW);  //recently added
}
else 
{
currentState2 = 0;
}
delay(100);
if(currentState2 != previousState2)
{
if(currentState2 == 1)
{
counter = counter - 1;
}
lcd.setCursor(14, 1);
lcd.print(counter);
Serial.print(counter);              //added by me
Serial.print(" : Total Inside");  //added by me
outside = outside +1;
}
lcd.setCursor(13, 0);
lcd.print(outside);
lcd.setCursor(14, 1);
lcd.print(counter);
Serial.print(counter);              //added by me
Serial.println(" : Total Inside");  //added by me
//if (counter > 9 || counter < 0)   //deleted by me
if (distance > 9 || distance < 0)    //adjust distance
{
lcd.setCursor(14, 1);
lcd.print(counter);
Serial.print(counter);              //added by me
Serial.println(" : Total Inside");  //added by me
delay(1000);
lcd.clear();
}
}
