#include <Servo.h>
Servo S;

//define inputs
#define LS A0
#define MS A1
#define RS A2
//#define echoPin

//define outputs
#define enL 
#define LMA 
#define LMB 
#define enR 
#define RMA 
#define RMB 
//#define trigPin

void setup() 
{
  // put your setup code here, to run once:
  pinMode(LS,INPUT);
  pinMode(MS,INPUT);
  pinMode(RS,INPUT);

  /*
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  */
 
  S.attach(1);
  S.write(0);
  
  pinMode(enL,OUTPUT);
  pinMode(LMA,OUTPUT);
  pinMode(LMB,OUTPUT);
  pinMode(enR,OUTPUT);
  pinMode(RMA,OUTPUT);
  pinMode(RMB,OUTPUT);

  analogWrite(enL, 200);
  analogWrite(enR, 200);
  
  Serial.begin(9600);
}


void forward()
{
   digitalWrite(LMA, HIGH);
   digitalWrite(LMB, LOW);
   digitalWrite(RMA, HIGH);
   digitalWrite(RMB, LOW);
   
   Serial.println("forward");
}

void turnLeft()
{
  
  digitalWrite(LMA, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMA, HIGH);
  digitalWrite(RMB, LOW);
  
  Serial.println("left");
}

void turnRight()
{
   digitalWrite(LMA, HIGH);
   digitalWrite(LMB, LOW);
   digitalWrite(RMA, LOW);
   digitalWrite(RMB, LOW);
   
   Serial.println("right");
}

void sharpRight()
{
   digitalWrite(LMA, HIGH);
   digitalWrite(LMB, LOW);
   digitalWrite(RMA, LOW);
   digitalWrite(RMB, HIGH);
   
   Serial.println("sharp right");
}

void halt()
{
  digitalWrite(LMA, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMA, LOW);
  digitalWrite(RMB, LOW);
  
  Serial.println("halt"); 
}

long duration;
int distance;
int angle=0;
int val;

void drop()
{
  delay(100);
  for (; angle>=0; )
  {
    angle=angle-15;
    S.write(angle);
    val=S.read();
    Serial.println(val);
    delay(100);
  }
  
  Serial.println("drop");
}

void grab()
{
  delay(100);
  while(angle<=180)
  {
     angle=angle+15;
     S.write(angle);
     val=S.read();
     Serial.println(val);
     delay(100);
  }
  
  Serial.println("grab");
  
}

//digitalRead() returns true when IR sensor detects white line

void loop() {

  /* USING ULTRASONIC SENSOR 

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
   */
   
  if (digitalRead(LS) && !digitalRead(MS) && digitalRead(RS)) 
    forward();
  else if (digitalRead(LS) && !digitalRead(RS)) 
    turnRight();
  else if (!digitalRead(LS) && digitalRead(RS)) 
    turnLeft();
  else if (!digitalRead(LS) && digitalRead(MS) && !digitalRead(RS))
    {
      halt();
      drop();
    }
  else 
    {
      halt();
      grab();
      do
        {
          sharpRight();
        } while (!(digitalRead(LS)==digitalRead(MS)==digitalRead(RS)));
    }
  
  delay(100);
}
