#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <TELEGRAM.h>
#include <config.h>

TELEGRAM tg;

void setup() {
  Serial.begin(115200);
  tg.begin();
  
  WiFi.begin(ssid, pass);
  Serial.print("Conectando...");
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.print("Conectado a ");
  Serial.print(WiFi.localIP());

  configTime(-10800, 0, "pool.ntp.org");
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, HIGH);
}

void loop() {
  tg.updates();
  unsigned long cicloStartMillis = millis();
  if (cicloStartMillis - cicloLastTime > CICLO1MINUTO) {
    cicloLastTime = cicloStartMillis;
  }
}
