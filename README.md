# Arduino-Digital-Alarm-Clock
This project implements an alarm clock using an Arduino board. The alarm clock allows users to set the time, set an alarm, and disable the alarm with an ultrasonic sensor.  The project demonstrates the integration of hardware components with Arduino programming to create a functional alarm clock system.

## Features
- Set the current time using the buttons and LCD display
- Set an alarm time and enable/disable the alarm
- Display the current time on the LCD screen
- Activate an alarm with sound and visual indication

## Components Required
- Arduino board (e.g., Arduino Uno)
- Ultrasonic sensor (HC-SR04)
- Liquid Crystal Display (LCD) module (16x2)
- Push buttons for menu navigation
- Buzzer for alarm sound
- Resistors, jumper wires, and breadboard for circuit connections

## Installation
- Connect the components as per the circuit diagram.
- Download and install the required libraries: LiquidCrystal_I2C, Time, Ultrasonic
- Open the Arduino IDE.
- Load the AlarmClock.ino sketch.
- Compile and upload the sketch to your Arduino board.

## Usage
- Power up the Arduino board.
- The LCD will display the current time.
- Use the buttons to navigate through the menu options.
- Set the current time, alarm time, and enable/disable the alarm.
- The LCD will provide feedback and indicate the status of the alarm.
- When the alarm time is reached, the buzzer will sound and the LCD will display the alarm message.
- To disable the alarm, place hand over the ultrasonic sensor for at least 2 seconds.
