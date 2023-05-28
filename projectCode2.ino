#include <Arduino.h>
#include <NewPing.h>  // Include the NewPing library

const int trigPin = A0;    // Trig pin of HC-SR04 connected to analog pin 0
const int echoPin = A1;    // Echo pin of HC-SR04 connected to analog pin 1
const int leftMotorForwardPin = 13;
const int leftMotorReversePin = 12;
const int rightMotorForwardPin = 11;
const int rightMotorReversePin = 10;
const int ledPin1 = 6;   // Pin for the first LED

char c;
int distanceThreshold = 20;  // Distance threshold in centimeters

NewPing sonar(trigPin, echoPin, 200);  // Create a NewPing object

void setup() {
  pinMode(leftMotorForwardPin, OUTPUT);
  pinMode(leftMotorReversePin, OUTPUT);
  pinMode(rightMotorForwardPin, OUTPUT);
  pinMode(rightMotorReversePin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, HIGH);  // Turn on the first LED initially
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
  }
 
  if (c == 'F') {       // move forward (all motors rotate in forward direction)
    if (isObstacleDetected()) {
      stopMotors();
    } else {
      digitalWrite(leftMotorForwardPin, HIGH);
      digitalWrite(rightMotorForwardPin, HIGH);
    }
  }
  
  else if (c == 'B') {  // move reverse (all motors rotate in reverse direction)
    stopMotors();
    digitalWrite(leftMotorReversePin, HIGH);
    digitalWrite(rightMotorReversePin, HIGH);
  }
  
  else if (c == 'R') {  // turn right (left side motors rotate in forward direction, right side motors don't rotate)
    stopMotors();
    digitalWrite(leftMotorForwardPin, HIGH);
  }
  
  else if (c == 'L') {  // turn left (right side motors rotate in forward direction, left side motors don't rotate)
    stopMotors();
    digitalWrite(rightMotorForwardPin, HIGH);
  }
  
  else if (c == 'W') {  // turn first LED on
    digitalWrite(ledPin1, LOW);
  }
  
  else if (c == 'w') {  // turn first LED off
    digitalWrite(ledPin1, HIGH);
  }
  
  else if (c == 'S') {  // STOP (all motors stop)
    stopMotors();
  }
  
  delay(100);
}

bool isObstacleDetected() {
  unsigned int duration = sonar.ping_cm();  // Measure the distance in centimeters
  
  if (duration <= 0 || duration > distanceThreshold) {
    return false;
  } else {
    return true;
  }
}

void stopMotors() {
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorReversePin, LOW);
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorReversePin, LOW);
}
