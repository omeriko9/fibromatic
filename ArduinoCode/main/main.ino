//#include <Wire.h>
//#include <Servo.h>
#include <Servo.h>
#include <NeoSWSerial.h>
#include "cmd.h"

Servo s1;
Servo s2;
Servo s3;

int servopin1 = 9;
int servopin2 = 6;
int servopin3 = 5;

int s1pos = 90;
int s2pos = 180;
int s3pos = 180;
int s1posOld = 90;
int s2posOld = 180;
int s3posOld = 180;

int moveDelay = 50;

bool runPlan2 = false;
int plan2Index = 0;

NeoSWSerial  mySer(10,7);
String Data = "";
Cmd c;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Ready");
  
  mySer.begin(19200);

  pinMode(servopin1,OUTPUT);
  pinMode(servopin2,OUTPUT);
  pinMode(servopin3,OUTPUT);
  
  s1.attach(servopin1);
  s2.attach(servopin2);
  s3.attach(servopin3);

  s1pos = s1posOld = c.Get1();
  s2pos = s2posOld = c.Get2();
  s3pos = s3posOld = c.Get3();

  setServoData();
}

void setServoData(int a, int b, int c)
{
  s1posOld = s1pos;
  s2posOld = s2pos;
  s3posOld = s3pos;
  s1pos = a;
  s2pos = b;
  s3pos = c; 

  moveSmoothlyAll();
}

void moveSmoothlySpecific(int oldPos, int newPos, Servo & s){

  if (oldPos==newPos){
    s.write(newPos);
    return;
  }
  for (int i=oldPos; i!=newPos; ){
    s.write(i);     
    delay(10);
    //Serial.println("oldPos: " + String(oldPos) + ", newPos: " + String(newPos) + ", i: " + String(i));
    if (newPos < oldPos) i--; else i++;
  }
  
}

void moveSmoothlyAll()
{
  //Serial.println("S1: oldPos: " + String(s1posOld) + ", newPos: " + String(s1pos));
  moveSmoothlySpecific(s1posOld, s1pos, s1);
  //Serial.println("S2: oldPos: " + String(s2posOld) + ", newPos: " + String(s2pos));
  moveSmoothlySpecific(s2posOld, s2pos, s2);
  //Serial.println("S3: oldPos: " + String(s3posOld) + ", newPos: " + String(s3pos));
  moveSmoothlySpecific(s3posOld, s3pos, s3);
}

void setServoData() 
{
//  Serial.print("Setting servo data: ");
  
  auto pos = c.GetNextPositions();
  moveDelay = c.GetDelay();
  setServoData(pos.s1, pos.s2, pos.s3);
   
 // Serial.println(String(s1pos) +", "+ String(s2pos) + "," + String(s3pos) + ", " + String(moveDelay));
}

void loop() 
{
  setServoData();
  
  while (mySer.available())
  {
      char character = mySer.read(); 
      Data.concat(character); 
      if (character == '\n')
      {
          //Serial.print("Received: ");
          //Serial.println(Data);
  
          c.Parse(Data);
          
          Data = "";
      }
  }

  delay(moveDelay);
}
