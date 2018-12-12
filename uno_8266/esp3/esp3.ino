#include <ESP8266WiFi.h>
const char* ssid     = "GA1";
const char* password = "@#ncvp2019";
//const char* ssid     = "TaoLaGa49";
//const char* password = "longcoi123";
const String ftp_account = "ftpin";
const String ftp_passwords = "ftppass";
const char *server = "192.168.145.7";

//const char* ssid     = "TP-LINK_P03";
//const char* password = "hoihoaivaydaica";
//const String ftp_account = "iottechn";
//const String ftp_passwords = "admin1@";
//const char *server = "iottechno.com";

String fileName = "test.csv";
String Folder_name = "459qb";

WiFiClient client;
WiFiClient dclient;
String data1, data2 ;
boolean debug = false;
boolean upload = true;
char outCount;
char outBuf[128];
long countMiliis ,count_time_check_wifi = 0 ;
//////////////// for transfer data
#include <EasyTransfer.h>
EasyTransfer ET;
struct SEND_DATA_STRUCTURE{
  int16_t command;
  int16_t data1;// year
  int16_t data2;// month-day
  int16_t data3; //hour-minutes
  int16_t data4;//second - input
};
SEND_DATA_STRUCTURE mydata;
#define CMD0 0x01  // can't connect wifi
#define CMD1 0x02  // connect wifi
#define CMD2 0x03  // send ftp
#define CMD3 0x04  // can't send ftp
#define CMD4 0x05  // send ftp complete
#define CMD5 0x06  // send signal input
#define CMD6 0x07  //send signal input complete
int year;
byte month, day, hour, minute, second;
byte _index, _old_index;
void setup()
{
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  Send_data(CMD0);
  if (debug)Serial.println(ssid);
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    if (debug)Serial.print(".");
    digitalWrite(2, HIGH);
    if (debug)delay (250);
    digitalWrite(2, LOW);
  }
  Send_data(CMD1);
  if (debug)Serial.println("");
  if (debug)Serial.println("WiFi connected");
  if (debug)Serial.println("IP address: ");
  if (debug)Serial.println(WiFi.localIP());
  if (debug)Serial.print("Netmask: ");
  if (debug)Serial.println(WiFi.subnetMask());
  if (debug)Serial.print("Gateway: ");
  if (debug)Serial.println(WiFi.gatewayIP());
}
void efail() {
  byte thisByte = 0;

  client.println(F("QUIT"));

  while (!client.available()) delay(1);

  while (client.available()) {
    thisByte = client.read();
    if (debug)Serial.write(thisByte);
  }

  client.stop();
  if (debug)Serial.println(F("Command disconnected"));
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
    if (debug)Serial.write(thisByte);
    if (outCount < 127) {
      outBuf[outCount] = thisByte;
      outCount++;
      outBuf[outCount] = 0;
    }
  }
  if (respCode >= '4') 
  {
    efail();
    return 0;
  }
  return 1;
}
byte doFTP(boolean upload)
{

  if (client.connect(server, 21))
  { // 21 = FTP server
    if (debug)Serial.println(F("Command connected"));
  }
  else
  {
    if (debug)Serial.println(F("Command connection failed"));
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
      if (debug)Serial.println(F("Bad PASV Answer"));
    }
  }
  unsigned int hiPort, loPort;
  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  if (debug) Serial.print(F("Data port: "));
  hiPort = hiPort | loPort;
  if (debug) Serial.println(hiPort);

  if (dclient.connect(server, hiPort)) {
    if (debug)Serial.println(F("Data connected"));
  }
  else {
    if (debug)Serial.println(F("Data connection failed"));
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
    if (debug)Serial.println(data1);
    //Serial.println(data2);

  }
  else
  {
    while (dclient.connected()) 
    {
      while (dclient.available()) 
      {
        char c = dclient.read();
        if (debug) Serial.write(c);
      }
    }
  }

  dclient.stop();
  if (debug)Serial.println(F("Data disconnected"));
  if (!eRcv()) return 0;

  client.println(F("QUIT"));

  if (!eRcv()) return 0;

  client.stop();
  if (debug)Serial.println(F("Command disconnected"));

  //fh.close();
  if (debug) Serial.println(F("SPIFS closed"));
  return 1;
}  // doFTP()
void callFTP()
{
  if (doFTP(upload))
  {

    if (debug)Serial.println(F("FTP OK"));
    if (debug)Serial.println("");
    Send_data(CMD3);
    _index = 0;
    data1 = "";
  }
  else
  {
    if (debug)Serial.println(F("FTP NOT CONNECTED."));
    Send_data(CMD2);
    data1 += "\n";
  }
}
void loop()
{
  //Send_data(CMD0);
  while (WiFi.status() != WL_CONNECTED)
  {
    
    delay(250);
    if (debug)Serial.print(".");
    digitalWrite(2, HIGH);
    delay (250);
    digitalWrite(2, LOW);
  }
  if(millis()-count_time_check_wifi>1000)
  {
    if (WiFi.status() != WL_CONNECTED)
  {
    Send_data(CMD0);
  }
  else
  {
    Send_data(CMD1);
  }
  }
  //Send_data(CMD1);
  Reciver_data();
  if ((_old_index != _index) && _index != 0)
  {
    if (debug)Serial.println("send FTP");
    getdata();
    Send_data(CMD2);
    callFTP();
    countMiliis = millis();
    _old_index = _index;
  }
  /*if (millis() - countMiliis > 10000)
  {
    if (debug)Serial.println("on");
    data1 = "Bonding Machine,1,1000-01-01 00:00:00";
    callFTP();
    countMiliis = millis();
  }*/
}
void Reciver_data()
{
  /*
    #define CMD0 0x00  // can't connect wifi
    #define CMD1 0x01  // connect wifi
    #define CMD2 0x02  // send ftp
    #define CMD3 0x03  // can't send ftp
    #define CMD4 0x04  // send ftp complete
    #define CMD5 0x05  // send signal input
    #define CMD6 0x06  //send signal input complete
  */
  if (ET.receiveData())
  {
    if (mydata.command == CMD5) // can't connect wifi
    {
      /*mydata.data1 = year;
        mydata.data2 = month << 8 | day ;
        mydata.data3 = hour << 8 | minute;
        mydata.data4 = second << 8 | index;*/
      year = mydata.data1;
      month = (mydata.data2 >> 8) & 0xff;
      day = (mydata.data2) & 0xff;
      hour = (mydata.data3 >> 8) & 0xff;
      minute = (mydata.data3) & 0xff;
      second = (mydata.data4 >> 8) & 0xff;
      _index = (mydata.data4) & 0xff;
      mydata.command = CMD6;
      ET.sendData();
    }
  }
}
void Send_data(byte CMD)
{
  mydata.command = CMD;
  ET.sendData();
}
void getdata()
{
  //Bonding Machine,1,0,0,0,0,0,0,0,1000-01-01 00:00:00

  data1 += "Bonding Machine,";
  for (byte i = 0; i < 8; i++)
  {
    if ((_index >> i) & 0x01)
    {
      data1 += "1,";
    }
    else
    {
      data1 += "0,";
    }
  }
  data1 += String(year);
  data1 += '-';
  if (month < 10) {
    data1 += '0';
    data1 += String(month);
  }
  else data1 += String(month);
  data1 += '-';
  if (day < 10) {
    data1 += '0';
    data1 += String(day);
  }
  else data1 += String(day);
  data1 += " ";
  //data1 += "\",\"";
  if (hour < 10) {
    data1 += '0';
    data1 += String(hour);
  }
  else data1 += String(hour);
  data1 += ':';
  if (minute < 10) {
    data1 += '0';
    data1 += String(minute);
  }
  else data1 += String(minute);
  data1 += ':';
  if (second < 10) {
    data1 += '0';
    data1 += String(second);
  }
  else data1 += String(second);

}
