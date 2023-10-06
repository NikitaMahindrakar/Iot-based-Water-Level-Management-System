 /*
 HC-SR04 ultrasonic sensor
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 9 
 Trig to Arduino pin 8
*/
#define echopin 9 // echo pin
#define trigpin 8 // Trigger pin

int maximumRange = 105; // maximum height of tank in cm
long duration;
float v; // volume in cubic cm
float distance; // height of water level in cm
int r = 53.2; // radius of tank in cm
int cap; // capacity in liters
int actual_height; // actual height in cm

void setup() 
{
  Serial.begin (9600);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode (4, OUTPUT);  //Buzzer
  pinMode (6, OUTPUT);  //PUMP control
  pinMode (A0, OUTPUT); //0% indicator
  pinMode (A1, OUTPUT); //25% indicator
  pinMode (A2, OUTPUT); //50% indicator
  pinMode (A3, OUTPUT); //75% indicator
  pinMode (A4, OUTPUT); //100% indicator
  
}
void loop ()
{
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    duration=pulseIn (echopin,HIGH);
    distance= duration/58.2;
    delay(200);
    Serial.print(distance);
    Serial.println("cm");
    /*Serial.print(v);
    Serial.println("cm3,");
    Serial.print(cap);
    Serial.println("liters, ");*/
    actual_height = maximumRange - distance;
    v = ((3.14*(r*r))*(actual_height)); // formula to calculate volume in cubic cm
    cap = v/1000; // final capacity in liters
  
  if (distance <= 100) 
    {
    digitalWrite(A0,HIGH);  // 0% INDICATION
     
      if (distance > 81) //buzzer action
      {
      digitalWrite(4,HIGH); 
      delay(200);           //BUZZER BEEPING
      digitalWrite(4,LOW);
      delay(200);
      }
      else
      {
      digitalWrite(4,LOW);  //BUZZER OFF
      }
    }
    else
    {
    digitalWrite(A0,LOW); 
    }

  if (distance <= 80) // 25% INDICATION
    {
    digitalWrite(A1,HIGH);
    }
    else 
    {
    digitalWrite(A1,LOW);
    }

  if (distance <= 60) // 50% INDICATION
    {
    digitalWrite(A2,HIGH);
    }
    else 
    {
    digitalWrite(A2,LOW);
    }

 if (distance <= 40) // 75% INDICATION
    {
    digitalWrite(A3,HIGH);
    }
    else 
    {
    digitalWrite(A3,LOW);
    }

 if (distance <= 20) // 100% INDICATION
    {
    digitalWrite(A4,HIGH);
    //digitalWrite(6,LOW); //PUMP OFF
    }
    else 
    {
    digitalWrite(A4,LOW);
    }
}
