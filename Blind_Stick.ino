#define trigPin 10
#define echoPin 13
#define alermPin 6
#include <Wire.h>
#include "MMA7660.h"
MMA7660 acc;
int buzz = 6;
float duration, distance;

void setup()
{   
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(alermPin,OUTPUT);
    pinMode(2,OUTPUT);  
    acc.init();
    pinMode(8, OUTPUT);
    Serial.begin(115200);
}

void loop()
{

    static long cnt     = 0;
    static long cntout  = 0;
    float ax,ay,az;
    int8_t x, y, z;

    acc.getXYZ(&x,&y,&z);

//    Serial.print("x = ");
//    Serial.println(x);
//    Serial.print("y = ");
//    Serial.println(y);
//    Serial.print("z = ");
//    Serial.println(z);
   


    if(acc.getAcceleration(&ax,&ay,&az))
    {
        Serial.print("get data ok: ");
    }
    else
    {
        Serial.print("tiem out: ");
    }
    
    //Serial.println("accleration of X/Y/Z: ");
    Serial.print(ax);
    Serial.println(" g");
//    Serial.print(ay);
//    Serial.println(" g");
//    Serial.print(az);
//    Serial.println(" g");
//    Serial.println();
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);

  distance = (duration/2)*0.0343;

  Serial.print("Distance = ");
  if(distance >= 400 || distance <= 2){
    Serial.println("Out of range");
  }
  else{
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
    if((distance>=2 && distance<=25)||ax<0){
      digitalWrite(alermPin,HIGH);
      }else{
        digitalWrite(alermPin,LOW);
      }
  }   
}


