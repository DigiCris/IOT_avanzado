#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  // Mensaje inicial en el LCD
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");
  
  // Configuración de WiFi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Redmi", "12349876");
  
  // Espera por conexión WiFi
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
}

void loop() {
  // Espera por conexión WiFi
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://comunyt.co/dolar.json")) {  // HTTP
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        String payload = http.getString();

        // Parse JSON object
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          client.stop();
          return;
        } else {
          // Obtener el precio de compra
          String compra;
          if (doc["compra"].is<double>()) {
            compra = String(doc["compra"].as<double>(), 2); // Si es un número con 2 decimales
          } else {
            compra = doc["compra"].as<String>(); // Si es un String
          }

          // Mostrar el precio en el LCD
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Dolar Compra:");
          lcd.setCursor(0, 1);
          lcd.print(compra);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }

  delay(10000); // Esperar 10 segundos antes de la siguiente consulta
}