#include <DHT.h>
#include "BluetoothSerial.h"
#include<FirebaseESP32.h>
#include<WiFi.h>
#include<EEPROM.h>

#define WIFI_SSID "Supreeth's S23 Ultra"
#define WIFI_PASSWORD "Supreeth1802"
#define FIREBASE_APIKEY "yPWej6fJ2YGqNQbD6mLB8uPJ9p0lKvnGcHvIhtlJ"
#define HOST_ID "supreethfirebase-default-rtdb.firebaseio.com"
#define trig 18
#define echo 19
#define ENGINE 5
#define EEPROM_SIZE 1

BluetoothSerial SerialBT;
DHT dht1(4,DHT11);
FirebaseData FirebaseDataObj;

unsigned long int t1;
int distance;
int ir,temp,rain;
byte x=0;
int wb;
String ch,ch1;
void setup() {
  EEPROM.begin(EEPROM_SIZE);
  wb= EEPROM.read(0);
  Serial.begin(9600);
  if(wb==0){
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    Serial.print("Connecting To ");
    Serial.println(WIFI_SSID);
    while(WiFi.status()!= WL_CONNECTED)
    {
      Serial.print(".");
      delay(500);  
    }
    Serial.println("\n CONNECTED");
    Firebase.begin(HOST_ID,FIREBASE_APIKEY);
  
    Firebase.setReadTimeout(FirebaseDataObj,60000);
    
    Firebase.setwriteSizeLimit(FirebaseDataObj,"tiny");
  }
  if(wb==1){
    SerialBT.begin("ESP32_Supreeth");
    Serial.println("The device started, now you can pair it with bluetooth");
   }
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(25,INPUT);
  pinMode(13,INPUT);
  pinMode(34, INPUT);
  pinMode(ENGINE, OUTPUT);
  Serial.begin(115200);

  dht1.begin();
  xTaskCreate(dhtsense, "dhtsense",3000,NULL,1,NULL);
  xTaskCreate(rainsense, "rainsense",1000,NULL,1,NULL);
  xTaskCreate(ultrasense, "ultrasense",1000,NULL,1,NULL);
  attachInterrupt(digitalPinToInterrupt(25),irsense,LOW);
}
