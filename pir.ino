/*
PIR HCSR501 
modified on 5 Feb 2019
by Saeed Hosseini @ ElectroPeak
https://electropeak.com/learn/guides/
*/
int ledPin = 7;                // LED 
int pirPin = 2;                 // PIR Out pin 
int pirStat = 0;                   // PIR status
void setup() {
 pinMode(ledPin, OUTPUT);     
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
 
}
void loop()
{
 pirStat = digitalRead(pirPin);
    delay(2000);
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println("Hey I got you!!!");
 } 
 else {
   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
 }
 delay(1000);
} 