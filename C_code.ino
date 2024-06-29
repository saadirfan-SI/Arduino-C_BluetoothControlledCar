#include <stdio.h>
#include <NewPing.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Define pins for HC-SR04 ultrasonic sensor
#define trigPin 0    // Trig pin of HC-SR04 connected to analog pin 0
#define echoPin 1    // Echo pin of HC-SR04 connected to analog pin 1

// Define pins for motor control
#define leftMotorForwardPin 13
#define leftMotorReversePin 12
#define rightMotorForwardPin 11
#define rightMotorReversePin 10

// Define pin for LED
#define ledPin1 6   // Pin for the first LED

char c;  // Variable to store received commands
int distanceThreshold = 20;  // Distance threshold in centimeters for obstacle detection

// Create a NewPing object for ultrasonic sensor
NewPing sonar(trigPin, echoPin, 200);

// Function prototypes for Arduino functions
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
    // Initialize motor control pins as output
    pinMode(leftMotorForwardPin, 1);
    pinMode(leftMotorReversePin, 1);
    pinMode(rightMotorForwardPin, 1);
    pinMode(rightMotorReversePin, 1);
    
    // Initialize LED pin as output
    pinMode(ledPin1, 1);
    
    // Turn on the LED initially
    digitalWrite(ledPin1, 1);
    
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);  // Bluetooth module communicates via serial port
}

void loop() {
    // Check if data is available to read from serial port
    if (Serial.available()) {  // Bluetooth module sends data to the serial port
        // Read the incoming byte
        c = Serial.read();  // Read the data sent by the Bluetooth module
        // Print the received character to serial monitor
        Serial.println(c);
    }

    // Control motor and LED based on the received command
    if (c == 'F') {       // Move forward (all motors rotate in forward direction)
        if (isObstacleDetected()) {
            stopMotors();
        } else {
            digitalWrite(leftMotorForwardPin, 1);
            digitalWrite(rightMotorForwardPin, 1);
        }
    } else if (c == 'B') {  // Move reverse (all motors rotate in reverse direction)
        stopMotors();
        digitalWrite(leftMotorReversePin, 1);
        digitalWrite(rightMotorReversePin, 1);
    } else if (c == 'R') {  // Turn right (left side motors rotate in forward direction, right side motors don't rotate)
        stopMotors();
        digitalWrite(leftMotorForwardPin, 1);
    } else if (c == 'L') {  // Turn left (right side motors rotate in forward direction, left side motors don't rotate)
        stopMotors();
        digitalWrite(rightMotorForwardPin, 1);
    } else if (c == 'W') {  // Turn first LED on
        digitalWrite(ledPin1, 0);
    } else if (c == 'w') {  // Turn first LED off
        digitalWrite(ledPin1, 1);
    } else if (c == 'S') {  // STOP (all motors stop)
        stopMotors();
    }

    // Small delay to stabilize loop
    delay(100);
}

bool isObstacleDetected() {
    // Measure the distance in centimeters
    unsigned int duration = sonar.ping_cm();

    // Check if the measured distance is within the threshold
    if (duration <= 0 || duration > distanceThreshold) {
        return false;
    } else {
        return true;
    }
}

void stopMotors() {
    // Stop all motors
    digitalWrite(leftMotorForwardPin, 0);
    digitalWrite(leftMotorReversePin, 0);
    digitalWrite(rightMotorForwardPin, 0);
    digitalWrite(rightMotorReversePin, 0);
}

int main() {
    // Setup the microcontroller
    setup();
    
    // Enter an infinite loop
    while (1) {
        loop();
    }
    
    return 0;
}
