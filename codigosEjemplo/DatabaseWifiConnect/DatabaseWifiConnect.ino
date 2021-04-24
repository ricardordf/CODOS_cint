
//GLOSARIO DE INCLUDES
#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Arduino_MKRENV.h> 
#include <String.h> 
 
//INICIALIZADORES
WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;
char INSERT_SQL[] = "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (1, 'Presion atmosferica', %d);";
//char query[128] = [];


void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  wifiConnection();
  databaseConnection();
  
  cursor = new MySQL_Cursor(&conn);
}


void loop() {

double presion = ENV.readPressure();
double temperatura = ENV.readPressure();
double humedad = ENV.readHumidity();
double luminosidad = ENV.readIlluminance();
double uva = ENV.readUVA();
double uvb = ENV.readUVB();

//String presion2 = String(presion, 4);
//char query[]= "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES (1, 'Presion atmosferica',4);";
//sprintf(query, INSERT_SQL, presion);    
int id = 1;
String n = "Presion Atmosferica";
                                                      
String insert = String ( "INSERT INTO bdrdelgado.datos_sensores (id_sensor, tipo, valor) VALUES( " ) + id + ", '" + n + "', " + presion + ")";

Serial.print(insert);

delay(5000);

if (conn.connected()){
    cursor->execute(insert);
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
