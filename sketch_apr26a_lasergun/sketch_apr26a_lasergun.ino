#include <Servo.h>

Servo servo;
int angle = 10;
const int led = 3;
const int buzzer = 4;
const int trigPin = 9;
const int echoPin = 10;
float duration, distance;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(6);
  servo.write(angle);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led, HIGH); 

  for (angle = 10; angle <= 180; angle += 5) 
  { 
    digitalWrite(led, HIGH);
    servo.write(angle);
    if (searching()) 
    { 
      gunshot();
     
    }
  }

  for (angle = 180; angle >= 10; angle -= 5) 
  { 
    digitalWrite(led, HIGH);
    servo.write(angle);
    if (searching()) 
    { 
      gunshot();
    }
  }
}


bool searching() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance > 0 && distance < 20) 
  {
    Serial.print("Target at ");
    Serial.print(distance);
    Serial.println(" cm!");
    return true;
  }
  return false;
}

void gunshot() 
{
  for (int i = 0; i < 10; i++) 
  { 
    digitalWrite(led, HIGH);
    tone(buzzer, 1500, 30); 
    delay(30);
    digitalWrite(led, LOW);
    noTone(buzzer);
    delay(30);

    digitalWrite(led, HIGH);
    tone(buzzer, 800, 100);
    delay(100);
    digitalWrite(led, LOW);
    noTone(buzzer);
    delay(50);
  }
}
