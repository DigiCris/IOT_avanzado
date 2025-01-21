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
    String request = ""; // Crear una variable para almacenar la solicitud completa

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

            String htmlL1 = "<!DOCTYPE html><html lang=\"es\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Reset cada 5 segundos</title><meta http-equiv=\"refresh\" content=\"5\"><style>body {font-family: Arial, sans-serif; display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100vh; background-color: #f4f4f4;} .container {text-align: center;} .progress-container {width: 200px; background-color: #e0e0e0; border-radius: 8px; overflow: hidden; margin-top: 20px; height: 30px;} .progress-bar {height: 100%; width: 0; background-color: #76c7c0; transition: width 0.5s;} .number {font-size: 24px; margin-bottom: 10px;}</style></head><body><div class=\"container\"><div class=\"number\" id=\"number\">1024</div><div class=\"progress-container\"><div class=\"progress-bar\" id=\"progress-bar\"></div></div></div><script>const hardcodedValue = ";
            String htmlL2 = String(analogRead(A0));
            String htmlL3 = "; const progressBar = document.getElementById(\"progress-bar\"); const numberDisplay = document.getElementById(\"number\"); function updateProgress() {numberDisplay.textContent = hardcodedValue; const percentage = (hardcodedValue / 1024) * 100; progressBar.style.width = percentage + '%';} updateProgress();</script></body></html>";
            client.print(htmlL1);
            client.print(htmlL2);
            client.println(htmlL3);

            break; // Salir del bucle
          } else {
            // Almacenar la línea actual en la variable 'request'
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