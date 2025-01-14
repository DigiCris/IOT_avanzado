#include <ESP8266WiFi.h>
#include <ArduinoWiFiServer.h>

#ifndef STASSID
#define STASSID "Redmi"
#define STAPSK "12349876"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ArduinoWiFiServer server(80); // Cambiar el puerto a 80 para HTTP

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();

  IPAddress ip = WiFi.localIP();
  Serial.println();
  Serial.println("Connected to WiFi network.");
  Serial.print("To access the server, connect with a web browser to ");
  Serial.print(ip);
  Serial.println(" 80");
}

void loop() {
  WiFiClient client = server.available(); // Comprobar si hay un cliente conectado

  if (client) { // Si hay un cliente conectado

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<body>");
    client.println("<h1>Hello World</h1>"); // Mensaje "Hello World"
    client.println("</body>");
    client.println("</html>");
    client.stop(); // Cerrar la conexión
    Serial.println("Client disconnected");
  }
}