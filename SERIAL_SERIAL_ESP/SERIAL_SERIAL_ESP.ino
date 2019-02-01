#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseCloudMessaging.h>
#include <Firebase.h>
#include <FirebaseHttpClient.h>
#include <FirebaseArduino.h>
#include <FirebaseError.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#define FIREBASE_HOST "smart-cylinder-78129.firebaseio.com"
#define FIREBASE_AUTH "TV8AyTBw9UVIIK4sy9Jy9r2bTHO54B2m2gmG3TNT"
#define WIFI_SSID "vivo 1714"//"BVRIT-ATL"I AM DUM"
#define WIFI_PASSWORD "saicharan"//"BvritAtl@Nsp"12345678

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  lcd.begin();

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
int data;
int sensor;
void loop() {
 // run over and over
 if (Serial.available()>0)
  {
    data=Serial.read();
    Serial.println(data);
  }
  sensor=analogRead(A0);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Weight :");
 lcd.print(data);
 lcd.setCursor(3,1);
 lcd.print("Gas :");
 lcd.print(sensor);
  Firebase.set("SmartCylinder/weight", data );
   yield();
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
   
  } 
  Firebase.set("SmartCylinder/Gas", sensor );
  // handle error
 if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    
  } 
  delay(500);
  
}
