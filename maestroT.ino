#include <Wire.h>  

const int sensorPin = A0;    

void setup() {
  Wire.begin();  
  Serial.begin(9600);  
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Leer valor del sensor
  float voltage = sensorValue * (5.0 / 1023.0);  // Convertir a voltaje
  float temperature = voltage * 100;  // Obtener temperatura en grados Celsius
  
  Serial.print("Temperatura: ");
  Serial.println(temperature);

  // Enviar la temperatura actual al ESP32
  Wire.beginTransmission(8);
  Wire.write((int)temperature); 
  Wire.endTransmission();


  if (temperature > 21) {
    Wire.beginTransmission(8);
    Wire.write(1);  // Enviar 1 para encender LED
    Wire.endTransmission();
  } else {
    Wire.beginTransmission(8);
    Wire.write(0);  // Enviar 0 para apagar LED
    Wire.endTransmission();
  }
  delay(1000);
}
