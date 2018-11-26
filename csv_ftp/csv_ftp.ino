#include <ESP8266WiFi.h>
#include <SPI.h>
#include <String.h>
#include <SD.h>
int button = 16; // là tx gắn d2
int led8 = 0; //gan d8
int led = LED_BUILTIN;

//const char* ssid     = "iPhone";
//const char* password = "longcoi12345";
const char* ssid     = "TaoLaGa49";
const char* password = "longcoi123";
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
void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led8, OUTPUT);
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

  if (upload) {
    if (debug) Serial.println("Send STOR filename");
    //client.print("MKD ");
    // client.println(Folder_name);
    client.print("CWD ");
    client.println(Folder_name);
    client.print(F("STOR "));
    client.println(fileName);
  } else {
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
  else {
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
  }
  else
  {
    Serial.println(F("FTP NOT CONNECTED."));
  }
}
void loop()
{
  if (digitalRead(button) == HIGH)
  {
    digitalWrite(led8, HIGH);
    digitalWrite(led, LOW);
    Serial.println("on");
    data1 = "Led dang ON";
    callFTP();
  }
  else { // ngược lại
    digitalWrite(led8, LOW);
    digitalWrite(led, HIGH);
    Serial.println("off");
    data1 = "Led dang OFF";
    callFTP();


  }

  delay(10000);
}
