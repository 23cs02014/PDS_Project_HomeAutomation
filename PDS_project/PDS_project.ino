#include <Servo.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo a1;
Servo a2;
#define light 11
#define buzzer 12
#define LDR A0
#define smokeSensor A1
#define door 9
#define window 10
struct cspro{
  char Incoming_value=0;
  bool flag;
  bool AUTOWN;
  bool AUTO;
  byte current_brightness;
};
struct cspro x1;
void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT); //light.
  pinMode(buzzer, OUTPUT); //buzzer.
  pinMode(smokeSensor, INPUT_PULLUP); //SmokeSensor.
  pinMode(LDR, INPUT_PULLUP); //photoresistor.
  a1.attach(door);//door
  a2.attach(window);//window
  dht.begin();//to start the dht sensor
  
  x1.flag=0;
  x1.avg=0;
  x1.AUTOWN=0;//initialising the variables 
  x1.AUTO=0;
  /*used pins 2,9,10,11,12,A0,A1*/
}
void openDoor() {// to open door
  a1.write(180);
}
void closeDoor() {// to close door
  a1.write(0);
}
void openWindow() {// to open window
  a2.write(90);
}
void closeWindow() {// to close window
  a2.write(0);
}

// switching lights on slowly using PWM
void lightsOn() {
  if (x1.flag == 0) {
    for (int i = 0; i < 256; i++) {
      analogWrite(light, i);
      delay(10);
    }
    x1.flag = 1;
  }
}
//to turn off lights slowly using PWM and int n which is the previous state of the lights
void lightsOff(byte n) {
  if (x1.flag == 1) {
    for (int i = n; i >= 0; i--) {
      analogWrite(light, i);
      delay(2);
    }
    x1.flag = 0;
  }
}
// to read values from the LDR
/*Here we are taking average of n values to reduce "Jitter", we found 5 values to be sufficient to reduce the jitter*/
// it returns a 10bit value
int readLight(int n){
  int avg = 0;
  for(int i = 0 ; i < n ; i++){
    avg+=analogRead(A0);
  }
  avg=avg/n;
  return avg;
}
// to read values from smoke sensor
/*Here we are taking average of n values to reduce "Jitter", we found 5 values to be sufficient to reduce the jitter*/
// it returns a 10bit value
int readSmoke(int n){
    int avg = 0;
  for(int i = 0 ; i < n ; i++){
    avg+=analogRead(A1);
  }
  avg=avg/n;
  return avg;
}
// to read values from dht temperature sensor
/*Here we are taking average of n values to reduce "Jitter", we found 5 values to be sufficient to reduce the jitter*/
//it returns values in celcius
int readTemp(int n){
      int avg = 0;
  for(int i = 0 ; i < n ; i++){
    avg+=dht.readTemperature();
  }
  avg=avg/n;
  return avg;
}

void loop() {
  // checking if a value is being sent
  if (Serial.available() > 0) {
    //Reading the value
    x1.Incoming_value = Serial.read();
    //Printing the value in the serial monitor
    Serial.println(x1.Incoming_value);
    //Entering the switch-case
    switch (x1.Incoming_value) {
      case '0':
        closeDoor();
        break;
      case '1':
        openDoor();
        break;
      case '3':
        /*checking AUTOWN to see if the automatic blinds toggle is inactive*/
        if (x1.AUTOWN == 0)
          openWindow();
        break;
      case '2':
        /*checking AUTOWN to see if the automatic blinds toggle is inactive*/
        if (x1.AUTOWN == 0)
          closeWindow();
        break;
      case 't':
        /*checking AUTO to see if the automatic lights toggle is inactive*/
        if (x1.AUTO == 0)
          lightsOn();
        break;
      case 'r':
        /*checking AUTO to see if the automatic lights toggle is inactive*/
        if (x1.AUTO == 0)
          analogWrite(11,map(75,0,100,0,255));
          x1.current_brightness=map(75,0,100,0,255);
        break;
      case 'e':
        /*checking AUTO to see if the automatic lights toggle is inactive*/
        if (x1.AUTO == 0)
          analogWrite(11,map(50,0,100,0,255));
          x1.current_brightness=map(50,0,100,0,255);
        break;
      case 'w':
        /*checking AUTO to see if the automatic lights toggle is inactive*/
        if (x1.AUTO == 0)
          analogWrite(11,map(25,0,100,0,255));
          x1.current_brightness=map(25,0,100,0,255);
        break;  
      case 'q':
        /*checking AUTO to see if the automatic lights toggle is inactive*/
        if (x1.AUTO == 0)
          lightsOff(x1.current_brightness);
        break;
      case 'A':
        /*Setting the AUTO value as per the lights toggle*/
        x1.AUTO = 1;
        break;
      case 'O':
        /*Setting the AUTO value as per the lights toggle*/
        x1.AUTO = 0;
        break;
      case 'B':
        /*Setting the AUTOWN value as per the blinds toggle*/
        x1.AUTOWN = 1;
        break;
      case 'C':
        /*Setting the AUTOWN value as per the blinds toggle*/
        x1.AUTOWN = 0;
        break;
    }
  }
  /*Checking if AUTO is enabled*/
  if (x1.AUTO) {
    /*reading and checking the values againt the preset threshold*/
    if (readLight(5) < 150) {
      lightsOff(255);
    } else {
      lightsOn();
    }
  }
//  Serial.println(analogRead(A0));
  /*Checking if AUTOWN is enabled*/
  if (x1.AUTOWN == 1) {
    /*reading and checking the values againt the preset threshold*/
    if (readTemp(5)<30) {
      closeWindow();
    } else {
      openWindow();
    }
  }
  /*reading and checking the values againt the preset threshold*/
  /*For the smoke sensor which enables the buzzer*/
   if(readSmoke(5)<=300){
     digitalWrite(buzzer,HIGH);    
   }
   else{
     digitalWrite(buzzer,LOW);
   }
  // Serial.print("temp:");
  // Serial.print(readTemp(5)); /* temp sensor for auto window*/
  // Serial.print("|| smoke:");
  // Serial.print(readSmoke(5));
  // Serial.print("|| Photo:");
  // Serial.println(readLight(5));

}

/*
0 = close door
1 = open door
A = auto on lights
O = auto off lights
0% = q
25% = w
50% = e 
75% = r
100% = t
2 = close window
3 = open window
B = auto window on
C = auto window off
*/
