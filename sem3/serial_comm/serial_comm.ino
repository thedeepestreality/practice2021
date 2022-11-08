//www.elegoo.com
//2016.12.9

#include <Keypad.h>
#include <LedControl.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte colPins[ROWS] = {5,4,3,2}; //connect to the row pinouts of the keypad
byte rowPins[COLS] = {9,8,7,6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LedControl lc=LedControl(12,10,11,1);
void setup(){
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  lc.setLed(0,1,1,1);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }

  if (Serial.available() >= 3)
  {
    String s = Serial.readString();
    int row = s[0] - 48;
    int col = s[1] - 48;
    bool state = s[2] - 48;
    lc.setLed(0,row,col,state);
  }
}
