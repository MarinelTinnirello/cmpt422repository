/*WORKS WITH BUTTON, NO TILT AS IT WAS LOST*/

/*************************************************
 * Notes for the Piezo Music
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#include <Servo.h>
//#include "pitches.h"

const int piezoPin = 8;   // piezo
const int rPin = 9;       // red LED
const int bPin = 10;      // blue LED
const int yPin = 5;       // yellow LED
const int gPin = 4;       // green LED
const int buttonPin = 6;  // button
//const int switchPin = 6;  // switch
const int servoPin =  3;  // servo
Servo servo;
int ledState = 0;
int isLedOn = false;
bool alreadyRun = false;
//int switchState = 0;
/*** how the song is gonna go ***/
/*notes themselves, needed to be played*/
int melody[] = {
  //NOTE_F5, NOTE_DS6, NOTE_AS5,NOTE_C6
  /* Megalovania - 1st 8 notes
  NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_D3, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4*/
  /*Matoya's Cave*/
  NOTE_B4, NOTE_D5, NOTE_FS5, NOTE_B4, NOTE_G5, NOTE_FS5, NOTE_E5, 
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_CS5,
  NOTE_D5, NOTE_FS5, NOTE_A5, NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5,
  NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_G5,
  NOTE_A5, NOTE_CS5, NOTE_E5,
  NOTE_D5/*, NOTE_CS5, NOTE_D5, NOTE_B4, NOTE_G5, NOTE_A5,
  NOTE_B5,NOTE_D5, NOTE_G5,
  NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_A5, NOTE_B5,
  NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,
  NOTE_E6, NOTE_D6, NOTE_CS6, NOTE_D6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_CS5, NOTE_A4,
  NOTE_FS5, NOTE_D4, NOTE_G5, NOTE_D4,
  NOTE_A4, NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_CS5, NOTE_B4, NOTE_CS5,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E5, NOTE_D5, NOTE_E5,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E5, NOTE_G5, NOTE_FS5, NOTE_G5,
  NOTE_FS5, NOTE_D5, NOTE_G5, NOTE_D5,
  NOTE_A5, NOTE_A5, NOTE_D5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_AS4*/
  };
/* duration of each note
* a duration is 2 = half notes
* this means any odd number must be represented by a fraction
*/
float duration[] = {
  //6,8,4,2
  /* Megalovania - 1st 8 notes
  16, 16, 8, 4, 12, 12, 4, 8, 12, 8, 4*/
  /*Matoya's Cave
  * https://gist.github.com/argelius/e8b0008567b388b98c4f */
  
  16,16,16,16,8,16,16,
  8,16,16,4,
  16,16,16,16,8,16,16,
  8,16,16,8,16,16,
  4,8,8,
  6/*,6,6,4.5,16,16,
  4,8,8,
  6,6,6,4.5,16,16,
  5,16,16,16,
  6,6,6,6,3,16,16,16,
  5,16,16,16,
  4,8,8,
  8,8,8,8,
  16,16,16,16,8,6,6,6,6,
  8,8,8,8,
  16,16,16,16,8,6,6,6,6,
  8,8,8,8,
  16,16,16,16,8,6,6,6,6,
  8,8,8,8,
  16,16,16,16,6,6,6,6,6,6,6,2*/
};
// calculates # of elements in the array, with starting note
int musicLength = sizeof(melody)/sizeof(melody[0]);

/* Sets up pin I/O */
void setup() {  
  Serial.begin(9600);         // use for debugging
  
  pinMode(buttonPin, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(gPin, OUTPUT);

  servo.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  //pinMode(switchPin, INPUT);
}

void loop() {
  int buttonPinState = digitalRead(buttonPin);    // reads in the state of the button
  Serial.println(buttonPinState);

  //switchState = digitalRead(switchPin);           // reads in the state of the switch

  /*if (buttonPinState == LOW)
  {
      ledState = 1;
      //Serial.println("jokes");
      
  }
  if (buttonPinState == LOW && ledState == 1)
  {   
      ledState = 2;
      isLedOn = true;
  }*/
  isLedOn = true;
  //if (buttonPinState == !HIGH && isLedOn) 
  if (alreadyRun == false && isLedOn == true)
  {
      finalCountdown();
      /* moves all functions for making this cleaner */
      playSong();

      
  } //else if (isLedOn == true)
  isLedOn = false; 
    if (alreadyRun == true && isLedOn == false)
    {
        digitalWrite(rPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(yPin, LOW);
        digitalWrite(gPin, LOW);

        /*if (switchState == HIGH) 
        {
          digitalWrite(servoPin, HIGH);
        } else 
        {
          digitalWrite(servoPin, LOW);
        }*/
        
        motor();
    }
}

void finalCountdown() {
    digitalWrite(rPin, HIGH);
    delay(1000);
    digitalWrite(bPin, HIGH);
    delay(1000);
    digitalWrite(yPin, HIGH);
    delay(1000);
    digitalWrite(gPin, HIGH);
    delay(1000);

    alreadyRun = true;

    if (buttonPinState == HIGH)
    {
        alreadyRun == false;
    }
}

/* Song handling done here */
void playSong() {
  for (int i = 0; i < musicLength; i++) 
  {
      /* sequence blinking in accordance to the index */
      if (i % 4 == 0)
      {    
        digitalWrite(rPin, HIGH);
        digitalWrite(bPin, LOW);
        digitalWrite(yPin, LOW);
        digitalWrite(gPin, LOW);
      } else if (i % 4 == 1)
      {
        digitalWrite(rPin, LOW);
        digitalWrite(bPin, HIGH);
        digitalWrite(yPin, LOW);
        digitalWrite(gPin, LOW);
      } else if (i % 4 == 2)
      {    
        digitalWrite(rPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(yPin, HIGH);
        digitalWrite(gPin, LOW);
      } else if (i % 4 == 3)
      {    
        digitalWrite(rPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(yPin, LOW);
        digitalWrite(gPin, HIGH);
      }

      int noteDuration = 2000 / duration[i];
      tone(piezoPin, melody[i], noteDuration);

      float pauseNotes = noteDuration * 1.30;

      /* button check
      * 1st delay: checks to see if button is turned off
      * 2nd delay: checks to turn off LEDs and sound
      */
      delay(pauseNotes / 2);
      if (digitalRead(buttonPin) == HIGH) 
      {
        break;      
      }
      delay (pauseNotes / 2);
      if(digitalRead(buttonPin) == HIGH) 
      {
        break;      
      }

      alreadyRun = true;
  }
}

void motor() {
    servo.write(0);
    delay(250);
    servo.write(90);
    delay(250);
    servo.write(180);
    delay(250);

    alreadyRun = true;
}
