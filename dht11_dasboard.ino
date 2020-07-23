#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 4
#define DHTTYPE DHT11

char auth[] = "BBFF-ENYM4Yxj6DyqZoEbPPBAa7nZhHft5N";
char ssid[] = "realme C2I";
char pass[] = "vipikilpo";

DHT dht(DHTPIN,DHTTYPE);
Ubidots client(auth);
unsigned long last = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(20);
  client.wifiConnection(ssid,pass);
}

void loop() {
  if(millis()-last>10000){
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("kelembapan",hum);
    client.add("Temperatur",temp);
    client.sendAll(true);
  }

}
