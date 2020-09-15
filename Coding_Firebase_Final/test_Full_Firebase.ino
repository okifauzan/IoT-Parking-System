#include <FirebaseArduino.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>

#include <ESP8266WiFi.h>

#define FIREBASE_HOST "test-skripsi-aa13e.firebaseio.com"
#define FIREBASE_AUTH "isvAA9RPJ4VAopjTb6YYJswpzdHFF353Nu9lPAg1"

#define WIFI_SSID "Galaxy A8"                                            
#define WIFI_PASSWORD "22222222"      
#include <SoftwareSerial.h>

String A1_kirim, A2_kirim, A3_kirim, A4_kirim, A5_kirim, A6_kirim, A7_kirim, A8_kirim;
String B1_kirim, B2_kirim, B3_kirim, B4_kirim, B5_kirim, B6_kirim, B7_kirim, B8_kirim;
SoftwareSerial SerialESP(13,15);

void setup() {
  Serial.begin(9600);
  SerialESP.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                    
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              //Start reading sensor value
}

void loop() {
  String Data = SerialESP.readString();
  Serial.print(Data);
  int myString = Data.length()+1;
  char char_array[myString];
  Data.toCharArray(char_array,myString);
  int A1 = Data[0]; //slot A1
  if (A1 == 49){
    A1_kirim = "Slot A1: Terisi";
  }
  else{
    A1_kirim = "Slot A1: Kosong";
  }
  int A2 = Data[1]; //slot A2
  if (A2 == 49){
    A2_kirim = "Slot A2: Terisi";
  }
  else{
    A2_kirim = "Slot A2: Kosong";
  }
  int A3 = Data[2]; //slot A3
  if (A3 == 49){
    A3_kirim = "Slot A3: Terisi";
  }
  else{
    A3_kirim = "Slot A3: Kosong";
  }
  int A4 = Data[3]; //slot A4
  if (A4 == 49){
    A4_kirim = "Slot A4: Terisi";
  }
  else{
    A4_kirim = "Slot A4: Kosong";
  }
  int A5 = Data[4]; //slot A5
  if (A5 == 49){
    A5_kirim = "Slot A5: Terisi";
  }
  else{
    A5_kirim = "Slot A5: Kosong";
  }
  int A6 = Data[5]; //slot A6
  if (A6 == 49){
    A6_kirim = "Slot A6: Terisi";
  }
  else{
    A6_kirim = "Slot A6: Kosong";
  }
  int A7 = Data[6]; //slot A7
  if (A7 == 49){
    A7_kirim = "Slot A7: Terisi";
  }
  else{
    A7_kirim = "Slot A7: Kosong";
  }
  int A8 = Data[7]; //slot A8
  if (A8 == 49){
    A8_kirim = "Slot A8: Terisi";
  }
  else{
    A8_kirim = "Slot A8: Kosong";
  }
  int B_1 = Data[8]; //slot B1
  if (B_1 == 49){
    B1_kirim = "Slot B1: Terisi";
  }
  else{
    B1_kirim = "Slot B1: Kosong";
  }
  int B2 = Data[9]; //slot B2
  if (B2 == 49){
    B2_kirim = "Slot B2: Terisi";
  }
  else{
    B2_kirim = "Slot B2: Kosong";
  }
  int B3 = Data[10]; //slot B3
  if (B3 == 49){
    B3_kirim = "Slot B3: Terisi";
  }
  else{
    B3_kirim = "Slot B3: Kosong";
  }
  int B4 = Data[11]; //slot B4
  if (B4 == 49){
    B4_kirim = "Slot B4: Terisi";
  }
  else{
    B4_kirim = "Slot B4: Kosong";
  }
  int B5 = Data[12]; //slot B5
  if (B5 == 49){
    B5_kirim = "Slot B5: Terisi";
  }
  else{
    B5_kirim = "Slot B5: Kosong";
  }
  int B6 = Data[13]; //slot B6
  if (B6 == 49){
    B6_kirim = "Slot B6: Terisi";
  }
  else{
    B6_kirim = "Slot B6: Kosong";
  }
  int B7 = Data[14]; //slot B7
  if (B7 == 49){
    B7_kirim = "Slot B7: Terisi";
  }
  else{
    B7_kirim = "Slot B7: Kosong";
  }
  int B8 = Data[15]; //slot B8
  if (B8 == 49){
    B8_kirim = "Slot B8: Terisi";
  }
  else{
    B8_kirim = "Slot B8: Kosong";
  }
  Firebase.setString("Parkir 1/A1", A1_kirim);
  Firebase.setString("Parkir 1/A2", A2_kirim);
  Firebase.setString("Parkir 1/A3", A3_kirim);
  Firebase.setString("Parkir 1/A4", A4_kirim);
  Firebase.setString("Parkir 1/A5", A5_kirim);
  Firebase.setString("Parkir 1/A6", A6_kirim);
  Firebase.setString("Parkir 1/A7", A7_kirim);
  Firebase.setString("Parkir 1/A8", A8_kirim);
  Firebase.setString("Parkir 1/B1", B1_kirim);
  Firebase.setString("Parkir 1/B2", B2_kirim);
  Firebase.setString("Parkir 1/B3", B3_kirim);
  Firebase.setString("Parkir 1/B4", B4_kirim);
  Firebase.setString("Parkir 1/B5", B5_kirim);
  Firebase.setString("Parkir 1/B6", B6_kirim);
  Firebase.setString("Parkir 1/B7", B7_kirim);
  Firebase.setString("Parkir 1/B8", B8_kirim);
  if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  //delay(4000);
}
