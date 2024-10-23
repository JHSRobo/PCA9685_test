#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define FREQUENCY 50

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
  pwm.setExtClk(25000000); // Set the external clock frequency (25 Mhz)
  // Initializes the ESCs
  for(int n = 0; n < 12; n+=1){
    pwm.writeMicroseconds(n, 1500);
    delay(500);
  }
  delay(2000);
}

void loop() {
  // Go from rest (1500) to full reverse load (1100)
  for(int i = 1500; i >= 1100; i-=100){
    sendPWM(i);
  }
  // Go from full reverse load (1100) to full forward load (1900)
  for(int i = 1100; i <= 1900; i+=100){
    sendPWM(i);
  }
  // Go from full forward load (1900) to rest (1500)
  for(int i = 1900; i >= 1500; i-=100){
    sendPWM(i);
  }
}

void sendPWM(int pwmValue){
  // for loop is used for writing PWM to all 12 channels on the board
  for (int n = 0; n < 12; n++){
    pwm.writeMicroseconds(n, pwmValue);
  }
  Serial.println(pwmValue);
  delay(2000);
}
