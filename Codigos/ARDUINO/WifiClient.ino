#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const char*     ssid     = "ssid";  //aca insertar el ssid del wifi.
const char*     password = "pswd";  //aca insertar el password del wifi.

const char*     host = "192.168.2.19";   //Colocar IP de la computadora que posea la aplicación de QT.
const uint16_t  port = 83;         //Mismo que en el QT.

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);

  // Conexion al wifi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.print("Wait for WiFi... ");

  while ( WiFiMulti.run() != WL_CONNECTED )
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {
  // Usando clase WiFiClient para conexiones TCP
  WiFiClient client;

  //-------Intento conectarme al server--------------------------
  if ( !client.connect(host, port) ) 
  {  //Si la conexión falla
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  //-------------------------------------------------------------

  //-------Envío mensaje al servidor-----------------------------
  if ( Serial.available() > 0 )
    client.print(Serial.readString());       
  //-------------------------------------------------------------

  //---------Leo lo que el servidor me tenga que decir-----------
  String line = client.readStringUntil('\r');
  for ( int i = 0 ; i < line.length() ; i++ )
  { //Imprimo de a un caracter a la vez
    if ( i == line.length() - 1 )
      Serial.println( line[i] );
    else
      Serial.print( line[i] );
    delay(10);
  }  

  //--Me desconecto-----------------------
  client.stop();

  //--Delay antes de repetir--------------
  Serial.println("wait 5 sec...");
  delay(4000);
}
