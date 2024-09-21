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
int readLight();
void start();
void stop();
void forward();
void brake();
void left();
void right();
int readLine();
int readForward();

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

  digitalWrite(MD1, LOW);
  digitalWrite(MD2, LOW);

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
    if (readLight() == 1) {
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED2, LOW);
    }
    if (readForward() == 1) {
      brake(); 
    } else {
      switch (readLine()) {
        case 0:
          forward();
          break;
        case 1:
          right();
          break;
        case 2:
          left();
          break;
        case 3:
          forward();
          break;
      }
     ;
    }
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

int readLight() {
  if (digitalRead(Light) == HIGH) {
    return 1;
  } else {
    return 0;
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

int readForward() {
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
    if (Distance < 20) {
      tone(Buzzer, 392, 200);
      delay(100);
      noTone(Buzzer);
      return 1;
    }
  }
  delay(100);
  return 0;
}

int readLine() {
  if (digitalRead(Line1) == HIGH && digitalRead(Line2) == LOW) {
    return 1;
  } else if (digitalRead(Line1) == LOW && digitalRead(Line2) == HIGH) {
    return 2;
  } else if (digitalRead(Line1) == HIGH && digitalRead(Line2) == HIGH) {
    return 3;
  } else if (digitalRead(Line1) == LOW && digitalRead(Line2) == LOW) {
    return 3;
  }
  return 0;
}

void brake() {
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, LOW);
  digitalWrite(LED3, LOW);
}

void forward() {
  analogWrite(MD1, 30);
  analogWrite(MD2, 30);
  digitalWrite(LED3, HIGH);
}

void left() {
  digitalWrite(MD1, LOW);
  analogWrite(MD2, 30);
  digitalWrite(LED3, HIGH);
}

void right() {    
  analogWrite(MD1, 30);
  digitalWrite(MD2, LOW);
  digitalWrite(LED3, HIGH);
}