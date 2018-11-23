#include <ESP8266WiFi.h>
#include <SPI.h>
#include <String.h>
//const char* ssid     = "iPhone";
//const char* password = "longcoi12345";
const char* ssid     = "TaoLaGa49";
const char* password = "longcoi123";
void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
   digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
void loop()
{

}
