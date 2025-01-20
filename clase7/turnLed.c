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
  pinMode(LED_BUILTIN, OUTPUT);
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
    String currentLine = ""; // Crear una línea para almacenar la solicitud
    String request = ""; // Crear una variable para almacenar la solicitud completa

    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Leer el carácter entrante
        Serial.write(c); // Mostrarlo en el monitor serie
        if (c == '\n') { // Si se recibe una nueva línea
          if (currentLine.length() == 0) {
            if (request.indexOf("GET /on") != -1) {
              digitalWrite(LED_BUILTIN, LOW); // Encender LED
            }
            if (request.indexOf("GET /off") != -1) {
              digitalWrite(LED_BUILTIN, HIGH); // Apagar LED
            }
            String html = "<!DOCTYPE html><html lang=\"es\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Control LED</title><style>body {font-family: Arial, sans-serif; display: flex; justify-content: center; align-items: center; height: 100vh; background-color: #f4f4f4;} .container {text-align: center;} button {padding: 15px 30px; font-size: 16px; margin: 10px; border: none; border-radius: 5px; cursor: pointer; transition: background-color 0.3s;} .on {background-color: #4CAF50; color: white;} .on:hover {background-color: #45a049;} .off {background-color: #f44336; color: white;} .off:hover {background-color: #e53935;}</style></head><body><div class=\"container\"><h1>Control de LED</h1><form action=\"/on\" method=\"get\"><button type=\"submit\" class=\"on\">Prender LED</button></form><form action=\"/off\" method=\"get\"><button type=\"submit\" class=\"off\">Apagar LED</button></form></div></body></html>";
            client.println(html);
            break; // Salir del bucle
          } else {
            request += currentLine + "\n"; 
            currentLine = ""; // Reiniciar la línea actual
          }
        } else if (c != '\r') {
          currentLine += c; // Agregar carácter a la línea actual
        }
      }
    }
    client.stop(); // Cerrar la conexión
    Serial.println("Client disconnected");
  }
}