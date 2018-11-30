#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <String.h>
#include <SD.h>
int button = 16; // là tx gắn d2
int switchK = 5;  //switch change kênh
int led8 = 0; //gan d8
int led = LED_BUILTIN;
int led5 = 14;
int led6 = 12;
int led7 = 13;
int lednetwork = 4;

//const char* ssid     = "iPhone";
//const char* password = "longcoi12345";
const char* ssid     = "TaoLaGa49";
const char* password = "longcoi123";
const char* ssid_web = "iPhone";
const char* password_web = "longcoi12345";
const String ftp_account = "ftpin";
const String ftp_passwords = "ftppass";
const char *server = "192.168.145.7";
String fileName = "arduino.csv";
String Folder_name = "459qb";

WiFiClient client;
WiFiClient dclient;
String data1, data2 ;
char outCount;
char outBuf[128];
boolean debug = true;
boolean upload = true;
String StatusLed;
long countMiliis = millis();
const char* host = "iottechno.com";
String url;
int count = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode (switchK, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode (led5, OUTPUT);
  pinMode (led6, OUTPUT);
  pinMode (led7, OUTPUT);
  pinMode(lednetwork, OUTPUT);
  delay(100);
  Serial.print("Connecting to ");
  if (digitalRead(switchK) == HIGH)
  {
    Serial.println(ssid);
    WiFi.begin(ssid, password);
  }
  if (digitalRead(switchK) == LOW)
  {
    Serial.println(ssid_web);
    WiFi.begin(ssid_web, password_web);
  }
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
    digitalWrite(lednetwork, HIGH);
    delay (250);
    digitalWrite(lednetwork, LOW);
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
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  delay(500);
}
void efail() {
  byte thisByte = 0;

  client.println(F("QUIT"));

  while (!client.available()) delay(1);

  while (client.available()) {
    thisByte = client.read();
    Serial.write(thisByte);
  }

  client.stop();
  Serial.println(F("Command disconnected"));
}  // efail
byte eRcv()
{
  byte respCode;
  byte thisByte;
  while (!client.available()) delay(1);
  respCode = client.peek();
  outCount = 0;
  while (client.available()) {
    thisByte = client.read();
    Serial.write(thisByte);
    if (outCount < 127) {
      outBuf[outCount] = thisByte;
      outCount++;
      outBuf[outCount] = 0;
    }
  }
  if (respCode >= '4') {
    efail();
    return 0;
  }
  return 1;
}
byte doFTP(boolean upload) {
  if (client.connect(server, 21)) {  // 21 = FTP server
    Serial.println(F("Command connected"));
  }
  else {
    Serial.println(F("Command connection failed"));

    return 0;
  }
  if (!eRcv()) return 0;
  if (debug) Serial.println("Send USER");
  client.write("USER ");
  client.println(ftp_account);


  if (!eRcv()) return 0;
  if (debug) Serial.println("Send PASSWORD");
  client.write("PASS ");
  client.println(ftp_passwords);

  if (!eRcv()) return 0;
  if (debug) Serial.println("Send SYST");
  //client.println("SYST");
  client.write("SYST\r\n");

  if (!eRcv()) return 0;
  if (debug) Serial.println("Send Type I");
  //client.println("Type I");
  client.write("Type I\r\n");


  if (!eRcv()) return 0;
  if (debug) Serial.println("Send PASV");
  //client.println("PASV");
  client.write("PASV\r\n");

  if (!eRcv()) return 0;

  char *tStr = strtok(outBuf, "(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL, "(,");
    array_pasv[i] = atoi(tStr);
    if (tStr == NULL) {
      Serial.println(F("Bad PASV Answer"));
    }
  }
  unsigned int hiPort, loPort;
  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  if (debug) Serial.print(F("Data port: "));
  hiPort = hiPort | loPort;
  if (debug) Serial.println(hiPort);

  if (dclient.connect(server, hiPort)) {
    Serial.println(F("Data connected"));
  }
  else {
    Serial.println(F("Data connection failed"));
    client.stop();
    return 0;
  }

  if (upload)
  {
    if (debug) Serial.println("Send STOR filename");
    //client.print("MKD ");
    // client.println(Folder_name);
    client.print("CWD ");
    client.println(Folder_name);
    client.print(F("STOR "));
    client.println(fileName);
  }
  else
  {
    if (debug) Serial.println("Send RETR filename");
    client.print(F("RETR "));
    client.println(fileName);
  }

  if (!eRcv()) {
    dclient.stop();
    return 0;
  }

  if (upload) {
    if (debug) Serial.println(F("Writing to Server"));
    // for faster upload increase buffer size to 1460
    //#define bufSizeFTP 64
#define bufSizeFTP 1460
    uint8_t clientBuf[bufSizeFTP];
    //unsigned int clientCount = 0;
    size_t clientCount = 0;

    dclient.println(data1);
    //dclient.println(data2);
    Serial.println(data1);
    //Serial.println(data2);

  }
  else
  {
    while (dclient.connected()) {
      while (dclient.available()) {
        char c = dclient.read();
        if (debug) Serial.write(c);
      }
    }
  }

  dclient.stop();
  Serial.println(F("Data disconnected"));
  if (!eRcv()) return 0;

  client.println(F("QUIT"));

  if (!eRcv()) return 0;

  client.stop();
  Serial.println(F("Command disconnected"));

  //fh.close();
  if (debug) Serial.println(F("SPIFS closed"));
  return 1;
}  // doFTP()
void callFTP()
{
  if (doFTP(upload))
  {

    Serial.println(F("FTP OK"));
    Serial.println("");
    digitalWrite(led8, LOW);
    digitalWrite(led5, HIGH);
    delay (200);
    digitalWrite(led6, HIGH);
    delay (200);
    digitalWrite(led7, HIGH);
    delay (800);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
  }
  else
  {
    Serial.println(F("FTP NOT CONNECTED."));
  }
}
void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
    digitalWrite(lednetwork, HIGH);
    delay (250);
    digitalWrite(lednetwork, LOW);
  }
  if ((digitalRead(button) == LOW) && (digitalRead(switchK) == HIGH))
  {
    digitalWrite(led8, HIGH);
    digitalWrite(led, LOW);
    Serial.println("on");
    data1 = "Bonding Machine,1,1000-01-01 00:00:00";
    callFTP();
  }
  if (digitalRead(switchK) == LOW)
  {
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
      i = i + 1;
      // delay(500);
      // Serial.print(String(i));
      // we’ll parse the HTML body here
      if (i == 11)  { // print the good stuff
        i = 1;
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
            digitalWrite(12, 1);
            delay(100);
            Serial.println("D1 is On..!");
          }
          else if (led == "off") {
            digitalWrite(12, 0);
            delay(100);
            Serial.println("D1 is Off..!");
          }
        }
        else if (count == 2) {
          if (led == "on") {
            digitalWrite(13, 1);
            Serial.println("D2 is On..!");
          }
          else if (led == "off") {
            digitalWrite(13, 0);
            Serial.println("D2 is Off..!");
          }
        }
        else if (count == 3) {
          if (led == "on") {
            digitalWrite(14, 1);
            Serial.println("D3 is On..!");
          }
          else if (led == "off") {
            digitalWrite(14, 0);
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

  /* //code xuat lien tuc
    if (digitalRead(button) == HIGH)
    {
    digitalWrite(led8, LOW);
    digitalWrite(led, LOW);
    Serial.println("on");
    data1 = "Led dang ON";

    if ((millis() - countMiliis) > 10000)
    {
      countMiliis = millis();
      Serial.println("Xuất file");
      callFTP();
    }
    }
    else
    {
    digitalWrite(led8, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("off");
    data1 = "Led dang OFF";

    if ((millis() - countMiliis) > 10000)
    {
      countMiliis = millis();
      Serial.println("Xuất file");
      callFTP();
    }
    }
  */
}
