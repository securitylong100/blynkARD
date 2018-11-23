#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <String.h>

const int kNetworkTimeout = 30 * 1000;
const int kNetworkDelay = 1000;
const char* ssid     = "iPhone";
const char* password = "longcoi12345";
const char* host = "iottechno.com"; //replace it with your webhost url
String url;
int count = 0;
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(16, OUTPUT);//connect pin2
  pinMode(0, OUTPUT); //connect pin 8
  pinMode(3, OUTPUT); //connect pin 0
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(16, 0);
  digitalWrite(0, 0);
  digitalWrite(3, 0);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
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
  digitalWrite(LED_BUILTIN, 1);
  delay(500);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
}
void loop() {

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  if (count == 0) {
    url = "/thuy/api/led/read_all.php?id=1";
    count = count + 1;
    Serial.println("Here1");
  }
  else if (count == 1) {
    url = "/thuy/api/led/read_all.php?id=2";
    count = count + 1;
    Serial.println("Here2");
  }
  else if (count == 2) {
    url = "/thuy/api/led/read_all.php?id=3";
    count = count + 1;
    Serial.println("Here3");
  }
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);
  String section = "header";
  int i = 0;
  while (client.available()) {
    String line = client.readStringUntil('\n');
     // Serial.print(line);
    i = i+1;
     // delay(500);
      // Serial.print(String(i));
    // we’ll parse the HTML body here
    if (i== 11)  { // print the good stuff
      i =1;
      String result = line;
     // Serial.print(result);
      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<100> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      String led = json_parsed["led"][0]["status"];

      if (count == 1) {
        if (led == "on") {
          digitalWrite(16, 1);
          delay(100);
          Serial.println("D1 is On..!");
        }
        else if (led == "off") {
          digitalWrite(16, 0);
          delay(100);
          Serial.println("D1 is Off..!");
        }
      }
      else if (count == 2) {
        if (led == "on") {
          digitalWrite(0, 1);
          Serial.println("D2 is On..!");
        }
        else if (led == "off") {
          digitalWrite(0, 0);
          Serial.println("D2 is Off..!");
        }
      }
      else if (count == 3) {
        if (led == "on") {
          digitalWrite(3, 1);
          Serial.println("D3 is On..!");
        }
        else if (led == "off") {
          digitalWrite(3, 0);
          Serial.println("D3 is Off..!");
        }
        count = 0;
      }

      if (count == 3)
        count = 0;

    }
  }
  Serial.println();
  Serial.println("closing connection");
//  delay(300);
}
