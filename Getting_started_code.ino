
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  200 // Minimum pulse length count (for 0 degrees)
#define SERVOMAX  665 // Maximum pulse length count (for 180 degrees)

// Stepper motor pins
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 400;
const int stepsFor90Degrees = stepsPerRevolution / 4;
int stepDelay = 4000;


void setup() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    Serial.begin(9600);
    pwm.begin();
    pwm.setPWMFreq(60);
    
    Serial.println("=== Robot Arm Motor Tester ===");
    Serial.println("Enter 'home' to home robot");
    Serial.println("Enter a number or 'wave':");
    Serial.println(" 0 - Test shoulder (servo 0 and 1 in sync)");
    Serial.println(" 2 - Test elbow");
    Serial.println(" 3 - Test wrist up/down");
    Serial.println(" 4 - Test wrist twist");
    Serial.println(" 5 - Test claw gripper");
    Serial.println(" 7 - Test stepper (base rotation)");
    Serial.println("----------------------------------------");
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input == "wave") {
            robotWave();
        } else if (input == "pickUp") {
            pickUp();
        } else if (input == "home") {
            home();
        } else {
            int motor = input.toInt();
              if (motor == 0) {
                Serial.println("Testing SHOULDER (servo 0 + 1 in sync)...");
                testShoulder();
            } else if (motor >= 2 && motor <= 5) {
                Serial.print("Testing servo ");
                Serial.println(motor);
                testServo(motor);
            } else if (motor == 7) {
                Serial.println("Testing stepper motor...");
                testStepper();
            } else {
                Serial.println("Invalid input. Try 0-5, 7, or 'wave'.");
            }
        }

        while (Serial.available()) {
            Serial.read(); // Clear the serial buffer
        }

        Serial.println("\nReady for next input.");
    }
}

// Shoulder: servos 0 and 1 move together
void testShoulder() {
    setServoPosition(0, 0);
    setServoPosition(1, 135);
    delay(1000);

    setServoPosition(0, 135);
    setServoPosition(1, 0);
    delay(1000);

    setServoPosition(0, 85);
    setServoPosition(1, 50);
    delay(2000);

    setServoPosition(0, 0);
    setServoPosition(1, 135);
    delay(2000);

    setServoPosition(0, 135);
    setServoPosition(1, 0);
    delay(1000);
}

void testServo(int servoNumber) {
    setServoPosition(servoNumber, 0);
    delay(1000);
    setServoPosition(servoNumber, 40);
    delay(1000);
    setServoPosition(servoNumber, 0);
    delay(1000);
    setServoPosition(servoNumber, 40);
    delay(1000);
    setServoPosition(servoNumber, 0);
    delay(1000);
}

void robotWave() {
    Serial.println("Performing wave motion...");

    // Move shoulder to wave position
    baseRotateLeft();
    setServoPosition(0, 85);
    setServoPosition(1, 50);
    delay(1000);

    // Raise elbow
    setServoPosition(2, 0);
    delay(1000);
    setServoPosition(2, 90);
    delay(1000);
    setServoPosition(2, 0);
    delay(1000);
    setServoPosition(4, 0);
    delay(500);
    setServoPosition(4, 180);
    setServoPosition(5, 0);
    delay(500);
    setServoPosition(4, 0);
    setServoPosition(5, 90);
    delay(1000);
    setServoPosition(5, 0);

   /* // Wave wrist (up/down)
    for (int i = 0; i < 3; i++) {
        setServoPosition(3, 60);
        delay(300);
        setServoPosition(3, 120);
        delay(300);
    } */

    // Return to rest position
    baseRotateRight();
    delay(1000);
     // Raise elbow
    setServoPosition(2, 0);
    delay(1000);
    setServoPosition(2, 90);
    delay(1000);
    setServoPosition(2, 0);
    delay(1000);
    setServoPosition(4, 0);
    delay(500);
    setServoPosition(4, 180);
    setServoPosition(5, 0);
    delay(500);
    setServoPosition(4, 0);
    setServoPosition(5, 90);
    delay(1000);
    setServoPosition(5, 0);  

    //baseRotateLeft();
    //delay(1000);

    Serial.println("Wave complete.");
}

void pickUp() {
    setServoPosition(0, 85);
    setServoPosition(1, 50);
    setServoPosition(3, 0);
    delay(1000);
    setServoPosition(5, 45);
    delay(1000);
    setServoPosition(0, 100);
    setServoPosition(1, 35);
    delay(200);
    setServoPosition(0, 110);
    setServoPosition(1, 25);
    delay(500);

    setServoPosition(2, 40);
    delay(100);
    setServoPosition(2, 45);
    delay(100);
    setServoPosition(2, 50);
    delay(100);
    setServoPosition(2, 55);
    delay(100);
    setServoPosition(2, 60);
    delay(100);
    setServoPosition(2, 65);
    delay(100);
    setServoPosition(2, 70);
    delay(100);
    setServoPosition(2, 75);
    delay(100);
    setServoPosition(2, 80);
    delay(100);
    setServoPosition(2, 85);
    delay(100);
    setServoPosition(2, 90);
    delay(100);
    setServoPosition(2, 95);
    delay(100);
    setServoPosition(2, 100);
    delay(1000);

    setServoPosition(5, 0);
    delay(1000);
    setServoPosition(0, 85);
    setServoPosition(1, 50);
    setServoPosition(3, 20);
    setServoPosition(2, 30);
    delay(1000);
    baseRotateLeft();
    delay(500);
    setServoPosition(0, 100);
    setServoPosition(1, 35);
    delay(200);
    setServoPosition(0, 110);
    setServoPosition(1, 25);
    delay(1000);

    setServoPosition(2, 40);
    delay(100);
    setServoPosition(2, 45);
    delay(100);
    setServoPosition(2, 50);
    delay(100);
    setServoPosition(2, 55);
    delay(100);
    setServoPosition(2, 60);
    delay(100);
    setServoPosition(2, 65);
    delay(100);
    setServoPosition(2, 70);
    delay(100);
    setServoPosition(2, 75);
    delay(100);
    setServoPosition(2, 80);
    delay(100);
    setServoPosition(2, 85);
    delay(100);
    setServoPosition(2, 90);
    delay(100);
    setServoPosition(2, 95);
    delay(100);
    setServoPosition(2, 100);
    delay(500);

    setServoPosition(5, 90);
    delay(500);
    setServoPosition(0, 85);
    setServoPosition(1, 50);
    delay(1000);
    setServoPosition(2, 30);
    setServoPosition(3, 20);
    delay(500);
    baseRotateRight();
    delay(1000);
    Serial.println("PickUp complete.");
}

void home() {
  Serial.println("homing...");
    setServoPosition(0, 85);
    setServoPosition(1, 50);
    delay(1000);
    setServoPosition(2, 30);
    setServoPosition(3, 20);
    delay(1000);
  Serial.print("homing complete");
}

void testStepper() {
    baseRotateLeft();
    delay(1000);
    baseRotateRight();
    delay(1000);
}

void baseRotateLeft() {
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < stepsFor90Degrees; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(stepDelay);
    }
    delay(1000);
}

void baseRotateRight() {
    digitalWrite(dirPin, LOW);
    for (int x = 0; x < stepsFor90Degrees; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(stepDelay);
    }
    delay(1000);
}

void setServoPosition(int servoNumber, int degrees) {
    int pulseLength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servoNumber, 0, pulseLength);
}