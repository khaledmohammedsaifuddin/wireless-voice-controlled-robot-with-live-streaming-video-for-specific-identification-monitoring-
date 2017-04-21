
//int duration1,distance1,duration2,distance2;
#include <BitVoicer11.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define tempin A0
#define smokepin A1
//#define trigpin1 42
//#define trigpin2 44
//#define echopin1 43
//#define echopin2 45
#define ONE_WIRE_BUS6 6

#define headlight_h1 34
#define headlight_h2 35
#define headlight_h3 36
#define headlight_h4 37
#define leftlight_h 40
#define rightlight_h 24
#define leftMotor_inputC  30  //any digital pin
#define leftMotor_inputD  28  //any digital pin

#define rightMotor_inputA 52  //any digital pin
#define rightMotor_inputB 50  //any digital pin

#define leftMotor_enableB  5 //Use for PWM Pn
#define rightMotor_enableA  2 //Use for PWM Pin
OneWire oneWire6(ONE_WIRE_BUS6); 
DallasTemperature sensors6(&oneWire6);

BitVoicerSerial bvSerial = BitVoicerSerial();
//Stores the data type retrieved by getData()
byte dataType = 0;
//Stores the state of pin 4
byte pinVal1 = 0;

byte pinVal2 = 0;

void setup ()
{

Serial.begin(9600);
  sensors6.begin();
 

pinMode(smokepin,INPUT);

  //setup for Motor Input and Speed Control

  pinMode (rightMotor_inputA, OUTPUT);
  pinMode (rightMotor_inputB, OUTPUT);
  
  pinMode (leftMotor_inputC, OUTPUT);
  pinMode (leftMotor_inputD, OUTPUT);
  
  //PWM OUTPUT
  pinMode (rightMotor_enableA, OUTPUT);
  pinMode (leftMotor_enableB, OUTPUT);

//pinMode(trigpin1,OUTPUT);
//pinMode(trigpin2,OUTPUT);

//pinMode(echopin1,INPUT);
//pinMode(echopin2,INPUT);  

}


void Forward ()
{
  //Left Motor Forward 
  digitalWrite (leftMotor_inputC, HIGH);
  digitalWrite (leftMotor_inputD, LOW);

  //Right Motor Forward
  digitalWrite (rightMotor_inputA, HIGH);
  digitalWrite (rightMotor_inputB, LOW);

  digitalWrite(leftlight_h,LOW);
  digitalWrite(rightlight_h,LOW);
  
   
  analogWrite (rightMotor_enableA,255);
  analogWrite (leftMotor_enableB,255);

}
void Backward ()
{
  //Left Motor Forward 
  digitalWrite (leftMotor_inputC, LOW);
  digitalWrite (leftMotor_inputD, HIGH);

  //Right Motor Forward
  digitalWrite (rightMotor_inputA, LOW);
  digitalWrite (rightMotor_inputB, HIGH);
   
  analogWrite (rightMotor_enableA,255);
  analogWrite (leftMotor_enableB,255);

}

void leftTurn ()
{
 //Left Motor Backward 
  digitalWrite (leftMotor_inputC, HIGH);
  digitalWrite (leftMotor_inputD, LOW);
  
  //Right Motor Forward
  digitalWrite (rightMotor_inputA, LOW);
  digitalWrite (rightMotor_inputB, LOW);

  digitalWrite (leftlight_h,HIGH);
  
  digitalWrite (rightlight_h,LOW);

  analogWrite (rightMotor_enableA,60);
  analogWrite (leftMotor_enableB,60 );
  
  delay (300);// sec need to turn Left

}

void rightTurn ()
{
   //Left Motor Forward 
  digitalWrite (leftMotor_inputC, LOW);
  digitalWrite (leftMotor_inputD, LOW);

  //Right Motor Backward
  digitalWrite (rightMotor_inputA, HIGH);
  digitalWrite (rightMotor_inputB, LOW);
  
    digitalWrite (rightlight_h,HIGH);
      digitalWrite (leftlight_h,LOW);


  analogWrite (rightMotor_enableA,60);
  analogWrite (leftMotor_enableB,60);
  
  delay (300);// sec need to turn Right
  
}
void head_light_on()
{

  digitalWrite (headlight_h1,HIGH);
    digitalWrite (headlight_h2,HIGH);
      digitalWrite (headlight_h3,HIGH);
        digitalWrite (headlight_h4,HIGH);
}

void head_light_off()
{

  digitalWrite (headlight_h1,LOW);
  digitalWrite (headlight_h2,LOW);
  digitalWrite (headlight_h3,LOW);
  digitalWrite (headlight_h4,LOW);
}

void motorStop ()
{
  
  //Left Motor Stop
  digitalWrite (leftMotor_enableB, LOW);
  
  //Right Motor Stop
  digitalWrite (rightMotor_enableA, LOW);
  digitalWrite(leftlight_h,LOW);
  digitalWrite(rightlight_h,LOW);
  //digitalWrite(trigpin1,LOW);
  
  //digitalWrite(trigpin2,LOW);
 // digitalWrite(trigpin3,LOW);
  //digitalWrite(echopin1,LOW);
 //digitalWrite(echopin2,LOW);
  //digitalWrite(echopin3,LOW);

  delay (1000);
}


void loop ()

{

 int a;
 a=analogRead(smokepin);
   if(a>=350)
   {
    Serial.print("\n");
   Serial.print("smoke detected");
   }
  delay(300);
sensors6.requestTemperatures(); // Send the command to get temperatures
  e=sensors6.getTempCByIndex(0);

 Serial.print(e);
 
Serial.print("\n");
Serial.print(" degrees Celsius, ");
Serial.print((e * 9)/5 + 32);
Serial.println(" degrees Fahrenheit");
delay(300);
  
    //digitalWrite( trigpin1,HIGH);
//delayMicroseconds(1000);
//digitalWrite( trigpin1,LOW);
//duration1=pulseIn(echopin1,HIGH);
//distance1=(duration1/2)/29.1;

//digitalWrite( trigpin2,HIGH);
//delayMicroseconds(1000);
//digitalWrite( trigpin2,LOW);
//duration2=pulseIn(echopin2,HIGH);
//distance2=(duration2/2)/29.1;

  serialEvent();

 
}


void serialEvent()
{
  
 
  
//if(distance2<=10)
//Forward();

//if(distance1<=10)
//{
 // Backward();
//}


 
//Reads the serial buffer and stores the received data type
dataType = bvSerial.getData();
//Checks if the data type is the same as the one in the
//Voice Schema
if (dataType == BV_BYTE)
{
//Checks the stored value in byteData by getData() and
//changes the value of the pin
if (bvSerial.byteData == 0)
{Forward();
}
if (bvSerial.byteData == 1)
motorStop();

if (bvSerial.byteData == 2)
leftTurn();
if (bvSerial.byteData == 3)
rightTurn();
if (bvSerial.byteData == 4)
{Backward();
}
if (bvSerial.byteData == 5)
head_light_on();
if (bvSerial.byteData == 6)
head_light_off();

}
}
