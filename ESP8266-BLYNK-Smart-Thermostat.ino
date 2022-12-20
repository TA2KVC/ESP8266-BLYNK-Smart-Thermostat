#define BLYNK_TEMPLATE_ID "xxxxxxxxxxxxxxxx"
#define BLYNK_DEVICE_NAME "VOLKAN Smart Thermostat"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "AAAAAAAAA";
char pass[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

#define DHTPIN 0
#define DHTTYPE DHT11
const int role = 13;
DHT dht(DHTPIN, DHTTYPE);

float humDHT = 0;
float tempDHT = 0;
int Vala = 0;
int VPin = 0;
WidgetLED LED(V6);
WidgetLED NODE(V2);

BLYNK_WRITE(V0)
{
  int Val = param.asInt();
  Vala = Val;
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(role, OUTPUT);
  digitalWrite(role, HIGH);
  NODE.off();
  humDHT = dht.readHumidity();
  tempDHT = dht.readTemperature();
}

void loop()
{
  Blynk.run();
  delay(2000);
  humDHT = dht.readHumidity();
  tempDHT = dht.readTemperature();
  if ( Vala > tempDHT){
    digitalWrite(role, LOW);
    VPin=1;
    Blynk.virtualWrite(V7, VPin);
    LED.on();
    delay(2000);
  }
  else if (Vala+0.5 < tempDHT) {
    digitalWrite(role, HIGH);
    VPin=0;
    Blynk.virtualWrite(V7, VPin);
    LED.off(); 
    delay(2000);
  }
  Blynk.virtualWrite(V4, tempDHT);
  Blynk.virtualWrite(V5, humDHT);
  NODE.on();
}

 
BLYNK_WRITE(V7)
{
  int pinValue = param.asInt();
  VPin = pinValue;
  if (VPin == 1) {
    Blynk.virtualWrite(V0, 35);
    Vala = 35;
  } 
  else if (VPin == 0){
    Blynk.virtualWrite(V0, 15);
    Vala = 15;
  }
}
