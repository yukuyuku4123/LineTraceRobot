#include <Arduino.h>

#define LED1 13
#define LED2 12
#define LED3 11
#define SW 10
#define Buzzer 9
#define MD1 6
#define MD2 5
#define Echo 3
#define Trig 2
#define Light A0
#define Line1 A1
#define Line2 A2

int melo = 200;
bool startFlag = false;

double Duration = 0;
double Distance = 0; 

void beginBuzzer();
void startBuzzer();
void stopBuzzer();
void readLight();
void start();
void stop();
void move();
void readLine();
void readForward();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Light, INPUT);
  pinMode(Line1, INPUT);
  pinMode(Line2, INPUT);

  beginBuzzer();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SW) == LOW) {
    if (startFlag == false) {
      startFlag = true;
      start();
    } else {
      startFlag = false;
      stop();
    }
  }
  if (startFlag == true) {
    readLight();
    readForward();
  } else if (startFlag == false) {
    ;
  }
}

void beginBuzzer() {
  tone(Buzzer, 262, melo);
  delay(melo);
  tone(Buzzer, 294, melo);
  delay(melo);
  tone(Buzzer, 330, melo);
  delay(melo);
  noTone(Buzzer);
  delay(melo);
}

void startBuzzer() {
  tone(Buzzer, 131, 300);
  delay(500);
  tone(Buzzer, 131, 300);
  delay(500);
  tone(Buzzer, 196, 300);
  delay(500);
  tone(Buzzer, 196, 300);
  delay(500);
  tone(Buzzer, 220, 300);
  delay(500);
  tone(Buzzer, 220, 300);
  delay(500);
  tone(Buzzer, 196, 300);
  delay(1000);
  tone(Buzzer, 175, 300);
  delay(500);
  tone(Buzzer, 175, 300);
  delay(500);
  tone(Buzzer, 165, 300);
  delay(500);
  tone(Buzzer, 165, 300);
  delay(500);
  tone(Buzzer, 147, 300);
  delay(500);
  tone(Buzzer, 147, 300);
  delay(500);
  tone(Buzzer, 131, 300);
  delay(1000);
}

void stopBuzzer() {
  tone(Buzzer, 392, 200);
  delay(200);
  tone(Buzzer, 349, 200);
  delay(200);
  tone(Buzzer, 392, 200);
  delay(400);
  tone(Buzzer, 392, 200);
  delay(200);
  tone(Buzzer, 349, 200);
  delay(200);
  tone(Buzzer, 392, 200);
  delay(400);
  tone(Buzzer, 392, 200);
  delay(200);
  tone(Buzzer, 349, 200);
  delay(200);
  tone(Buzzer, 392, 200);
  delay(400);
}

void readLight() {
  if (digitalRead(Light) == HIGH) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }
}

void start() {
  digitalWrite(LED1, HIGH);
  startBuzzer();
}

void stop() {
  digitalWrite(LED1, LOW);
  stopBuzzer();
}

void readForward() {
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH);
  delayMicroseconds( 10);
  digitalWrite(Trig, LOW);
  Duration = pulseIn(Echo, HIGH);
  if (Duration > 0) {
    Duration = Duration/2;
    Distance = Duration*340*100/1000000;
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");
  }
  delay(500);
}