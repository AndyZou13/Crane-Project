#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoHook;

int counterX = 0;
int counterY = 0;
const int XJoy = 0;
const int YJoy = 1; 
const int HookJoy = 2;
const int button = 3;
int Xread;
int Yread;



void setup() {
 servoX.attach(9);
 servoY.attach(8);
 servoHook.attach(7);
 
}

void loop() {
  Xread = analogRead(XJoy);
  Xread = map(Xread, 0, 1023, 0, 10);
  if (Xread >= 0){
    counterX + Xread;
  }
  else (Xread == 180);{
    counterX = counterX;
  }
  servoX.write(counterX);
  
  Yread = analogRead(YJoy);
  Yread = map(Yread, 0, 1023, 0, 89);
  servoY.write(counterY);
  if (Yread >= 0){
    counterY + Yread;
  }
  else (Yread == 89);{
    counterY = counterY;
  }
  servoX.write(counterX);
}
