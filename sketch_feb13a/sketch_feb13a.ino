const int sensorPin = A0;
const float baselineTemp = 20.0;
const int redLEDPin = 11;
const int blueLEDPin = 10;
int redValue = 0;
int blueValue = 0;
int redSensorValue = 0;
int blueSensorValue = 0;

/***Sets up LED colors***/
void setLED(int redValue, int blueValue)
{
  analogWrite(blueLEDPin, blueValue);
  redSensorValue = analogRead(sensorPin);
}

/***Sets up program and PIN outputs***/
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  for (int pinNum = 2; pinNum < 5; pinNum++)
  {
    pinMode(pinNum, OUTPUT);
    digitalWrite(pinNum, LOW); 
  }
}

/***Loops for the entirety of running on the board***/
void loop() 
{
  int counterB = 0;
  int counterR = 0;
  
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor value:   ");
  Serial.print(sensorVal);

  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(" , Volts:   ");
  Serial.print(voltage);

  float temperature = (voltage - 0.5) * 100;
  Serial.print(" , Degrees (C):   ");
  Serial.print(temperature);

  // use the while loops here, since they're going to continue to run
  // use a longer delay to see changes
  // colors go from blue (cold), purple (cool), red (hot), white (really hot)

  while (temperature < baselineTemp)
  {
    setColor(0,0,255);
    delay(500);
    setColor(0,0,0);
    delay(500);
    counterB++;
  }
  while (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4)
  {
    setColor(128,0,128);
    delay(100);
    setColor(0,0,0);
    delay(100);
    counterB++;
  }
  while (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6)
  {
    setColor(255,0,0);
    delay(100);
    setColor(0,0,0);
    delay(100);
    counterR++;
  }
  while (temperature >= baselineTemp + 6)
  {
    setColor(255,255,255);
    delay(100);
    setColor(0,0,0);
    delay(100);
    counterR++;
  }

  delay(1);
}
