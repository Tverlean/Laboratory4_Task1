//Conditions:
//FOR PHOTORESISTOR:
//When the intensity of light is greater than 500
  //the bulb lights up
  //the RGB turns green
//When the intensity of light is less than 500
  //the bulb turns off
  //the RGB turns red
  //"Good Morning!" will appear on the serial monitor.
//FOR IR SENSOR AND REMOTE:
//When number "1" press on the remote,
  //the servo motor place on 0 degrees, 
  //the RGB turns Red, 
  //and "Close" will appear on the LCD together with the "Windows Status."
//when number "2" press on the remote, 
  //the servo motor place on 90 degrees, 
  //the RGB turns Blue, 
  //and "Half Open" will appear on the LCD together with the "Windows Status."
//when number "3" press on the remote, 
  //the servo motor place on 180 degrees, 
  //the RGB turns Green, 
  //and "Widely Open" will appear on the LCD together with the "Windows Status."
//FOR PIR:
  //When the PIR value is "0", the servomotors for door will rotate 180 degree.
  //When the PIR value is "1", nothings happen with the servomotors for door.

#include<Servo.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2);
int IRpin=3;
IRrecv IR(IRpin);
int redLight=11,blueLight=10,greenLight=9,relayPin=8,readPin=A3;
int t=1500;
int pirPin=4;
int pirVal;
int servoPin=5,servoPin2=6,servoPin3=2,servoPin4=13;
Servo servoA;
Servo servoB;
Servo servoC;
Servo servoD;
float angleVala,angleValb;
unsigned long fromStartms; //millis from start
unsigned long prevms; //millis previous read
unsigned long interval=1000;

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
Serial.begin(9600);
pinMode(IRpin,INPUT);
pinMode(redLight,OUTPUT);
pinMode(blueLight,OUTPUT);
pinMode(greenLight,OUTPUT);
IR.enableIRIn();
pinMode(pirPin,INPUT);
pinMode(relayPin,OUTPUT);
pinMode(readPin,INPUT);
pinMode(servoPin,OUTPUT);
servoA.attach(servoPin);
pinMode(servoPin2,OUTPUT);
servoB.attach(servoPin2);
pinMode(servoPin3,OUTPUT);
servoC.attach(servoPin3);
pinMode(servoPin4,OUTPUT);
servoD.attach(servoPin4);
Serial.begin(9600);
}

void loop()   
{
fromStartms=millis();
pirVal=digitalRead(pirPin);
if(fromStartms - prevms >= interval)
{
prevms = fromStartms;
    
if(pirVal==1)
{
  servoC.write(180);
  servoD.write(180);
  }
  else
  {
  servoC.write(0);
  servoD.write(0);
  }
  Serial.println(pirVal);
 { 
int readVal= analogRead(readPin);
delay(t);

if (readVal>500)
{
digitalWrite(redLight,HIGH);
digitalWrite(greenLight,LOW);
digitalWrite(relayPin,LOW);

Serial.println("Good Morning!");
}
else
{
digitalWrite(redLight,LOW);
digitalWrite(greenLight,HIGH);
digitalWrite(relayPin,HIGH);
  
lcd.setCursor(0,0);
lcd.print("Windows Status:");
while(IR.decode())
{

  if(IR.decodedIRData.decodedRawData==0xFF00BF00)
  {
   analogWrite(redLight,0);
   analogWrite(greenLight,0);
   analogWrite(blueLight,0);
   Serial.println("POWER");
   lcd.clear();
  }
  if(IR.decodedIRData.decodedRawData==0xEF10BF00)
  {
   Serial.println(1);
   analogWrite(redLight,255);
   analogWrite(greenLight,0);
   analogWrite(blueLight,0);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Windows Status:");
   lcd.setCursor(0,1);
   lcd.print("Close");
   servoA.write(0);
   servoB.write(0);
   
  }
  if(IR.decodedIRData.decodedRawData==0xEE11BF00)
  {
   Serial.println(2);
   analogWrite(redLight,0);
   analogWrite(greenLight,0);
   analogWrite(blueLight,255);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Windows Status:");
   lcd.setCursor(0,1);
   lcd.print("Half Open");
   servoA.write(90);
   servoB.write(90);
  }
  if(IR.decodedIRData.decodedRawData==0xED12BF00)
  {
   Serial.println(3);
   analogWrite(redLight,0);
   analogWrite(greenLight,255);
   analogWrite(blueLight,0);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Windows Status:");
   lcd.setCursor(0,1);
   lcd.print("Widely open");
   servoA.write(180);
   servoB.write(180);
  }
IR.resume();
}
}
}
}
}
