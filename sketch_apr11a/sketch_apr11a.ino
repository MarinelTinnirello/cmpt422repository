#include <LiquidCrystal.h>

const int buttonPin1 = 6;                     // location of button1
const int buttonPin2 = 7;                     // location of button2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);        // LCD coordinates on the board
String byte1 = "00000000";                    // base string seen on the LCD screen, byte1Screen()
String byte2 = "00000000";                    // base string seen on the LCD screen, byte2Screen()
int carry = 0;                                // for overflow
int calculatedResult = 0;                     // result found from strings
int buttonState1 = 0;                         // reads in the status on button1
int buttonState2 = 0;                         // reads in the status on button2
int backlight = 12;                           // for manual checking of backlight
int contrast = 5;                             // for manual checking of contrast
String str;                                   // does all the work
String str1 = "sfh";                          // test strings, for the individual byte1Screen()
String str2 = "fhs";                          // test strings, for the individual byte2Screen()
int index = 0;                                // index checker for the byteScreens()
bool one = false;                             // checks if current byte is 1 or 0
int goToNext = 0;                             // tells what screen we're currently on

/*** Sets up LCD Scrreen and the str = byte1 for input ***/
void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    analogWrite(backlight, 255);
    analogWrite(contrast, 50);

    lcd.setCursor(0, 0);

    str = byte1;
    lcd.print(str);
}

/*** Calls all other functions, then sets them up in a queue ***/
void loop() {
   buttonState1 = digitalRead(buttonPin1);
   buttonState2 = digitalRead(buttonPin2);

   if (goToNext == 0) {
      splashScreen();
   } else if(goToNext == 1) {
       byte1Screen();
   } else if (goToNext == 2) {
       byte2Screen();
   } else if (goToNext == 3) {
       calculate();
   } else if (goToNext == 4) {
      contrastScreen();
   }
   
   delay(250);
}

/*** Handles Splash screen ***/
void splashScreen() {
    //clear the screen and print new content  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to the");
    lcd.setCursor(0 ,1);
    lcd.print("Binary Calc");

    if ((buttonState1 == HIGH) && (buttonState2 == HIGH)) {
        goToNext++;
    }
}

/*** Handles the 1st byteScreen() ***/
void byte1Screen() {
   if(buttonState1 == HIGH) { 
      char c = -1;
  
      if(one) {
          c = '0';
          one = false;
      } else {
          c = '1';
          one = true;
      }
      str.setCharAt(index, c);
      lcd.clear();
      lcd.print(str);
      
      Serial.print(str);
   }

   if(buttonState2 == HIGH) {
      index++;
      one = false;

      Serial.print(index);

      if (index >= 8) {
          index = 0;
          goToNext++;
          byte1 = str.toInt();
          str = byte2;
          lcd.clear();
          lcd.print(str);
      }
   }
}

/*** Handles the 2nd byteScreen() ***/
void byte2Screen() {
   if(buttonState1 == HIGH) {
      char c = -1;
  
      if(one) {
          c = '0';
          one = false;
      } else {
          c = '1';
          one = true;
      }
      str.setCharAt(index, c);
      lcd.clear();
      lcd.print(str);
      
      Serial.print(str);
   }

   if(buttonState2 == HIGH) {
      index++;
      one = false;

      Serial.print(index);

      if (index >= 8) {
          byte2 = str.toInt();
          goToNext++;
      }
   }
}

/*** Deals with all the math and prints it out ***/
void calculate() {
    String result = "";                                     // Initialize result 
    int s = 0;                                              // Initialize digit sum 
    int i = byte1.length() - 1, j = byte2.length() - 1;     // goes through the byte Strings
    
    while (i >= 0 || j >= 0 || s == 1) 
    { 
        // the actual math
        s += ((i >= 0)? byte1[i] - '0': 0); 
        s += ((j >= 0)? byte2[j] - '0': 0); 
  
        result = char(s % 2 + '0') + result;      // puts the carry with the result 
  
        s /= 2;                                   // deals with the carry
  
        i--; j--; 
    } 
    lcd.clear();
    lcd.print(result);

    if ((buttonState1 == HIGH) && (buttonState2 == HIGH)) {
        goToNext++;
    }
}

/*** Handles the contrastScreen() ***/
void contrastScreen() {
    lcd.clear();
    lcd.print("Turn knob to");
    lcd.setCursor(0, 1);
    lcd.print("contrast bright");
    
    /*for (int i = 0; i <= 150; i++) {
      analogWrite(contrast, i);
      lcd.setCursor(0, 1);
      delay(80);
    }
    
    analogWrite(contrast, 50);
    lcd.clear();
    lcd.print("Back light:");
    
    for (int i = 0; i <= 255; i += 2) {
      analogWrite(backlight, i);
      lcd.setCursor(0, 1);
      delay(80);
    }*/
    if ((buttonState1 == HIGH) && (buttonState2 == HIGH)) {
        goToNext = 0;
    }
}
