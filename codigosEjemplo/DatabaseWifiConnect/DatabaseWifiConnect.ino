
//GLOSARIO DE INCLUDES
#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <Arduino_MKRENV.h> 

 
//INICIALIZADORES
WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  wifiConnection();
  databaseConnection();


}

void loop() {

double presion = ENV.readPressure();
double temperatura = ENV.readPressure();
double humedad = ENV.readHumidity();
double luminosidad = ENV.readIlluminance();
double uva = ENV.readUVA();
double uvb = ENV.readUVB();
delay(5000);
 
}


//METODO CONEXION DATABASE
void databaseConnection(){
  
  IPAddress server_ip(127,0,0,1);   // IP of the MySQL server
  char user[] = "root";              // MySQL user login username
  char password[] = " ";             // MySQL user login password
  int port = 3306;

   Serial.print("Attempting to connect to Database: ");
   Serial.print(server_ip);
  if (conn.connect(server_ip, port, user, password)) {
    delay(1000);
  }
  else
  Serial.println("Connection failed.");
  conn.close();
  
}

//METODO CONEXION WIFI
void wifiConnection() {

  //DEFINICION DE CONSTANTES
  char ssid[] = "Residencial el Bosque 2,4";        // your network SSID (name)
  char pass[] = "CalleTera1A";    // your network password (use for WPA, or use as key for WEP)
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
