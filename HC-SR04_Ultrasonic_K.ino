/**
   ICC. Temperature Module
   I2C for LCD 16x2
   MLX90614 Temperature Sensor, 3.3v
   A4 = SDA
   A5 = SCL
   Hardware Connections:
    Arduino | HC-SR04
    -------------------
      5V    |   VCC
      7     |   Trig
      6     |   Echo
      GND   |   GND
*/
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3 // Declaring LCD Pins
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

// Pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 6;
const int ledPin = 8;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
  mlx.begin();

  //LCD Display Configuration
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH); //Lighting backlight
  lcd.home ();
}

void loop() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  // Print out results
  if ( pulse_width > MAX_DIST ) {
    Serial.println("Out of range");
  } 
  else {
    Serial.print(cm);
    Serial.print(" cm \t");
//    Serial.print(inches);
//    Serial.println(" in");
  if (cm <= 10)
  {
    Serial.println("\t detected");
    Serial.print(mlx.readObjectTempC());
    Serial.println("   C");
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
     lcd.setCursor(0,1);
     lcd.print("Temp   ");
     lcd.print(mlx.readObjectTempC());
     lcd.print(" C");
  }
  else
   Serial.println("\t not detected");
  }

  // Wait at least 60ms before next measurement
  delay(3000);
}
