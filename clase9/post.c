#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "Redmi"
#define STAPSK "12349876"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi network.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client; // Crear un cliente WiFi
    String postData = "temperature=25"; // Valor a enviar

    http.begin(client, "http://comunyt.co/post.php"); // Usar el cliente WiFi
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Tipo de contenido

    // Enviar la solicitud POST
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString(); // Obtener la respuesta
      Serial.println(httpResponseCode); // Código de respuesta
      Serial.println(response); // Imprimir respuesta
    } else {
      Serial.print("Error en la solicitud POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Cerrar la conexión
  } else {
    Serial.println("Error en la conexión WiFi");
  }

  delay(10000); // Esperar 10 segundos
}