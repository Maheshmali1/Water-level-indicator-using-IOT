#include <Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "J1AdSZ7qObKXFAEwLO4SlK4QJ4I8dzya";//Enter your Auth token
char ssid[] = "HUAWEI-AD47";//Enter your WIFI name
char pass[] = "Mahimali1@h";//Enter your WIFI password
BlynkTimer timer;
bool pinValue = 0;
#define trig D3
#define echo D4
#define relay D5
void setup() {
  pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 pinMode(relay, OUTPUT);
 Wire.begin(D2, D1);
 Serial.begin(115200);
 Serial.print("Connecting to "); 
 Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) { 
 delay(500);
 Serial.print(".");
}
 Serial.println(""); 
 Serial.println("WiFi connected");
 Blynk.begin(auth, ssid, pass);
 timer.setInterval(10L, Wlevel);
 digitalWrite(relay, HIGH);
}
BLYNK_WRITE(V0) {
 pinValue = param.asInt();
}
void loop() {
 Blynk.run();
 timer.run();
}
void Wlevel() {
 if (pinValue == 1) {
 digitalWrite(relay, HIGH); 
 Serial.print("Motor is ON ");
 } 
 else if (pinValue == 0) {
 digitalWrite(relay, LOW);
 Serial.print("Motor is OFF");
 }
 digitalWrite(trig, LOW);
 delayMicroseconds(4);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);
 long t = pulseIn(echo, HIGH);
 long cm = t * 0.034 / 2;
 Blynk.virtualWrite(V1, cm);
 Serial.println(cm);
}
