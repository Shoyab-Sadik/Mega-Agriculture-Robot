#include <SoftwareSerial.h>
#include<Servo.h>
Servo servo;
SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd (0x27, 16, 2);
#include<DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define pump A3
#define buzz A6
#define soil A7

String command;
char c;

float duration;
float distance;

int servo_pin = 5;
int trig = 3;
int echo = 4;
int solar_power = 13;
int red = A0;
int green = A1;
int blue = A2;

int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;

void setup()
{
  pinMode(soil, INPUT);
  pinMode(echo, INPUT);
  pinMode(solar_power, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(red, HIGH);
  digitalWrite(pump, HIGH);

  dht.begin();
  servo.attach(servo_pin);
  servo.write(0);
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(1000);
  Serial.println("Starting the programme-\nby- M. Shoyab Sadik\nCell:01575317604; 01977662117\nPico Robotics & MSS ElectroTech");
  lcd.begin();
  welcome();
  delay(3000);
  start();
  delay(3000);
}

void loop()
{
  if(BTSerial.available())
  {
    command = BTSerial.readStringUntil('\n'); // Read a character
    //Serial.write(command); // write on serial monitor
  }
  if (Serial.available()) 
  {
    char c = Serial.read();   // Read a character
    BTSerial.write(c);        // Send it to HC-05

    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(buzz, HIGH);
    delay(250);
    digitalWrite(buzz, LOW);
    delay(250);
    digitalWrite(buzz, HIGH);
    delay(250);
    digitalWrite(buzz, LOW);
    delay(250);
  }

  lcd.begin();

  int solar_val = digitalRead(solar_power);
  int soil_read = analogRead(soil);
  Serial.println("Soil -");
  Serial.print(soil_read);

  int soil_value = map(soil_read, 1023, 0, 0, 100);
  int solar = solar_val*100;

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if(soil_value > 5 && soil_value < 50)
  {
    digitalWrite(pump, LOW); //pump on (BC 557)
    soil_buzzer();
  }
  /*else
  {
    digitalWrite(pump, HIGH); //pump off
  }*/

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Temp- "); lcd.print(temp); lcd.print(char(223)); lcd.print("C");
  lcd.setCursor(0,1); lcd.print("Humidity- "); lcd.print(humi); lcd.print("%");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Soil - "); lcd.print(soil_value); lcd.print("%");

  if(command == "Data")
  {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      BTSerial.print("Humidity: ");
      BTSerial.print(h);
      BTSerial.print("%");
      BTSerial.println("Temperature: ");
      BTSerial.print(t);
      BTSerial.print("°C");
      BTSerial.println("Soil Moisture: ");
      BTSerial.print(soil_value);
      BTSerial.print("Solar Power: ");
      BTSerial.print(solar);
      BTSerial.print("W");
  }

  if(c == 'F')
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  if(c == 'B')
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  if(c == 'L')
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  if(c == 'R')
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  if(c == 'S')
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    servo.write(0);
  }
  if(c == 'A')
  {
    digitalWrite(trig, LOW);
    delay(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration / 58.82;
    Serial.println("Distance - ");
    Serial.print(distance);

    if(distance <= 25)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite(buzz, HIGH);
    digitalWrite(red, HIGH);
  }
    else
    {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    digitalWrite(red, LOW);
    digitalWrite(buzz, LOW);
    }
  }
  if(c == 'C')
  {
    servo.write(90);
  }
  else
  {
    servo.write(0);
  }
}

void buzzer_sound()
{
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
      delay(500);
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
      delay(500);
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
      delay(500);
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
}

void soil_buzzer()
{
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
      delay(100);
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
      delay(100);
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
}

void welcome()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to -");
  delay(600);
  lcd.setCursor(0,1);
  lcd.print("Digital Agriculture");
}

void start()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Exploring");
  lcd.setCursor(1,1);
  lcd.print("Digital Agriculture");
  lcd.setCursor(3,3);
  lcd.print("with > Jihad");
}


/*void soil_wet()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("The Soil is Wet!");
  lcd.setCursor(0,1);
  lcd.print("No need to Watering");
  lcd.setCursor(0,2);
  lcd.print("Pump is Off");
}

void soil_pump()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("There is some-");
  lcd.setCursor(0,1);
  lcd.print("Moisture in Soil!");
  lcd.setCursor(0,2);
  lcd.print("You Can Water!");
  lcd.setCursor(0,3);
  lcd.print("Pump is Off");
}

void soil_dry()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("The Soil is Dry!");
  lcd.setCursor(0,1);
  lcd.print("Watering by Pump");
  lcd.setCursor(0,2);
  lcd.print("Automatically!");
  lcd.setCursor(0,3);
  lcd.print("Pump is On!");
}*/









/*

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05

void setup() {
  Serial.begin(9600);   // Serial monitor
  BTSerial.begin(9600); // HC-05
}

void loop() {
  // Check if there's data from the Bluetooth module
  if (BTSerial.available()) {
    String message = BTSerial.readStringUntil('\n'); // Read until newline
    Serial.print("Received: ");
    Serial.println(message);
    // Process the message as needed
    // e.g., send an SMS, toggle a pin, etc.
  }

  // Check if there's data from Serial Monitor
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    BTSerial.println(message); // Send it to the HC-05
  }
}
*/
