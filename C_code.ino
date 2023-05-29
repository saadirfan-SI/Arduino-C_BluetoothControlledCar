#include <stdio.h>
#include <NewPing.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define trigPin 0    // Trig pin of HC-SR04 connected to analog pin 0
#define echoPin 1    // Echo pin of HC-SR04 connected to analog pin 1
#define leftMotorForwardPin 13
#define leftMotorReversePin 12
#define rightMotorForwardPin 11
#define rightMotorReversePin 10
#define ledPin1 6   // Pin for the first LED

char c;
int distanceThreshold = 20;  // Distance threshold in centimeters

NewPing sonar(trigPin, echoPin, 200);  // Create a NewPing object

void pinMode(int pin, int mode) {
    // Implement the pinMode function for the specific microcontroller
}

void digitalWrite(int pin, int value) {
    // Implement the digitalWrite function for the specific microcontroller
}

int digitalRead(int pin) {
    // Implement the digitalRead function for the specific microcontroller
    return 0;
}

void setup() {
    pinMode(leftMotorForwardPin, 1);
    pinMode(leftMotorReversePin, 1);
    pinMode(rightMotorForwardPin, 1);
    pinMode(rightMotorReversePin, 1);
    pinMode(ledPin1, 1);
    digitalWrite(ledPin1, 1);  // Turn on the first LED initially
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
            digitalWrite(leftMotorForwardPin, 1);
            digitalWrite(rightMotorForwardPin, 1);
        }
    }

    else if (c == 'B') {  // move reverse (all motors rotate in reverse direction)
        stopMotors();
        digitalWrite(leftMotorReversePin, 1);
        digitalWrite(rightMotorReversePin, 1);
    }

    else if (c == 'R') {  // turn right (left side motors rotate in forward direction, right side motors don't rotate)
        stopMotors();
        digitalWrite(leftMotorForwardPin, 1);
    }

    else if (c == 'L') {  // turn left (right side motors rotate in forward direction, left side motors don't rotate)
        stopMotors();
        digitalWrite(rightMotorForwardPin, 1);
    }

    else if (c == 'W') {  // turn first LED on
        digitalWrite(ledPin1, 0);
    }

    else if (c == 'w') {  // turn first LED off
        digitalWrite(ledPin1, 1);
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
    digitalWrite(leftMotorForwardPin, 0);
    digitalWrite(leftMotorReversePin, 0);
    digitalWrite(rightMotorForwardPin, 0);
    digitalWrite(rightMotorReversePin, 0);
}

int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
