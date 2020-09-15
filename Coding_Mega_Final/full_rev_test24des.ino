#define trigPinA1 2
#define echoPinA1 4
#define trigPinA2 6
#define echoPinA2 8
#define trigPinA3 12
#define echoPinA3 14
#define trigPinA4 16
#define echoPinA4 18
#define trigPinA5 3
#define echoPinA5 5
#define trigPinA6 7
#define echoPinA6 9
#define trigPinA7 13
#define echoPinA7 15
#define trigPinA8 17
#define echoPinA8 19
#define trigPinB1 25
#define echoPinB1 23
#define trigPinB2 29
#define echoPinB2 27
#define trigPinB3 30
#define echoPinB3 31
#define trigPinB4 26
#define echoPinB4 28
#define trigPinB5 22
#define echoPinB5 24
#define trigPinB6 35
#define echoPinB6 33
#define trigPinB7 36
#define echoPinB7 37
#define trigPinB8 32
#define echoPinB8 34

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         38           // Configurable, see typical pin layout above
#define SS_PIN          39          // Configurable, see typical pin layout above

SoftwareSerial SerialESP(10,11);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorValueA1 = 0; int sensorValueA2 = 0;
int sensorValueA3 = 0; int sensorValueA4 = 0;
int sensorValueA5 = 0; int sensorValueA6 = 0;
int sensorValueA7 = 0; int sensorValueA8 = 0;

int sensorValueB1 = 0; int sensorValueB2 = 0;
int sensorValueB3 = 0; int sensorValueB4 = 0;
int sensorValueB5 = 0; int sensorValueB6 = 0;
int sensorValueB7 = 0; int sensorValueB8 = 0;

int SisaParkir = 16;
int IR_1 = 47; //exit
int IR_2 = 46; //enter
int currentState = 0;
int previousState1 = 0; int previousState2 = 0;
int IR_1_op; int IR_2_op;

void setup() {
Serial.begin (9600);
SerialESP.begin(9600);
lcd.begin();        // Initialize serial communications with the PC
SPI.begin();                // Init SPI bus
mfrc522.PCD_Init();         // Init MFRC522 card
myservo.attach(42);
myservo.write(0);
readlcd();
  pinMode(trigPinA1, OUTPUT);  pinMode(echoPinA1, INPUT);
  pinMode(trigPinA2, OUTPUT);  pinMode(echoPinA2, INPUT);
  pinMode(trigPinA3, OUTPUT);  pinMode(echoPinA3, INPUT);
  pinMode(trigPinA4, OUTPUT);  pinMode(echoPinA4, INPUT);
  pinMode(trigPinA5, OUTPUT);  pinMode(echoPinA5, INPUT);
  pinMode(trigPinA6, OUTPUT);  pinMode(echoPinA6, INPUT);
  pinMode(trigPinA7, OUTPUT);  pinMode(echoPinA7, INPUT);
  pinMode(trigPinA8, OUTPUT);  pinMode(echoPinA8, INPUT);
  pinMode(trigPinB1, OUTPUT);  pinMode(echoPinB1, INPUT);
  pinMode(trigPinB2, OUTPUT);  pinMode(echoPinB2, INPUT);
  pinMode(trigPinB3, OUTPUT);  pinMode(echoPinB3, INPUT);
  pinMode(trigPinB4, OUTPUT);  pinMode(echoPinB4, INPUT);
  pinMode(trigPinB5, OUTPUT);  pinMode(echoPinB5, INPUT);
  pinMode(trigPinB6, OUTPUT);  pinMode(echoPinB6, INPUT);
  pinMode(trigPinB7, OUTPUT);  pinMode(echoPinB7, INPUT);
  pinMode(trigPinB8, OUTPUT);  pinMode(echoPinB8, INPUT);
  
}

void loop() {

updatelcd();
readrfid();
readSensor();
String str_sensorA1 = String(sensorValueA1);
String str_sensorA2 = String(sensorValueA2);
String str_sensorA3 = String(sensorValueA3);
String str_sensorA4 = String(sensorValueA4);
String str_sensorA5 = String(sensorValueA5);
String str_sensorA6 = String(sensorValueA6);
String str_sensorA7 = String(sensorValueA7);
String str_sensorA8 = String(sensorValueA8);
String str_sensorB1 = String(sensorValueB1);
String str_sensorB2 = String(sensorValueB2);
String str_sensorB3 = String(sensorValueB3);
String str_sensorB4 = String(sensorValueB4);
String str_sensorB5 = String(sensorValueB5);
String str_sensorB6 = String(sensorValueB6);
String str_sensorB7 = String(sensorValueB7);
String str_sensorB8 = String(sensorValueB8);

String kirim_datasensor = str_sensorA1 + str_sensorA2 + str_sensorA3 + str_sensorA4 + str_sensorA5 + str_sensorA6 + str_sensorA7 + str_sensorA8 + str_sensorB1 + str_sensorB2 + str_sensorB3 + str_sensorB4 + str_sensorB5 + str_sensorB6 + str_sensorB7 + str_sensorB8;
Serial.println(kirim_datasensor);
SerialESP.println(kirim_datasensor);
delay(2000);
}

