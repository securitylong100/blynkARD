#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <EasyTransfer.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

EasyTransfer ET;
struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  byte id;
  byte command;
  uint16_t data0;
  uint16_t data1;
};
#define CMD0 0x00  //write all relay
#define CMD1 0x01  //write relay1
#define CMD2 0x02  //write relay2
#define CMD3 0x03  //write relay3
#define CMD4 0x04  //write relay4
#define CMD5 0x05  //read all output
#define CMD6 0x06  //read all input
#define CMD7 0x07  //read  input 0
#define CMD8 0x08  //read  input 1
#define CMD9 0x09  //read  input 2
#define CMD10 0x0A //read  input 3
#define CMD11 0x0B //read  input 4
#define CMD12 0x0C //read  input 5
#define CMD13 0x0D //read  input 6
#define CMD14 0x0E //read  input 7
#define CMD15 0x0F //auto send data from slave
#define CMD16 0x10 //write data status
#define CMD17 0x11 // data ok
#define chipSelect  15;
//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
//char auth[] = "e739b91b3af6419181353d1a71a296ab";// token ==> nhận từ email
//char ssid[] = "GA1";// dien Tên điểm phát wifi
//char pass[] = "@#ncvp2019";// password
char ssid[] = "TaoLaGa49";// dien Tên điểm phát wifi
char pass[] = "longcoi123";// password
/* For FTP*/
const char *server = "192.168.145.7";    //chay thuc te
const String ftp_account = "ftpin";      //chay thuc te
const String ftp_passwords = "ftppass";  //chay thuc te
String Folder_name = "459qb";
const String int_fileName = "test.csv";
const String int_path = "/NC01_";
char outBuf[128];
char outCount;
boolean status_connect = true;
boolean upload = true;
String data1, data2;
String fileName, path;
WiFiClient client;
WiFiClient dclient;
bool debug = 0;
long count1 = 0, count2 = 0;
int status_machine = 0;
int year, month, day, hour, minute, second;
long _index;
File myFile;
DateTime now;
RTC_DS1307 rtc;
byte change = 0;
byte sync_time = 0;
byte step_to_run = 0;
byte wifi_status = 1 , sd_ftp = 2, write_data = 0;
byte have_data = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  mydata.data0 = 0;
  write_status(0x01);
  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    write_status(0x00);
  }
  else
  {
    write_status(0x01);
  }
  // We start by connecting to a WiFi network

  if (debug)Serial.println();
  if (debug)Serial.println();
  if (debug)Serial.print("Connecting to ");
  if (debug)Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if (debug)Serial.print(".");
  }
  write_status(0x01);

  if (debug)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  if (!SD.begin(16))
  {
    if (debug)Serial.println("initialization failed!");
    write_status(0x00);
  }
  mydata.id = 0x01;
  sync_time = 1;
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (ET.receiveData())
  {
    if (mydata.command == CMD5) // read output
    {
    }
    if (mydata.command == CMD6) // read all input
    {

    }
    if (mydata.command == CMD15) //auto send data from slave
    {
      mydata.command = CMD17;
      have_data = 1;
      _index |= mydata.data1;
      ET.sendData();
    }
  }

  if ((millis() - count2) > 1000)
  {
    RTC_print();
    //_index++;

    if (debug)
    {
      _index = random(0, 255);
      Serial.print("_index: ");
      Serial.println(_index);
      _index = random(0, 255);
    }
    write_status(write_data);
    count2 = millis();
  }

  if ((millis() - count1) > 2000 )
  {
    if (status_machine == 0)
    {
      write_data = 0;
      getdata();
      SD_card_write();

      status_machine = 1;
    }
    if (status_machine == 1)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        write_data |= wifi_status;
        status_machine = 2;
      }
      else
      {
        write_data = 0;
        status_machine = 0;
      }
      /*if (client.connect(server, 21))
        {
        write_data |= wifi_status;
        }
        else
        {
        write_data &= ~wifi_status;
        SD_card_write();
        }*/


    }
    if (status_machine == 2)
    {
      if (doFTP(upload))
      {
        //byte wifi_status = 1 , sd_ftp = 2, input = 4;
        write_data |= sd_ftp;
        if (debug)Serial.println("FTP OK");
        if (debug)Serial.println("");
        if (SD.exists("test.csv")) {
          if (debug)
          {
            Serial.println("test.csv exists.");
            Serial.println("Removing test.csv...");
          }
          SD.remove("test.csv");
        }
        else
        {
          if (debug)Serial.println("example.txt doesn't exist.");
        }
      }
      else
      {
        write_data &= ~sd_ftp;
        if (debug)Serial.println("FTP FAIL");
        if (debug)Serial.println("");
        status_connect = false;
      }
      status_machine = 0;
      have_data = 0;
      _index = 0;
    }
    count1 = millis();
  }
}
void write_status(byte _status)
{
  mydata.command = CMD16;
  mydata.data0 = _status;
  ET.sendData();
}
void efail()
{
  byte thisByte = 0;

  client.println("QUIT");

  while (!client.available()) delay(50);

  while (client.available())
  {
    thisByte = client.read();
    //Serial.write(thisByte);
  }

  client.stop();
  if (debug)Serial.println("Command disconnected");
}  // efail
byte eRcv()
{
  byte respCode;
  byte thisByte;

  while (!client.available()) delay(50);

  respCode = client.peek();

  outCount = 0;

  while (client.available())
  {
    thisByte = client.read();
    //Serial.write(thisByte);

    if (outCount < 127)
    {
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
}  // eRcv()
byte doFTP(boolean upload)
{

  //if (debug) Serial.println("SPIFFS opened");
  if (client.connect(server, 21))
  { // 21 = FTP server
    if (debug)Serial.println("Command connected");
  }
  else
  {
    if (debug)Serial.println("Command connection failed");
    return 0;
  }
  if (!eRcv()) return 0;
  delay(5);
  if (debug) Serial.println("Send USER");
  client.write("USER ");
  client.println(ftp_account);
  if (!eRcv()) return 0;
  delay(5);
  if (debug) Serial.println("Send PASSWORD");
  client.write("PASS ");
  client.println(ftp_passwords);

  if (!eRcv()) return 0;
  delay(5);
  if (debug) Serial.println("Send SYST");
  //client.println("SYST");
  client.write("SYST\r\n");

  if (!eRcv()) return 0;
  delay(5);
  if (debug) Serial.println("Send Type I");
  //client.println("Type I");
  client.write("Type I\r\n");

  if (!eRcv()) return 0;
  delay(5);
  if (debug) Serial.println("Send PASV");
  //client.println("PASV");
  client.write("PASV\r\n");

  if (!eRcv()) return 0;
  delay(5);
  char *tStr = strtok(outBuf, "(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL, "(,");
    array_pasv[i] = atoi(tStr);
    if (tStr == NULL) {
      if (debug)Serial.println("Bad PASV Answer");
    }
  }
  unsigned int hiPort, loPort;
  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  if (debug) Serial.print("Data port: ");
  hiPort = hiPort | loPort;
  if (debug) Serial.println(hiPort);

  if (dclient.connect(server, hiPort)) {
    if (debug)Serial.println("Data connected");
  }
  else {
    if (debug)Serial.println("Data connection failed");
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
    client.print("STOR ");
    client.println(fileName);
  }
  else
  {
    if (debug) Serial.println("Send RETR filename");
    client.print("RETR ");
    client.println(fileName);
  }
  if (!eRcv())
  {
    dclient.stop();
    return 0;
  }

  if (upload)
  {
    if (debug) Serial.println("Writing to Server");
    // for faster upload increase buffer size to 1460
    myFile = SD.open("test.csv");
    size_t _my_size = myFile.size();
    uint8_t temp = 0x00;


    if (myFile)
    {
      if (debug)Serial.print("open to test.txt...");
      //while (myFile.available())
      //{
      if (debug)Serial.println("bat dau truyen ");
      if (debug)Serial.print("data the nho voi size:");
      if (debug)Serial.println(_my_size);
      /*for (size_t i = 0; i < _my_size; i++)
        {
        temp = myFile.read();
        if (debug)Serial.write(temp);
        dclient.write((const uint8_t *) temp, 1);
        }
        myFile.close();*/
      String temp_data = "";
      while (myFile.available())
      {
        //temp_data += myFile.read();
        temp = myFile.read();
        dclient.write(temp);
      }
      dclient.println();
      // close the file:
      myFile.close();
      //dclient.println(temp_data);
      temp_data = "";
      if (debug)Serial.println("truyen done");

      //}
      if (debug)Serial.println("done.");
    }
    else
    {
      // if the file didn't open, print an error:
      if (debug)Serial.println("error opening test.csv");
    }
    if (debug)Serial.println("xoa file sau truyen done");
    //dclient.println(data1);
    //dclient.println(data2);
    // if (debug)Serial.println(data1);
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
  if (debug)Serial.println("Data disconnected");

  if (!eRcv()) return 0;

  client.println("QUIT");

  if (!eRcv()) return 0;

  client.stop();
  write_data &= ~sd_ftp;
  if (debug)Serial.println(F("Command disconnected"));

  //fh.close();
  if (debug) Serial.println("SPIFS closed");
  return 1;
}  // doFTP()

void getdata()
{
  fileName = int_fileName;
  path = int_path;
  path += String(year);
  /*if (month < 10)
    {
    path += '0';
    path += String(month);
    }
    else  path += String(month);
    if (day < 10)
    {
    path += '0';
    path += String(day);
    }
    else  path += String(day);
    if (hour < 10)
    {
    path += '0';
    path += String(hour);
    }
    else  path += String(hour);
    if (minute < 10) {
    path += '0';
    path += String(minute);
    }
    else  path += String(minute);
    if (second < 10) {
    path += '0';
    path += String(second);
    }
    else  path += String(second);

    data1 = "\"";
    data1 += String(_index);
    data1 += "\",\"NC01\",\"CUTTING\",\"NCVP\",\"1B\",\"L01\",\"IOT\",\"STATUS\"";

    data1 += ",\"";
    data1 += String(year);
    data1 += '/';
    if (month < 10) {
    data1 += '0';
    data1 += String(month);
    }
    else data1 += String(month);
    data1 += '/';
    if (day < 10) {
    data1 += '0';
    data1 += String(day);
    }
    else data1 += String(day);
    data1 += "\",\"";
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
    data1 += "\",\"";
    data1 += String(status_machine);
    data1 += "\",\"";
    data1 += String(0);
    data1 += "\",\"INITIAL\",\"\"";*/
  //Bonding Machine,1,0,0,0,0,0,0,0,1000-01-01 00:00:00
  data1 = "";
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
  //data1 += "\"";
}
void SD_card_write()
{
  /*                          */
  if (debug)Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.csv", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile)
  {
    if (debug)Serial.print("Writing to test.txt...");
    //myFile.print("index: ");
    myFile.println(data1);
    // close the file:
    myFile.close();
    if (debug)Serial.println("done.");
  }
  else
  {
    // if the file didn't open, print an error:
    if (debug)Serial.println("error opening test.csv");
  }
}
void RTC_print()
{
  now = rtc.now();
  year = now.year();
  month = now.month();
  day = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
}
