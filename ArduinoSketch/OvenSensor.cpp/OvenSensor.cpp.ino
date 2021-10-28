#include <max6675.h>
#include <LiquidCrystal.h>
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>

/* SETUP SENSOR DE TEMPERATURA */
#define GPIO_SO   8
#define GPIO_CS   9
#define GPIO_CLK  10
MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO);

#define DEBUG_SERIAL Serial

/* LCD SETUP */
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

/* WIFI SETUP */
#define ssid "ForaBolsoasno2.4"
#define pass "jupeva98"

WiFiEspClient wifiClient;
int status = WL_IDLE_STATUS;
SoftwareSerial Serial1(6, 7); //Serial setup for ESP8266

/* WEBSOCKET SETUP */
const char wsHost[] = "192.168.0.141";
const char wsPath[] = "/";
const int port = 3001;
WebSocketClient client = WebSocketClient(wifiClient, wsHost, port);

float tempCelsius = 0;
float tempFarenheit = 0;

StaticJsonDocument<64> doc;

bool connected = false;
unsigned long messageInterval = 5000;
unsigned long lastUpdate = millis();

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial1.begin(9600);

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.write("Conectando a rede wifi: ");
    Serial.write(ssid);
    status = WiFi.begin(ssid, pass);
  }
  
  Serial.write("Conectado a rede wifi: ");
  printWifiStatus();
}

void loop() {
  // put your main code here, to run repeatedly:
  tempCelsius = termopar.readCelsius();
  tempFarenheit = termopar.readFarenheit();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. Forno:");
  lcd.setCursor(0, 1);
  lcd.print(tempCelsius, 1);
  lcd.print("C");
  lcd.print("|");
  lcd.print(tempFarenheit, 1);
  lcd.print("F");

  doc["id"] = "johncooking";
  doc["tempCentigrados"] = tempCelsius;
  doc["tempFarenheit"] = tempFarenheit;  

  char msg[128];
  serializeJson(doc, msg);
  //msg = escapeQuotes(&msg);
  Serial.print(msg);
  
  client.begin();    
  if (client.connected()) {    
    client.beginMessage(TYPE_TEXT);
    client.print(msg);
    client.endMessage();
  }
  
  delay(5000);
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
