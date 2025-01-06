
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2sRn4EP23"
#define BLYNK_TEMPLATE_NAME         "Clase4"
#define BLYNK_AUTH_TOKEN            "P2FcOpntRfVVCOaFC31QJgBu1vI9lcu8"
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN D2     // Digital pin connected to the DHT sensor

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi";
char pass[] = "12349876";

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);

  int h = dht.readHumidity();
  int t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    Blynk.virtualWrite(V6, t);
    Blynk.virtualWrite(V0, h);

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
  }
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 is: ");
  Serial.println(pinValue);
  digitalWrite(D4,!pinValue);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(2000L, myTimerEvent);
  dht.begin();
  pinMode(D4, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}