#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoHook;

int counterX = 0;
int counterY = 0;
int lastX = 0;
int lastY = 0;
int button = 3;
int savedposX = 0;
int savedposY = 0;
int savedposHook = 0;
int Xread;
int Yread;
int Hookread;

void setup() {
  // put your setup code here, to run once:
  servoX.attach(9);
  servoY.attach(8);
  servoHook.attach(7);
}

void loop() {
  // put your main code here, to run repeatedly:


  if(analogRead(A1) < 200) {
    counterX += 5;
    servoX.write(counterX);
  }
  delay (50);

  if (analogRead(A1) > 600) {
    counterX -= 5;
    servoX.write(counterX);
  }
  delay (50);

  if (counterX == 180) {
    counterX += 0;
    servoX.write(counterX);
  }
}
