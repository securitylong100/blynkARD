
#include <ESP8266WiFi.h>

const char* ssid = "TaoLaGa49";
const char* password = "longcoi123";

IPAddress staticIP(192, 168, 94, 30);
IPAddress gateway(192, 168, 94, 1);
IPAddress subnet(255, 255, 255, 0);

void setup(void)
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s \n", ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  pinMode(LED_BUILTIN, OUTPUT);

}
void connectwifi()
{
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

}
void loop() {
  connectwifi();
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(500);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(500);
}
