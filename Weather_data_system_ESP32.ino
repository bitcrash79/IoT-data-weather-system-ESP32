#define BLYNK_TEMPLATE_ID "TMPL3tscnBuVO"
#define BLYNK_TEMPLATE_NAME "weather data system"
#define BLYNK_AUTH_TOKEN "kJfRWHj05tmwRPsXj_8B1ijHJOAiipN8"
#include "DHTesp.h"
#include "BlynkSimpleEsp32.h"

const int sensorPin = 13;

BlynkTimer timer;

DHTesp dht;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";


void setup(){
  Serial.begin(115200);
  dht.setup(sensorPin, DHTesp::DHT22);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendDHTData);
}

void sendDHTData() {
  float t = dht.getTemperature();
  float h = dht.getHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
}

void loop() {
  Blynk.run();
  timer.run();
}