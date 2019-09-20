#include <Servo.h>
Servo S;

//define inputs
#define LS A2
#define MS A1
#define RS A0
#define R A3
#define L A4
#define echoPin 11

//define outputs
#define enL 3
#define LMA 7
#define LMB 8
#define enR 6
#define RMA 2
#define RMB 4
#define trigPin 12

void setup()
{
  // put your setup code here, to run once:
  pinMode(LS,INPUT);
  pinMode(MS,INPUT);
  pinMode(RS,INPUT);


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  S.attach(13);
  S.write(0);
 
  pinMode(enL,OUTPUT);
  pinMode(LMA,OUTPUT);
  pinMode(LMB,OUTPUT);
  pinMode(enR,OUTPUT);
  pinMode(RMA,OUTPUT);
  pinMode(RMB,OUTPUT);

  /*analogWrite(enL, 200);
  analogWrite(enR, 200);*/
 
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

void reverse()
{
   digitalWrite(LMA, LOW);
   digitalWrite(LMB, HIGH);
   digitalWrite(RMA, LOW);
   digitalWrite(RMB, HIGH);
   
   Serial.println("reverse");
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
int box=0;
int Dmin=6;
int Dmax=12;

int FindDistance()
{ //USING aULTRASONIC SENSOR
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
  return distance;
   
}
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

char prev;
int allWhite()
{
  return digitalRead(L) && digitalRead(LS) && digitalRead(MS) && digitalRead(RS) && digitalRead(R);
}

void reacquire()
{
  switch(prev)
  {
    case 'R': do
              {
                turnLeft();
                delay(50);
                halt();
                delay(50);
              }
              while(allWhite());
              Serial.println("reacquire");
              break;
              
    case 'L': do
              {
                turnRight();
                delay(50);
                halt();
                delay(50);
              }
              while(allWhite());
              Serial.println("reacquire");
              break;
  }
  delay(100);
}

//digitalRead() returns true when IR sensor detects white line

void loop() {
  
  if((FindDistance()>=Dmin&&FindDistance()<=Dmax)&&box==false)
  {
      halt();
      delay(500);
      grab();
      box=true;
  }
  else if ((FindDistance()<Dmin)&&box==false)
  {
    do
    {
       reverse();
       delay(50);
       halt();
    }while(!(FindDistance()<Dmin));
  }
  else if (digitalRead(LS) && !digitalRead(MS) && digitalRead(RS))
    {forward(); prev='F';}
  else if (digitalRead(LS) && (!digitalRead(RS) || !(digitalRead(R))))
    {turnRight(); prev='R';}
  else if ((!digitalRead(LS) || !digitalRead(L))&& digitalRead(RS))
    {turnLeft(); prev='L';}
  else if (!digitalRead(LS) && digitalRead(MS) && !digitalRead(RS))
    {
      halt();
      drop();
    }
  else if(allWhite())
   {
    reacquire();
   }
  else
    {
      halt();
      grab();
      delay(500);
      do
        {
          sharpRight();
          prev='R';
        } while (!(digitalRead(LS)==digitalRead(MS)==digitalRead(RS)));
    }
 
  delay(50);
  halt();
  delay(50);
}
