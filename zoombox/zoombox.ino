#include "Arduino.h"
#include <Streaming.h>
#include "Switch.h"
#include "Keyboard.h"

// https://www.arduino.cc/en/Reference/KeyboardModifiers
// Keys
char ctrlKey = KEY_LEFT_CTRL;
char cmdKey = KEY_LEFT_GUI;
char shiftKey = KEY_LEFT_SHIFT;
char enterKey = KEY_RETURN;
char f17Key = KEY_F17;
char f18Key = KEY_F18;

// Buttons
int btnOne = 2;
int btnTwo = 3;
int btnThree = 4;
int smBtnOne = 8;
int smBtnTwo = 7;
int smBtnThree = 6;
int smBtnFour = 11;
int smBtnFive = 10;
int smBtnSix = 9;

const byte toggleSwitchpin = 5; // (right button)
int i;

Switch toggleSwitch = Switch(toggleSwitchpin);

void setup() {
  // set up button pins
  pinMode(btnOne, INPUT_PULLUP);
  pinMode(btnTwo, INPUT_PULLUP);
  pinMode(btnThree, INPUT_PULLUP);
  pinMode(smBtnOne, INPUT_PULLUP);
  pinMode(smBtnTwo, INPUT_PULLUP);
  pinMode(smBtnThree, INPUT_PULLUP);
  pinMode(smBtnFour, INPUT_PULLUP);
  pinMode(smBtnFive, INPUT_PULLUP);
  pinMode(smBtnSix, INPUT_PULLUP);
  
  // Initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  while (digitalRead(btnOne) == LOW) {
    // Toggle audio On/Off: Cmd+Shift+A
    // Changed via settings to F17 (Global)
    keyPress(f17Key);
  }

  while (digitalRead(btnTwo) == LOW) {
    // Toggle video On/Off: Cmd+Shift+V
    // Changed via settings to F18 (Global)
    keyPress(f18Key);
  }
  
  while (digitalRead(btnThree) == LOW) {
    leaveMeeting();
  }

  while (digitalRead(smBtnOne) == LOW) {
    // Take screenshot (OSX Global): Shift+Cmd+4
    Keyboard.press(shiftKey);
    Keyboard.press(cmdKey);
    keyPress('4');
  }

  while (digitalRead(smBtnTwo) == LOW) {
    // Start local recording: Cmd+Shift+R
    Keyboard.press(cmdKey);
    Keyboard.press(shiftKey);
    keyPress('r');
  }

  while (digitalRead(smBtnThree) == LOW) {
    // Switch camera: Cmd+Shift+N
    Keyboard.press(cmdKey);
    Keyboard.press(shiftKey);
    keyPress('n');
  }

  while (digitalRead(smBtnFour) == LOW) {
    // Toggle Active Speaker and Gallery views: Cmd+Shift+W
    Keyboard.press(cmdKey);
    Keyboard.press(shiftKey);
    keyPress('w');
  }

  while (digitalRead(smBtnFive) == LOW) {
    // Toggle Participants panel On/Off: Cmd+U
    Keyboard.press(cmdKey);
    keyPress('u');
  }

  while (digitalRead(smBtnSix) == LOW) {
    // Toggle In-Meeting Chat panel On/Off: Cmd+Shift+H
    Keyboard.press(cmdKey);
    Keyboard.press(shiftKey);
    keyPress('h');
  }

  if(toggleSwitch.poll()) {
    // Share your screen: Cmd+Shift+S
    Keyboard.press(cmdKey);
    Keyboard.press(shiftKey);
    keyPress('s');
  }

}

//////////////////////
// HELPER Functions //
//////////////////////

void keyPress(char key) {
    Keyboard.press(key);
    delay(100);
    Keyboard.releaseAll();
    delay(200);
}

void leaveMeeting() {
  // End/Leave meeting or close current window: Cmd+W > Enter
  Keyboard.press(cmdKey);
  keyPress('w');
  delay(500);
  keyPress(enterKey);
}
