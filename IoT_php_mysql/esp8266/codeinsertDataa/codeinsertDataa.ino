#include <ESP8266WiFi.h>

//const char* ssid     = "TaoLaGa49";
//const char* password = "longcoi123";
const char* ssid     = "iPhone";
const char* password = "longcoi12345";
//const char* ssid     = "82 LAU 1";
//const char* password = "123456789";
const char* host = "iottechno.com";
float t = 70;
float h  = 25;

void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
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
  Serial.println("MAC: ");
  Serial.println(WiFi.macAddress());
}
void loop() {
  t = t + 0.5;
  h = h + 0.5;
  if (t > 35 || h > 80)
  {
    t = 25;
    h = 70;
  }

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/api/weather/insert.php?temp=" + String(t) + "&hum=" + String(h);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  delay(3000);
}
