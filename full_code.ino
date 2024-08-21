

// import library for bluetooth
#include <SoftwareSerial.h>
SoftwareSerial EEBlue(A0, A1);  // RX | TX


// set motor driver pins
  // Left motor pins
  const byte A_PWM = 6;
  const byte A_IN1 = 7;
  const byte A_IN2 = 8;

  // Right motor pins
  const byte B_PWM = 11;
  const byte B_IN1 = 10;
  const byte B_IN2 = 9;


void setup() {

  // Setup commands for enabling serial monitor and bluetooth module
    Serial.begin(9600);  // Begin communication to Serial monitor
    EEBlue.begin(9600);  // Begin communication to Bluetooth module
    Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");

  //Setup motor driver
    // Left motor setup
    pinMode(A_PWM, OUTPUT);
    pinMode(A_IN1, OUTPUT);
    pinMode(A_IN2, OUTPUT);

    // Right motor setup
    pinMode(B_PWM, OUTPUT);
    pinMode(B_IN1, OUTPUT);
    pinMode(B_IN2, OUTPUT);
}

void loop() {

  if (EEBlue.available()) {
    char received_data = EEBlue.read();
    Serial.write(received_data);

    switch (received_data) {
      case 'F':  // Forward
        motor(100, 100);
        break;

      case 'L':  // Left
        motor(-100, 100);
        break;

      case 'R':  // Right
        motor(100, -100);
        break;

      case 'B':  // Back
        motor(-100, -100);
        break;

      case 'S':  // Stop
        motor(0, 0);
        break;

      default:  // Else do nothing 
        break;
    }
  }
}

// Function to run motors based on speed
void motor(int leftSpeed, int rightSpeed) {

  // Left Motor
  if (leftSpeed < 0) {
    analogWrite(A_PWM, abs(leftSpeed));
    digitalWrite(A_IN1, LOW);
    digitalWrite(A_IN2, HIGH);
  } else {
    analogWrite(A_PWM, abs(leftSpeed));
    digitalWrite(A_IN1, HIGH);
    digitalWrite(A_IN2, LOW);
  }


  // Right Motor
  if (rightSpeed < 0) {
    analogWrite(B_PWM, abs(rightSpeed));
    digitalWrite(B_IN1, HIGH);
    digitalWrite(B_IN2, LOW);
  } else {
    analogWrite(B_PWM, abs(rightSpeed));
    digitalWrite(B_IN1, LOW);
    digitalWrite(B_IN2, HIGH);
  }

}