#include <WiFi.h>  
#include <Wire.h>  
#include <HTTPClient.h>  

const char* ssid = "FAMILIA PUERTO";  
const char* password = "Yiyo2024.";  
const char* apiKey = "9LSM2QU1I7A5C1XG";  
const char* server = "http://api.thingspeak.com/update";  

const int ledPin = 2;  
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);  

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");

  Wire.begin(8);  
  Wire.onReceive(receiveEvent);  
}

void loop() {}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    int data = Wire.read();  // Leer los datos enviados por el Arduino
    if (data == 1) {
      digitalWrite(ledPin, HIGH);  // Enciende el LED
    } else if (data == 0) {
      digitalWrite(ledPin, LOW);  // Apaga el LED
    } else {
      enviarThingSpeak(data);
    }
  }
}

// Función para enviar datos a ThingSpeak
void enviarThingSpeak(int temperatura) {
  if (WiFi.status() == WL_CONNECTED) {  
    HTTPClient http;

    // Crear la URL de la solicitud HTTP
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temperatura);
    http.begin(url);

    // Enviar solicitud y verificar el código de respuesta
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("Datos enviados a ThingSpeak: ");
      Serial.println(temperatura);
    } else {
      Serial.print("Error al enviar datos: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Terminar la conexión HTTP
  } else {
    Serial.println("Error: No conectado a WiFi");
  }
}