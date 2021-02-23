#include <Arduino_MKRENV.h>

void setup() {
 // Initialize Serial and wait for port to open:
 Serial.begin(9600);
 // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
 delay(1500);
 
 if (!ENV.begin()) {
  Serial.println("Failed to initialize MKR ENV shield!");
  while(1);
 }
}


void loop() {
 Serial.print("--------------------------\n");
 //PRESION
 Serial.print("Pressure    = ");
 Serial.print(ENV.readPressure());
 Serial.println(" kPa");

 //TEMPERATURA
 Serial.print("Temperature = ");
 Serial.print(ENV.readTemperature());
 Serial.println(" °C");
 
 //HUMEDAD
 Serial.print("Humidity    = ");
 Serial.print(ENV.readHumidity());
 Serial.println(" %");

 //LUMINOSIDAD
 Serial.print("Lux .       = ");
 Serial.println(ENV.readIlluminance());

 Serial.print("--------------------------\n\n");
 delay(5000);
}
