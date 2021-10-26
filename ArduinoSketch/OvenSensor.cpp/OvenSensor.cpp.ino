#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#include <ArduinoJson.h>
#include <Base64.h>
#include <global.h>
#include <MD5.h>
#include <sha1.h>
#include <WebSocketClient.h>
#include <doxygen.h>
#include <ESP8266.h>

/* SETUP SENSOR DE TEMPERATURA */
#define GPIO_SO   8
#define GPIO_CS   9
#define GPIO_CLK  10
MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO);

#define TEMPO_ENTRE_LEITURAS 5000 //milisegundos

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

/* WIFI SETUP */
char ssid[] = "ForaBolsoasno2.4";
char pass[] = "jupeva98";

char websocketHost[] = "192.168.0.141";
const int websokectPort = 3001;

int status = WL_IDLE_STATUS;
SoftwareSerial Serial1(6, 7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial1.begin(9600);  
  
  WiFi.init(&Serial1);

  if(WiFi.status() == WL_NO_SHIELD){    
    while (true);
  }
  while(status != WL_CONNECTED){
    Serial.write("Conectando a rede wifi: ");
    Serial.write(ssid);
    status = WiFi.begin(ssid, pass);
  }  
  
  Serial.write("Conectado a rede wifi: ");  
  printWifiStatus();

  if (client.connect(websocketHost, websocketPort)) {
      Serial.println("Connected");
    } else {
      Serial.println("Connection failed.");
    }  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.clear();
  lcd.setCursor(0, 0);    
  lcd.print("Temp. Forno:");
  lcd.setCursor(0, 1);  
  float tempCelsius = termopar.readCelsius();
  float tempFarenheiht = termopar.readFarenheit();
  lcd.print(tempCelsius, 1);  
  lcd.print("C");
  lcd.print("|");
  lcd.print(tempFarenheiht, 1);
  lcd.print("F");
  DynamicJsonDocument data(1024);
  data["id"] = "johncooking";
  data["tempCentigrados"] = tempCelsius;
  data["tempFarenheit"] = tempFarenheiht;
  
  webSocketClient.sendData(data);
  
  delay(TEMPO_ENTRE_LEITURAS);
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
