#include <Servo.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo a1;
Servo a2;
struct cspro{
  char Incoming_value=0;
  int flag;
  int avg;
  int AUTOWN;
  int AUTO;
  int current_brightness;
};
struct cspro x1;
void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);  //light.
  pinMode(12, OUTPUT); //buzzer.
  pinMode(A1, INPUT_PULLUP); //SmokeSensor.
  pinMode(A0, INPUT_PULLUP); //photoresistor.
  a1.attach(9);//door
  a2.attach(10);//window
  dht.begin();
  
  x1.flag=0;
  x1.avg=0;
  x1.AUTOWN=0;
  x1.AUTO=0;
  /*used pins 2,9,10,11,12,A0,A1*/
}
void openDoor() {
  a1.write(180);
}
void closeDoor() {
  a1.write(0);
}
void openWindow() {
  a2.write(90);
}
void closeWindow() {
  a2.write(0);
}


void lightsOn() {
  if (x1.flag == 0) {
    for (int i = 0; i < 256; i++) {
      analogWrite(11, i);
      delay(10);
    }
    x1.flag = 1;
  }
}
void lightsOff(int n) {
  if (x1.flag == 1) {
    for (int i = n; i >= 0; i--) {
      analogWrite(11, i);
      delay(2);
    }
    x1.flag = 0;
  }
}
int readLight(int n){
  x1.avg = 0;
  for(int i = 0 ; i < n ; i++){
    x1.avg+=analogRead(A0);
  }
  x1.avg=x1.avg/n;
  return x1.avg;
}
int readSmoke(int n){
    x1.avg = 0;
  for(int i = 0 ; i < n ; i++){
    x1.avg+=analogRead(A1);
  }
  x1.avg=x1.avg/n;
  return x1.avg;
}
int readTemp(int n){
      x1.avg = 0;
  for(int i = 0 ; i < n ; i++){
    x1.avg+=dht.readTemperature();
  }
  x1.avg=x1.avg/n;
  return x1.avg;
}

void loop() {
  if (Serial.available() > 0) {
    x1.Incoming_value = Serial.read();
    Serial.println(x1.Incoming_value);
    switch (x1.Incoming_value) {
      case '0':
        closeDoor();
        break;
      case '1':
        openDoor();
        break;
      case '3':
        if (x1.AUTOWN == 0)
          openWindow();
        break;
      case '2':
        if (x1.AUTOWN == 0)
          closeWindow();
        break;
      case 't':
        if (x1.AUTO == 0)
          lightsOn();
        break;
      case 'r':
        if (x1.AUTO == 0)
          analogWrite(11,map(75,0,100,0,255));
          x1.current_brightness=map(75,0,100,0,255);
        break;
      case 'e':
        if (x1.AUTO == 0)
          analogWrite(11,map(50,0,100,0,255));
          x1.current_brightness=map(50,0,100,0,255);
        break;
      case 'w':
        if (x1.AUTO == 0)
          analogWrite(11,map(25,0,100,0,255));
          x1.current_brightness=map(25,0,100,0,255);
        break;  
      case 'q':
        if (x1.AUTO == 0)
          lightsOff(x1.current_brightness);
        break;
      case 'A':
        x1.AUTO = 1;
        break;
      case 'O':
        x1.AUTO = 0;
        break;
      case 'B':
        x1.AUTOWN = 1;
        break;
      case 'C':
        x1.AUTOWN = 0;
        break;
    }
  }
  if (x1.AUTO) {
    if (readLight(5) < 150) {
      lightsOff(255);
    } else {
      lightsOn();
    }
  }
//  Serial.println(analogRead(A0));
  if (x1.AUTOWN == 1) {
    if (readTemp(5)<30) {
      closeWindow();
    } else {
      openWindow();
    }
  }
  // if(readSmoke(5)<=300){
  //   digitalWrite(12,HIGH);    
  // }
  // else{
  //   digitalWrite(12,LOW);
  // }
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
