/*
 * This code is used to control a wooden crane that uses 3 servo motors, 2 joysticks, and the integrated, non volitile memory
 * The joystick inputs values like a variable resistor. Once the values are read, they will determine wether to add or subtract from a counter that controls the servo motors.
 * The integrated memory is use to remember the previous position so that the crane will not spontaneously spin out of place, preventing accidents.
 * The button on the joystick is also used as a position saver. Once the button is clicked, the current position will be saved and any time the button is pressed, the crane
 * will return to the save position slowly.
 */


#include <Servo.h> //includes Servo library into the useable code
#include <EEPROM.h> //includes EEPROM library into the useable code

Servo servoX; //Setting up the servo motors
Servo servoY;
Servo servoHook;

int counterX = 90; //setting up variables and link them up to intergers
int counterY = 45;
int counterHook = 90;
const int btn = 2; 
int lastbtnState = 1;
int btnState = 0;
int saveX = 0;
int saveY = 0;
int saveHook = 0;
int btncounter = 0;
int eepromX = 0; //setting up the EEPROM variables
int eepromY = 1;
int eepromHook = 2;
byte value; //reading from the first byte of EEPROM (non volitile integrated memory)

void setup() {
  counterX = EEPROM.read(eepromX); //setting startup counters to match with the EEPROM values
  counterY = EEPROM.read(eepromY);
  counterHook = EEPROM.read(eepromHook);
  servoX.attach(9); //setting servo motors 
  servoY.attach(8);
  servoHook.attach(7);
  pinMode (2, INPUT_PULLUP); //setting up pin 2 to be input with the integrated resistor
  servoX.write(counterX);
  servoY.write(counterY);
  servoHook.write(counterHook);
  Serial.begin(9600); //setting up serial montior
}
void XJoy() { //setting up XJoy function
   if(analogRead(A1) < 200) { //if joystick is in a position less than 200, it will add 3 to the counter which is written to the servo motor
    counterX += 3;
    servoX.write(counterX);
  }
  delay (15);

  if (analogRead(A1) > 600) { //if joystick is in a position more than 600, it will subtract 3 to the counter which is written to the servo motor
    counterX -= 3;
    servoX.write(counterX);
  }
  delay (15);

  if (counterX >= 180) { //if counter goes above 180, it will set the counter to 180 and write it to the servo motor
    counterX = 180;
    servoX.write(counterX);
  }

  if (counterX <= 0) { //if counter goes below 0, it will set the counter to 0 and write it to the servo motor
    counterX = 0;
    servoX.write(counterX);
  }
}

void YJoy() { //setting up YJoy function
  if(analogRead(A0) < 200) { //if joystick is in a position less than 200, it will add 3 to the counter which is written to the servo motor
    counterY += 3;
    servoY.write(counterY);
  }
  delay (15);

  if (analogRead(A0) > 600) { //if joystick is in a position more than 600, it will subtract 3 to the counter which is written to the servo motor
    counterY -= 3;
    servoY.write(counterY);
  }
  delay (15);

  if (counterY <= 90) { //if counter goes below 90, it will set the counter to 90 and write it to the servo motor
    counterY = 90;
    servoY.write(counterY);
  }

  if (counterY >= 180) { //if counter goes above 180, it will set the counter to 180 and write it to the servo motor
    counterY = 180;
    servoY.write(counterY);
  }
}

void HookJoy() {
   if(analogRead(A2) < 200) { //if joystick is in a position less than 200, it will add 3 to the counter which is written to the servo motor
    counterHook += 3;
    servoHook.write(counterHook);
  }
  delay (15);

  if (analogRead(A2) > 600) { //if joystick is in a position more than 600, it will subtract 3 to the counter which is written to the servo motor
    counterHook -= 3;
    servoHook.write(counterHook);
  }
  delay (15);

  if (counterHook <= 60) { //if counter goes below 60, it will set the counter to 0 and write it to the servo motor
    counterHook = 60;
    servoHook.write(counterHook);
  }

  if (counterHook >= 180) { //if counter goes above 180, it will set the counter to 180 and write it to the servo motor
    counterHook = 180;
    servoHook.write(counterHook);
  }
}

void eepromUpdate() { //setting up eepromUpdate function
  EEPROM.update(eepromX, counterX); //updates specified EEPROM address with the current value of the given counter
  EEPROM.update(eepromY, counterY);
  EEPROM.update(eepromHook, counterHook);
}

void btnSaving() { //setting up btnSaving function
  if (lastbtnState != btnState) { //checks if current button state is different from the previous button state
    if (btncounter == 0) { //checks if button counter is equal to 0
     saveX = counterX; //saves the given counter values
     saveY = counterY;
     saveHook = counterHook; 
    btncounter ++ ; //adds 1 to the button counter
    }
 else (btncounter == 1); { //checks if button counter is equal to 1
    if (lastbtnState != btnState) { //checks if current button state is different from the previous button state
      while (counterX != saveX) { //checks if the given counter value is equal to the saved value. If not, it will add or subract 1 from the given counter until the given value is equal to the saved value
        if (counterX >= saveX) {
          counterX -= 1; 
          delay(30); //delay to slow down process
          servoX.write(counterX); //writes to servo motor
          delay(30);
        }
        else (counterX <= saveX); {
          counterX += 1;
          delay(30);
          servoX.write(counterX);
          delay(30);
        }
      }

      while (counterY != saveY) {
        if (counterY >= saveY) {
          counterY -= 1;
          delay(30);
          servoY.write(counterY);
          delay(30);
        }
        else (counterY <= saveY); {
          counterY += 1;
          delay(30);
          servoY.write(counterY);
          delay(30);
        }
      }
      lastbtnState = btnState; //sets the previous button state to the current button state so that the code above does not run multiple times
    }
  }
  delay(1); //delay to decrease bouncing
    }
    if (btncounter >= 2) { //if the button counter goes above 2, it will set it back to 1
      btncounter = 1;
      delay (15); //decrease bouncing
    }
  }

void loop() {
XJoy(); //calling specified function to run in given order
YJoy();
HookJoy();
eepromUpdate();
btnState = digitalRead(btn); //tells btnState to read from digital pin 2
Serial.println(btnState); //serial print the current button state
Serial.print("Button Counter : "); //serial prints the button counter value
Serial.println(btncounter);
btnSaving();
}
