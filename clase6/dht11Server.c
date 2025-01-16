#include <ESP8266WiFi.h>
#include "DHT.h"

#ifndef STASSID
#define STASSID "Redmi"
#define STAPSK "12349876"
#endif

#define DHTPIN D2 


#define DHTTYPE DHT11

const char* ssid = "Redmi";//STASSID;
const char* password = STAPSK;

WiFiServer server(80); // Servidor en el puerto 80

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();
  Serial.println();
  Serial.print("Connected to WiFi. Access the server at: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);
  WiFiClient client = server.available(); // Comprobar si hay un cliente conectado

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }


  if (client) {
    String currentLine = ""; // Almacenar la solicitud
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Leer carácter
        Serial.write(c); // Mostrar en el monitor serie
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Enviar respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<html lang='en'> <head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Temperatura y Humedad</title> </head> <body> <p> Temperatura:");
            client.print(t);
            client.print("°C </p> <p> Humedad: ");
            client.print(h);
            client.println("% </p> </body> </html>");
            break; // Salir del bucle
          } else {
            currentLine = ""; // Reiniciar línea
          }
        } else if (c != '\r') {
          currentLine += c; // Agregar carácter a la línea actual
        }
      }
    }
    client.stop(); // Cerrar conexión
    Serial.println("Client disconnected");
  }
}