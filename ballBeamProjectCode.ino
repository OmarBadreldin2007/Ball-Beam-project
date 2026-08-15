#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <Servo.h>
#define servoPin 9
#define initangle 43
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo myServo;

// Varibale initialisation
float distance;
int setpoint = 17.5;
float filtereddistance = 17.5;
int readpin = A2;
int readval;
float kp = 1;
float ki = 0.000001;
float kd = 9.5;
float proportional = 0, integral = 0, derivative = 0, derivativeRAW = 0;
float output = 0;
int now = 0, lastTime = 0, dt;
float error = 0, lastError = 0;
// PID function intialisation
float pid(float error);

void setup() {
  // Initialise serial monitor for serial tracking
  Serial.begin(115200);
  // TOF sensor initialisation
  while (!Serial) { delay(1); }
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_DEFAULT);
  Wire.setWireTimeout(3000, true);
  lox.startRange();
  // Servo motor intialisation
  myServo.attach(servoPin);
  myServo.write(initangle);
}

void loop() {
  // Time Tracking
  now = millis();
  dt = now - lastTime;
  // PID loop every 40 milliseconds
  if (dt >= 40) {
    readDistance();
    readval= analogRead(readpin);
    int setpoint = 11 +readval/70;
    Serial.print("setpoint set to: ");
    Serial.println(setpoint);
    error = filtereddistance - setpoint;
    Serial.print("  Distance: ");
    Serial.print(filtereddistance);
    Serial.println(" cm");
    pid(error);
    // Overwrite last error and time
    lastError = error;
    lastTime = now;

    // Constrain servo angle to avoid over actuation
    float angle = initangle + output;
    angle = constrain(angle,10, 175);
    myServo.write(angle);

    Serial.print("  Angle: ");
    Serial.println(angle);
    Serial.print("  output: ");
    Serial.println(output);
  }
}

float pid(float error){
  proportional = kp * error;
  integral += error * dt;
  derivativeRAW = (error - lastError) / dt;
  // Active low pass filter for derivative term to reduce noise
  derivative = 0.65*derivative + 0.45*derivativeRAW;
  output = proportional + ki*integral + kd*derivative;
  return output;
}
// Apply range gate to reject invalid distance measurements
void readDistance(){
  if (lox.isRangeComplete()) {
   float mm = lox.readRangeResult();
    distance = mm / 10.0;
    if (distance < 33 && distance > 6){
      filtereddistance = distance;
    }
    lox.startRange();
  }
}