void updatelcd() {
  IR_1_op = digitalRead(IR_1);
  IR_2_op = digitalRead(IR_2);
  if (IR_1_op == HIGH && IR_2_op == LOW)
  {
    currentState=1;  
  }
  else 
  {
    currentState=0;
  }
  if(currentState!=previousState1)
  {
    if(currentState==1)
    {
      SisaParkir = SisaParkir - 1;
      lcd.setCursor(14,1);
      lcd.print("  ");
      lcd.setCursor(14,1);
      lcd.print(SisaParkir);
    }
  }
  previousState1 = currentState;
  
  if (IR_1_op == LOW && IR_2_op == HIGH)
  {
    currentState=1;  
  }
  else 
  {
    currentState=0;
  }
  if(currentState!=previousState2)
  {
    if(currentState==1)
    {
      SisaParkir = SisaParkir + 1;
      lcd.setCursor(14,1);
      lcd.print("  ");
      lcd.setCursor(14,1);
      lcd.print(SisaParkir);
    }
  }
  previousState2=currentState;
}
void readrfid() {
  if(!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String uid="";
  Serial.println();
  Serial.print("UID=");
  for(int i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i]<0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i],HEX);
    uid.concat(String(mfrc522.uid.uidByte[i]<0x10 ? "0" : ""));
    uid.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  uid.toUpperCase();
  Serial.println();
  if(uid=="19B5DE59")
  {
    Serial.println("Akses Diterima");
    myservo.write(90);
  }
  else if(uid=="19F1DE5A")
  {
    Serial.println("Akses Diterima");
    myservo.write(90);
  }
  else if(uid=="794CCF5A")
  {
    Serial.println("Akses Diterima");
    myservo.write(90);
  }
  else if(uid=="79D7C05A")
  {
    Serial.println("Akses Diterima");
    myservo.write(90);
  }
  else if(uid=="29F4C45A")
  {
    Serial.println("Akses Diterima");
    myservo.write(90);
  }
  else
  {
    Serial.println("Akses Ditolak!");
  }
  delay(5000);
  myservo.write(0);
  return;
}

