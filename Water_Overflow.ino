#define BLYNK_PRINT SwSerial
#define TRIGGER 3 
#define ECHO 2 
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11);
#include <BlynkSimpleStream.h> 
BlynkTimer timer;  
char auth[] = "uC-h40-YJ6Ruw-ozLNZ1KemrsoS3NgnT"; 
BLYNK_WRITE(V5) 
{
  int pinValue = param.asInt(); 
}
void sendSensor()
{ 
  long duration, distance; 
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW); 
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  Blynk.virtualWrite(V5, distance); 
}
void setup() 
{ 
   SwSerial.begin(9600); 
   Serial.begin(9600); 
   Blynk.begin(Serial, auth); 
   pinMode(TRIGGER, OUTPUT); 
   pinMode(ECHO, INPUT); 
   timer.setInterval(1000L, sendSensor); 
}
void loop()
{ 
    Blynk.run(); 
    timer.run();
}