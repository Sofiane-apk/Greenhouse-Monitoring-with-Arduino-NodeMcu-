//----------------------------------Library-------------------------
#include <PubSubClient.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "Arduino.h"
#include "SoilMoisture.h"
//---------------------------------Firebase info---------------------
#define FIREBASE_HOST "iot-green-house.firebaseio.com"
#define FIREBASE_AUTH "NvcMFPWJsqHqhmIPii2DwWIdaJGIdwPfex0fs8cl"
//---------------------------------Wifi INFO--------------------------
#define WIFI_SSID "boom"
#define WIFI_PASSWORD "12345678"
//---------------------------------Pin initialisation-----------------
#define RELAYMODULE4CH_PIN_IN1  5  // --- pump
#define RELAYMODULE4CH_PIN_IN2  4  // --- fan
#define RELAYMODULE4CH_PIN_IN3  12 // --- lamp
#define DHTPIN 13                  // --- DHT11
#define DHTTYPE DHT11              // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);
//---------------------------------Variable/Constant-----------------
float p ,t,h;
int soilMoistureValue = 0;
String BtnPumpMan = "0";
String BtnFun = "0";
String BtnLamp="0";
String Manual = "0";
//--------------------------------------Void seup-----------------------------
void setup() {
  //Serial Begin at 9600 Baud
  Serial.begin(115200);
  delay(1000);
     WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
           delay(500);
            Serial.print(".");
         }
          pinMode(RELAYMODULE4CH_PIN_IN1, OUTPUT);
          pinMode(RELAYMODULE4CH_PIN_IN2, OUTPUT);
          pinMode(RELAYMODULE4CH_PIN_IN3, OUTPUT);
          Serial.println ("");
          Serial.println ("WiFi Connected!");
          Serial.println(WiFi.localIP());
     Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
//--------------------------------------Void Loop-----------------------------
void loop() {
  //-----------------------------------Temp/Hum--------------------------------------------
  float h = dht.readHumidity();       // Reading temperature or humidity
  float t = dht.readTemperature();   // Read temperature as Celsius (the default)
   //------------------------------- BTN start pump Manual----------------------------------------
  BtnPumpMan = Firebase.getString("onpump");
  Manual = Firebase.getString("Manual");

       if(Manual == "1"  ) {
        if(BtnPumpMan == "1"){
           Serial.println("Pump active manual");
           digitalWrite(5,LOW);
                              }
        else {
          Serial.println("Pump active manual");
           digitalWrite(5,HIGH);
              }
                                                 }else {
 //---------------------Soil sensor + pump ------------------------------------
soilMoistureValue = analogRead(A0);
  Serial.println(soilMoistureValue);

       if(soilMoistureValue > 500    ) {
           Serial.println("DRY");
           digitalWrite(5,LOW);
             float p = 1;
            Firebase.setInt("/pump", p);
                                   }
       else {
           Serial.println("WET");
           digitalWrite(5, HIGH);
           float p = 0;
           Firebase.setInt("/pump", p);
            }
                                                 }
//------------------------------- BTN Lamp ----------------------------------------
  BtnLamp  = Firebase.getString("onlight");
    
        if(BtnLamp == "1"){
           Serial.println("Lamp  active (ON)");
           digitalWrite(12,LOW);
                              }
        else {
          Serial.println("Lamp desactive (Off");
           digitalWrite(12,HIGH);
              }
//------------------------------- BTN Fun ----------------------------------------
  BtnFun  = Firebase.getString("onfan");
        if(BtnFun  == "1"){
           Serial.println("Fun active (ON)");
           digitalWrite(4,LOW);
                              }
        else {
          Serial.println("Fun desactive (Off");
           digitalWrite(4,HIGH);
              }
//-----------------------Serial Monitor T/H-----------------------------------------
     Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");   //convert integer humidity to string humidity
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("C°");
  String fireTemp = String(t) + String("C°");
  //-----------------------Firebase (T/H) write---------------------------------------------
 if (!(isnan(h) || isnan(t))) {
Firebase.setFloat("t", t);
Firebase.setFloat("h", h);

 Firebase.pushString("/measures/temp", fireTemp);
  Firebase.pushString("/measures/hum", fireHumid);
  }

 //-----------------------Test Sensor read/write-----------------------------
  if (isnan(h) || isnan(t)||isnan(soilMoistureValue)) {         // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor OR soil sensor!"));
    return;
  }
}
