const int buttonPin1 = 6;         // button pin for left button
const int buttonPin2 = 7;         // button pin for right button
const int buttonPin3 = 8;         // button pin for up button
const int buttonPin4 = 9;         // button pin for down button
const int xPin = A0;              // analog pin for the X axis
const int yPin = A1;              // analog pin for the Y axis
const int switchPin = 2;          // digital pin for the switch (push down on joystick)
int buttonState1 = 0;             // button state for left button
int buttonState2 = 0;             // button state for right button
int buttonState3 = 0;             // button state for up button
int buttonState4 = 0;             // button state for down button
int switchState = 0;              // switch state for joystick
int xState = 0;                   // x-axis state for joystick
int yState = 0;                   // y-axis state for joystick
bool hit = false;                 // makes sure that the buttons only register as 1 hit

/*** Sets up the controller ***/
void setup() {
    Serial.begin(9600);
    
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    pinMode(buttonPin4, INPUT);
    pinMode(switchPin, INPUT);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);

    //digitalWrite(buttonPin1, HIGH);
    //digitalWrite(buttonPin2, HIGH);
}

/*** Tests the controller ***/
void loop() {
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    
    buttonSwitch();

    switchState = digitalRead(switchPin);
    xState = analogRead(xPin);
    yState = analogRead(yPin);

    joystickSwitch();
    joystickAxis();
    
    // if there's no delay, the buttons read like 10 outputs per hit
    delay(250);
}

void buttonSwitch() {
    // if left button is hit
    if (buttonState1 == HIGH) {
        /*if (hit) {
            hit = false;
            buttonState1 == HIGH;
        } else {
            hit = true;
            buttonState1 == LOW;
        }*/
        
        Serial.println("LEFT");
                
        Serial.write(0);
        Serial.flush();
    }
    // if right button is hit
    if (buttonState2 == HIGH) {
        /*if (hit) {
            hit = false;
            buttonState2 == HIGH;
        } else {
            hit = true;
            buttonState2 == LOW;
        }*/
      
        Serial.println("RIGHT");
                
        Serial.write(1);
        Serial.flush();
    }
    // if right button is hit
    if (buttonState3 == HIGH) {
        Serial.println("UP");
                
        Serial.write(2);
        Serial.flush();
    }
    // if down button is hit
    if (buttonState4 == HIGH) {
        Serial.println("DOWN");
                
        Serial.write(3);
        Serial.flush();
    }
}

void joystickSwitch() {
    // if switch on the joystick is hit
    if (switchState == HIGH) {
        if (hit) { 
            hit = false;
            switchState == HIGH;
        } else {
            hit = true;
            switchState == LOW;
        }

        Serial.println("SWITCH PRESSED");

        //delay(20);
    }
}

void joystickAxis() {
     // movement in -Y direction
     if (xState >= 0 && yState <= 10){
        //digitalWrite(10, HIGH);
        Serial.println("X-axis:  " + xState);
        Serial.println("Y-axis:  " + yState);
     } /*else {
        digitalWrite(10, LOW);
     }*/
     // movement in -X direction
    if (xState <= 10 && yState >= 500){
        //digitalWrite(11, HIGH);
        Serial.println("X-axis:  " + xState);
        Serial.println("Y-axis:  " + yState);
    } /*else {
        digitalWrite(11, LOW);
    }*/
    // movement in +X direction
    if (xState >= 1020 && yState >= 500){
        //digitalWrite(9, HIGH);
        Serial.println("X-axis:  " + xState);
        Serial.println("Y-axis:  " + yState);
    } /*else {
        digitalWrite(9, LOW);
    }*/
    // movement in the +Y direction
    if (xState >= 500 && yState >= 1020){
        //digitalWrite(8, HIGH);
        Serial.println("X-axis:  " + xState);
        Serial.println("Y-axis:  " + yState);
    } /*else {
        digitalWrite(8, LOW);
    }*/
}