void readlcd() {
  lcd.setCursor(0,0);
  lcd.print(" Selamat Datang ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(" Sisa Parkir:  ");
  lcd.setCursor(14,1);
  lcd.print(SisaParkir);
  delay(2000);
}

void readSensor() {
  //Pembacaan nilai sensor A1
int durationA1, distanceA1;
  digitalWrite (trigPinA1, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA1, LOW);
  durationA1 = pulseIn (echoPinA1, HIGH);
  distanceA1 = durationA1*0.034/2;

  if (distanceA1 < 6) {  // Change the number for long or short distances. 
    sensorValueA1 = 1;
  } else {
    sensorValueA1 = 0; 
  }  
Serial.print("Sensor A1: ");
Serial.println(sensorValueA1);

//Pembacaan nilai sensor A2
int durationA2, distanceA2;
  digitalWrite (trigPinA2, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA2, LOW);
  durationA2 = pulseIn (echoPinA2, HIGH);
  distanceA2 = durationA2*0.034/2;

  if (distanceA2 < 5) {  // Change the number for long or short distances. 
    sensorValueA2 = 1;
  } else {
    sensorValueA2 = 0;
  }  
Serial.print("Sensor A2: ");
Serial.println(sensorValueA2);

//Pembacaan nilai sensor A3
int durationA3, distanceA3;
  digitalWrite (trigPinA3, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA3, LOW);
  durationA3 = pulseIn (echoPinA3, HIGH);
  distanceA3 = durationA3*0.034/2;

  if (distanceA3 < 5) {  // Change the number for long or short distances. 
    sensorValueA3 = 1;
  } else {
    sensorValueA3 = 0;
  }  
Serial.print("Sensor A3: ");
Serial.println(sensorValueA3);

//Pembacaan nilai sensor A4
int durationA4, distanceA4;
  digitalWrite (trigPinA4, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA4, LOW);
  durationA4 = pulseIn (echoPinA4, HIGH);
  distanceA4 = durationA4*0.034/2;

  if (distanceA4 < 5) {  // Change the number for long or short distances. 
    sensorValueA4 = 1;
  } else {
    sensorValueA4 = 0;
  }  
Serial.print("Sensor A4: ");
Serial.println(sensorValueA4);

//Pembacaan nilai sensor A5
int durationA5, distanceA5;
  digitalWrite (trigPinA5, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA5, LOW);
  durationA5 = pulseIn (echoPinA5, HIGH);
  distanceA5 = durationA5*0.034/2;

  if (distanceA5 < 5) {  // Change the number for long or short distances. 
    sensorValueA5 = 1;
  } else {
    sensorValueA5 = 0;
  }  
Serial.print("Sensor A5: ");
Serial.println(sensorValueA5);
 
//Pembacaan nilai sensor A6
int durationA6, distanceA6;
  digitalWrite (trigPinA6, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA6, LOW);
  durationA6 = pulseIn (echoPinA6, HIGH);
  distanceA6 = durationA6*0.034/2;

  if (distanceA6 < 5) {  // Change the number for long or short distances. 
    sensorValueA6 = 1;
  } else {
    sensorValueA6 = 0;
  }  
Serial.print("Sensor A6: ");
Serial.println(sensorValueA6);

//Pembacaan nilai sensor A7
int durationA7, distanceA7;
  digitalWrite (trigPinA7, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA7, LOW);
  durationA7 = pulseIn (echoPinA7, HIGH);
  distanceA7 = durationA7*0.034/2;

  if (distanceA7 < 5) {  // Change the number for long or short distances. 
    sensorValueA7 = 1;
  } else {
    sensorValueA7 = 0;
  }  
Serial.print("Sensor A7: ");
Serial.println(sensorValueA7);

//Pembacaan nilai sensor A8
int durationA8, distanceA8;
  digitalWrite (trigPinA8, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA8, LOW);
  durationA8 = pulseIn (echoPinA8, HIGH);
  distanceA8 = durationA8*0.034/2;

  if (distanceA8 < 5) {  // Change the number for long or short distances. 
    sensorValueA8 = 1;
  } else {
    sensorValueA8 = 0;
  }  
Serial.print("Sensor A8: ");
Serial.println(sensorValueA8);

  //Pembacaan nilai sensor B1
int durationB1, distanceB1;
  digitalWrite (trigPinB1, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB1, LOW);
  durationB1 = pulseIn (echoPinB1, HIGH);
  distanceB1 = durationB1*0.034/2;

  if (distanceB1 < 5) {  // Change the number for long or short distances. 
    sensorValueB1 = 1;
  } else {
    sensorValueB1 = 0; 
  }  

Serial.print("Sensor B1: ");
Serial.println(sensorValueB1);

//Pembacaan nilai sensor B2
int durationB2, distanceB2;
  digitalWrite (trigPinB2, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB2, LOW);
  durationB2 = pulseIn (echoPinB2, HIGH);
  distanceB2 = durationB2*0.034/2;

  if (distanceB2 < 5) {  // Change the number for long or short distances. 
    sensorValueB2 = 1;
  } else {
    sensorValueB2 = 0;
  }  
Serial.print("Sensor B2: ");
Serial.println(sensorValueB2);

//Pembacaan nilai sensor B3
int durationB3, distanceB3;
  digitalWrite (trigPinB3, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB3, LOW);
  durationB3 = pulseIn (echoPinB3, HIGH);
  distanceB3 = durationB3*0.034/2;

  if (distanceB3 < 5) {  // Change the number for long or short distances. 
    sensorValueB3 = 1;
  } else {
    sensorValueB3 = 0;
  }  
Serial.print("Sensor B3: ");
Serial.println(sensorValueB3);

//Pembacaan nilai sensor B4
int durationB4, distanceB4;
  digitalWrite (trigPinB4, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB4, LOW);
  durationB4 = pulseIn (echoPinB4, HIGH);
  distanceB4 = durationB4*0.034/2;

  if (distanceB4 < 5) {  // Change the number for long or short distances. 
    sensorValueB4 = 1;
  } else {
    sensorValueB4 = 0;
  }  
Serial.print("Sensor B4: ");
Serial.println(sensorValueB4);

//Pembacaan nilai sensor B5
int durationB5, distanceB5;
  digitalWrite (trigPinB5, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB5, LOW);
  durationB5 = pulseIn (echoPinB5, HIGH);
  distanceB5 = durationB5*0.034/2;

  if (distanceB5 < 5) {  // Change the number for long or short distances. 
    sensorValueB5 = 1;
  } else {
    sensorValueB5 = 0;
  }  
Serial.print("Sensor B5: ");
Serial.println(sensorValueB5);

  
//Pembacaan nilai sensor B6
int durationB6, distanceB6;
  digitalWrite (trigPinB6, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB6, LOW);
  durationB6 = pulseIn (echoPinB6, HIGH);
  distanceB6 = durationB6*0.034/2;

  if (distanceB6 < 5) {  // Change the number for long or short distances. 
    sensorValueB6 = 1;
  } else {
    sensorValueB6 = 0;
  }  
Serial.print("Sensor B6: ");
Serial.println(sensorValueB6);

//Pembacaan nilai sensor B7
int durationB7, distanceB7;
  digitalWrite (trigPinB7, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB7, LOW);
  durationB7 = pulseIn (echoPinB7, HIGH);
  distanceB7 = durationB7*0.034/2;

  if (distanceB7 < 5) {  // Change the number for long or short distances. 
    sensorValueB7 = 1;
  } else {
    sensorValueB7 = 0;
  }  
Serial.print("Sensor B7: ");
Serial.println(sensorValueB7);

//Pembacaan nilai sensor B8
int durationB8, distanceB8;
  digitalWrite (trigPinB8, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB8, LOW);
  durationB8 = pulseIn (echoPinB8, HIGH);
  distanceB8 = durationB8*0.034/2;

  if (distanceB8 < 5) {  // Change the number for long or short distances. 
    sensorValueB8 = 1;
  } else {
    sensorValueB8 = 0;
  }  
Serial.print("Sensor B8: ");
Serial.println(sensorValueB8);
}
