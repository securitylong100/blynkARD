#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <String.h>

const char* ssid     = "iPhone";
const char* password = "longcoi12345";
const char* host = "iottechno.com"; //replace it with your webhost url
String url;
int count = 0;
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  digitalWrite(2, 0);
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
    url = "/api/led/read_all.php?id=1";
    count = count + 1;
    Serial.println("Here1");
  }
  else if (count == 1) {
    url = "/api/led/read_all.php?id=2";
    count = count + 1;
    Serial.println("Here2");
  }
  else if (count == 2) {
    url = "/api/led/read_all.php?id=3";
    count = count + 1;
    Serial.println("Here3");
  }
  //code test khong chay
  Serial.print("Requesting URL: ");
  Serial.println(url);
  delay (1000);
  client.println(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");

  if (client.println() != 0)
  {
    Serial.println(String("gui tin hien di OK"));
  }
  else
  {
    Serial.println(String("Gui tin di NG"));
    return;
  }
  delay(500);

  char abc[] = "";
  char strincat[] = "";
  String a ;
  while (client.available())
  {

    a  = client.readStringUntil('\r');
    int size = a.length() + 1;
    a.toCharArray(abc, size);
    //code tu Khoi.
    //end code
    strncpy(strincat, abc + 0, 47);
    strincat[47] = '\0';
    Serial.println(strincat);
  }
  delay (5000);
  String section = "header";
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    if (section == "header") { // headers..
      if (line == "\n") { // skips the empty space at the beginning
        section = "json";
      }
    }
    else if (section == "json") { // print the good stuff
      section = "ignore";
      String result = line.substring(1);
      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      //   char json[] = "{\"time\":\"on\"}";
      // char json[] = "{\"success\":1,\"led\":[{\"id\":\"1\",\"status\":\"on\"}]}";
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);

      if (!json_parsed.success()) {
        Serial.println("parseObject() failed");
        return;
      }
      String led = ""; //json_parsed["led"][0]["status"];

      if (count == 1)
      {
        if (led == "on") {
          digitalWrite(LED_BUILTIN, 1);
          delay(100);
          Serial.println("D1 is On..!");
        }
        else if (led == "off") {
          digitalWrite(LED_BUILTIN, 0);
          delay(100);
          Serial.println("D1 is Off..!");
        }
      }
      else if (count == 2) {
        if (led == "on") {
          digitalWrite(2, 1);
          Serial.println("D2 is On..!");
        }
        else if (led == "off") {
          digitalWrite(2, 0);
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

}
