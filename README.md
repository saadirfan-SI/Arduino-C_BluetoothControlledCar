# Arduino_BluetoothControlledCar

This Arduino sketch controls a car, that was built, using inputs from the serial monitor. It utilizes the HC-SR04 ultrasonic sensor to detect obstacles and controls the movement of motors accordingly. The robot can move forward, backward, turn left, turn right, and control an LED.

## Prerequisites

- Arduino board
- HC-SR04 ultrasonic sensor
- Motors and motor driver circuit
- LED and appropriate resistor

## Hardware Setup

1. Connect the Trig pin of the HC-SR04 sensor to analog pin A0 of the Arduino.
2. Connect the Echo pin of the HC-SR04 sensor to analog pin A1 of the Arduino.
3. Connect the motor driver circuit to the appropriate digital pins of the Arduino as follows:
   - Left motor forward pin: 13
   - Left motor reverse pin: 12
   - Right motor forward pin: 11
   - Right motor reverse pin: 10
4. Connect the LED to pin 6 of the Arduino.

## Software Setup

1. Install the Arduino IDE (Integrated Development Environment) from the Arduino website (https://www.arduino.cc/en/software).
2. Open the Arduino IDE and create a new sketch.
3. Copy and paste the code from `robot_control.ino` into the sketch.
4. Go to `Tools > Board` and select the appropriate Arduino board.
5. Go to `Tools > Port` and select the port to which the Arduino board is connected.
6. Click the "Upload" button to compile and upload the code to the Arduino board.

## Usage

1. Open the serial monitor in the Arduino IDE (or any other serial communication software) at a baud rate of 9600.
2. Send the following commands to control the robot:
   - `F`: Move forward (all motors rotate in the forward direction).
   - `B`: Move backward (all motors rotate in the reverse direction).
   - `R`: Turn right (left side motors rotate in the forward direction, right side motors don't rotate).
   - `L`: Turn left (right side motors rotate in the forward direction, left side motors don't rotate).
   - `W`: Turn the first LED on.
   - `w`: Turn the first LED off.
   - `S`: Stop (all motors stop).
3. The robot will continuously read inputs from the serial monitor and perform the corresponding actions.
