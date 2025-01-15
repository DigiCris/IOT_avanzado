#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Redmi"
#define STAPSK "12349876"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80); // Servidor en el puerto 80

void setup() {
  Serial.begin(9600);
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
  WiFiClient client = server.available(); // Comprobar si hay un cliente conectado

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
            client.println("<!DOCTYPE HTML><html><body><h1>Hello World</h1></body></html>");
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