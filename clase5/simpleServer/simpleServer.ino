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
    String currentLine = ""; // Crear una línea para almacenar la solicitud
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Leer el carácter entrante
        Serial.write(c); // Mostrarlo en el monitor serie
        if (c == '\n') { // Si se recibe una nueva línea
          // Si la línea actual está vacía, significa que se ha terminado la solicitud
          if (currentLine.length() == 0) {
            // Enviar la respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<body>");
            client.println("<h1>Hello World</h1>"); // Mensaje "Hello World"
            client.println("</body>");
            client.println("</html>");
            break; // Salir del bucle
          } else { // Si la línea no está vacía, continuar leyendo
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