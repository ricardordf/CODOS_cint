
//GLOSARIO DE INCLUDES
#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Arduino_MKRENV.h> 
#include <String.h> 
#include <avr/dtostrf.h>

 
//INICIALIZADORES
WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;


void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  wifiConnection();
  databaseConnection();
  
  cursor = new MySQL_Cursor(&conn);

  if (!ENV.begin()) {
  Serial.println("Failed to initialize MKR ENV shield!");
  while(1);
 }
 
}


void loop() {

float presion = ENV.readPressure();
float temperatura = ENV.readTemperature();
float humedad = ENV.readHumidity();
float luminosidad = ENV.readIlluminance();
float uva = ENV.readUVA();
float uvb = ENV.readUVB();
float uvi = ENV.readUVIndex();
//float co2 = .... SENSOR CO2 falta.

//INSERT PRESION
char INSERT_SQL1[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (1, 'Presion atmosferica', %s);";
char pres[10];
char query1[128];
dtostrf(presion, 1, 1, pres);
sprintf(query1, INSERT_SQL1, pres); 

//INSERT TEMPERATURA
char INSERT_SQL2[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (2, 'Temperatura', %s);";
char tempF[10];
char query2[128];
dtostrf(temperatura, 1, 1, tempF);
sprintf(query2, INSERT_SQL2, tempF);      

//INSERT HUMEDAD
char INSERT_SQL3[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (3, 'Humedad', %s);";
char hum[10];
char query3[128];
dtostrf(humedad, 1, 1, hum);
sprintf(query3, INSERT_SQL3, hum);  

//INSERT LUMINOSIDAD
char INSERT_SQL4[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (4, 'Luminosidad', %s);";
char lux[10];
char query4[128];
dtostrf(luminosidad, 1, 1, lux);
sprintf(query4, INSERT_SQL4, lux); 

//INSERT UVA
char INSERT_SQL5[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (5, 'Rayos UVA', %s);";
char uvas[10];
char query5[128];
dtostrf(uva, 1, 1, uvas);
sprintf(query5, INSERT_SQL5, uvas); 

//INSERT UVB
char INSERT_SQL6[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (6, 'Rayos UVB', %s);";
char uvbs[10];
char query6[128];
dtostrf(uvb, 1, 1, uvbs);
sprintf(query6, INSERT_SQL6, uvbs); 

//INSERT UVI
char INSERT_SQL7[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (7, 'UV Index', %s);";
char uvis[10];
char query7[128];
dtostrf(uvi, 1, 1, uvis);
sprintf(query7, INSERT_SQL7, uvis); 

/*
///INSERT CO2
char INSERT_SQL8[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (8, 'CO2', %s);";
char co2s[10];
char query8[128];
dtostrf(co2, 1, 1, co2s);
sprintf(query8, INSERT_SQL8, co2s);
*/



delay(5000);

if (conn.connected()){
    cursor->execute(query1);
    cursor->execute(query2);
    cursor->execute(query3);
    cursor->execute(query4);
    cursor->execute(query5);
    cursor->execute(query6);
    cursor->execute(query7);
    //cursor->execute(query8);
  
}
 
}


//METODO CONEXION DATABASE
void databaseConnection(){
  
  IPAddress server_addr(2,139,176,212);   // IP of the MySQL server
  char user[] = "db_rdelgado";              // MySQL user login username
  char password[] = "Prueba1234$";             // MySQL user login password

   Serial.print("Attempting to connect to Database: ");
   Serial.print(server_addr);
  
  if (conn.connect(server_addr, 3306, user, password)) {
    Serial.println("Conectado a la base de datos!\n");
  }
  else{
  Serial.println("Connection failed.");
  conn.close();
  }
  
}

//METODO CONEXION WIFI
void wifiConnection() {

  //DEFINICION DE CONSTANTES
  char ssid[] = "Juan-RN7";        // your network SSID (name)
  char pass[] = "hola1234";    // your network password (use for WPA, or use as key for WEP)
  int keyIndex = 0;            // your network key index number (needed only for WEP)
  int status = WL_IDLE_STATUS;

   // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
   // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  //status = WiFi.begin(ssid);
  status = WiFi.begin(ssid, pass);

  // wait 10 seconds for connection:
  delay(10000);
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("---------------------------------\n");

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("---------------------------------\n\n");
}
