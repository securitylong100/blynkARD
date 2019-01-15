#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <Ticker.h>
#include <EasyTransfer.h>
//const char* ssid     = "GA1";
//const char* password = "@#ncvp2019";
//const char* ssid     = "TaoLaGa49";
//const char* password = "longcoi123";
const char* ssid     = "RedmiLapTop";
const char* password = "quangdang";
const String ftp_account = "ftpin";
const String ftp_passwords = "ftppass";
const char *server = "192.168.145.7";
IPAddress staticIP(192,168,148,251);
IPAddress gateway(192,168,144,254);
IPAddress subnet(255,255,240,0);

//#define DEBUG
bool activeInput[12];
unsigned long activeInputCountTime[12];
#define TimeOutInputCount 5000
/* DEFINE Process name */
String Folder_name = "LDP_5SG";
//String Folder_name = "LDP_5SG";
String fileName = "MC_NOICHK_L01_";
String SerialName = "\"MC-NOICHK";
String LotNoName = ",\"Motor\"";
String ModelName = ",\"LDP_5SG\"";
String SiteName = ",\"NCVP\"";
String FactoryName = ",\"2A\",\"";
String LineName = "L01";
String ProcessName = "\",\"MC_NOICHK\"";

byte SizeOfInspectItemName = 2;
String InspectItemName1 = ",\"NOI_HI\",";
String InspectItemName2 = ",\"NOI_LW\",";

/* Replace by dataCommon2
  String InspectDate = "\"";// "YYYY/MM/DD"
  String InspectTime = "\"";// "HH:MM:SS"
  String InspectData = "\"";
  String JudgeName = "\"0\"";
  String StatusName = "\"INITAL\"";
  String RemarkName = "\"\"";
*/
struct InspectDataDef
{
  byte checkdata;
  long CountOfLine;
  long countOfNG1;
  long countOfNG2;
  long countOfNG3;
  long countOfNG4;
  long countOfNG5;
  long countOfNG6;
  long countOfNG7;
  long countOfNG8;
  long countOfNG9;
  long countOfNG10;
  long countOfNG11;
  long countOfNG12;
  uint16_t yearWhenRun;
  uint8_t monthWhenRun;
  uint8_t dayWhenRun;
  uint8_t hourWhenRun;
  uint8_t minuteWhenRun;
  uint8_t secondWhenRun;
  uint8_t lastminuteWhenRun;
};
InspectDataDef LineData;
int sizeOfData = sizeof(LineData);
String dataCommon0 = "";
String dataCommon1 = "";
String dataCommon2 = "\",\"0\",\"INITAL\",\"\"";
String dataMergeTime = "";
String data1 = "";
String data2 = "";
String data3 = "";
String data4 = "";
String data5 = "";
String data6 = "";
String data7 = "";
String data8 = "";
String data9 = "";
String data10 = "";
String data11 = "";
String data12 = "";
byte checkdata = 0x12;
bool fristRun = 1, fristSync = 1, allowTransferData = 0;

/* End of DEFINE Process name */

WiFiClient client;
WiFiClient dclient;

boolean upload = true;
bool led_pin2_status = 0;
char outCount;
char outBuf[128];
long countMiliis , count_time_check_wifi = 0;
long internalTimer = 0, CheckFactoryTimer = 0;
//////////////// for transfer data
EasyTransfer ET;
struct SEND_DATA_STRUCTURE
{
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

RTC_DS3231 rtc;
DateTime now;
uint16_t _index, _old_index;
long counter = 0;
byte wifi_count = 0;
int counterMinute = 0;
// set up variables using the SD utility library functions:
File myFile;
#define  chipSelect 16
/*                      */
// Using timer as wdt
Ticker TimerCounter ; // Name your ticker
volatile int WatchDogCount = 0;
/**/

void setup()
{
  // put your setup code here, to run once:
  initSerial();
  initWifi();
  initSdCard();
  initEEProm();
  initRTC();
  WriteDataToFlash();
  internalTimer = millis();
  count_time_check_wifi = millis();
  TimerCounter.attach(1, ISRWatchDog);
}
void loop()
{
  WatchDogCount = 0;
  processInputComming();
  processFacoryDefault();
  processEvent1Second();
  processEvent10Second();
  processEvent10minutes();
}
void initSerial()
{
  delay(1000);
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
}
void initWifi()
{
  Send_data(CMD0);
#ifdef DEBUG
  Serial.println(ssid);
#endif
  WiFi.begin(ssid, password);
 // WiFi.config(staticIP,gateway,subnet);
  pinMode(2, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  while ((WiFi.status() != WL_CONNECTED) && wifi_count < 50)
  {
    delay(250);
#ifdef DEBUG
    Serial.print(".");
#endif
    digitalWrite(2, HIGH);
    delay (250);
    digitalWrite(2, LOW);
    wifi_count++;
  }
  Send_data(CMD1);
#ifdef DEBUG

  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Netmask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
  }
#endif
}
void initSdCard()
{
  if (!SD.begin(chipSelect))
  {
#ifdef DEBUG
    Serial.println("initialization failed!");
#endif
  }
}
void initEEProm()
{
  EEPROM.begin(512);
  //reset_factory_default();
  if (fristRun)
  {
#ifdef DEBUG
    Serial.println("fristRun");
#endif
    if (ReadDataFromFlash())
    {
#ifdef DEBUG
      Serial.println("Load data");
#endif
      if (LineData.checkdata != 0x12)
      {
#ifdef DEBUG
        Serial.println("wrong data");
#endif
        for (unsigned int t = 0; t < sizeOfData; t++)
        {
          EEPROM.write(t, 0x00);
        }
        LineData.checkdata = 0x12;
        for (unsigned int t = 0; t < sizeOfData; t++)
        {
          EEPROM.write(t, *((char*)&LineData + t));
        }
        EEPROM.commit();
      }
      if (LineData.checkdata != 0x12)
      {
#ifdef DEBUG
        Serial.println("reset to default data");
#endif
      }
    }
    fristRun = 0;
  }
}
void initRTC()
{
  if (! rtc.begin())
  {
#ifdef DEBUG
    Serial.println("Couldn't find RTC");
#endif
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (rtc.lostPower())
  {
#ifdef DEBUG
    Serial.println("RTC is NOT running!");
#endif
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  now = rtc.now();
  LineData.yearWhenRun = now.year();
  LineData.monthWhenRun = now.month();
  LineData.dayWhenRun = now.day();
  LineData.hourWhenRun = now.hour();
  LineData.minuteWhenRun = now.minute();
  LineData.secondWhenRun = now.second();
#ifdef DEBUG

  {
    Serial.println("fristRun time: ");
    Serial.print(LineData.yearWhenRun);
    Serial.print("/");
    Serial.print(LineData.monthWhenRun);
    Serial.print("/");
    Serial.print(LineData.dayWhenRun);
    Serial.print(",");
    Serial.print(LineData.hourWhenRun);
    Serial.print(":");
    Serial.print(LineData.minuteWhenRun);
    Serial.print(":");
    Serial.println(LineData.secondWhenRun);
  }
#endif
}
void processInputComming()
{
  Reciver_data();
  if ((_old_index != _index) && _index != 0)
  {
    process_index();
    WriteDataToFlash();
    _index = 0;
    _old_index = _index;
  }
}
void processfristSync()
{
  if (fristSync)
  {
    if ((abs(LineData.lastminuteWhenRun - LineData.minuteWhenRun)) % 10 == 0)
    {
#ifdef DEBUG
      Serial.println("sync time");
#endif
      internalTimer = millis();
      counterMinute = 0;
#ifdef DEBUG
      Serial.println("process timer 10 minutes sync");
#endif
      fristSync = 0; allowTransferData = 1;
      send_data_to_server();
    }
  }
}
void processFacoryDefault()
{
  if (longPress())
  {
    reset_factory_default();
    RTC_process();
    WriteDataToFlash();
#ifdef DEBUG
    Serial.println("Reset factory default and reset ESP");
#endif
  }
}
void processEvent1Second()
{
  if (millis() - count_time_check_wifi >= 999)
  {
    processfristSync();
    if (WiFi.status() != WL_CONNECTED)
    {
      Send_data(CMD0);
      led_pin2_status = !led_pin2_status;
      digitalWrite(2, led_pin2_status);
    }
    else
    {
      Send_data(CMD1);
      digitalWrite(2, LOW);
    }
    LineData.secondWhenRun = LineData.secondWhenRun + 1;
    if (LineData.secondWhenRun > 59)
    {
      LineData.minuteWhenRun = LineData.minuteWhenRun + 1;
      LineData.secondWhenRun = 0;
    }
    if (LineData.minuteWhenRun > 59)
    {
      LineData.minuteWhenRun = 0;
      LineData.hourWhenRun = LineData.hourWhenRun + 1;
    }
    if (LineData.hourWhenRun >= 24)
    {
      LineData.hourWhenRun = 0;
    }
    count_time_check_wifi = millis();
  }
}
void processEvent10Second()
{
  if (millis() - internalTimer >= 10000) // update 10s
  {
    counterMinute++;
    RTC_process();
    WriteDataToFlash();
    internalTimer = millis();
  }
}
void processEvent10minutes()
{
  if (counterMinute >= 3)// send data with 10 minutes circle ~ 10 * 6 * 10000 (10s)
  //if (counterMinute >= 60)// send data with 10 minutes circle ~ 10 * 6 * 10000 (10s)
  {
    send_data_to_server();
  }
}
void efail()
{
  byte thisByte = 0;

  client.println(F("QUIT"));

  while (!client.available()) delay(1);

  while (client.available())
  {
    thisByte = client.read();
#ifdef DEBUG
    Serial.write(thisByte);
#endif
  }
  client.stop();
#ifdef DEBUG
  Serial.println(F("Command disconnected"));
#endif
}  // efail
byte eRcv()
{
  byte respCode;
  byte thisByte;
  while (!client.available()) delay(1);
  respCode = client.peek();
  outCount = 0;
  while (client.available())
  {
    thisByte = client.read();
#ifdef DEBUG
    Serial.write(thisByte);
#endif
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
#ifdef DEBUG
    Serial.println(F("Command connected"));
#endif
  }
  else
  {
#ifdef DEBUG
    Serial.println(F("Command connection failed"));
#endif
    return 0;
  }
  if (!eRcv()) return 0;
#ifdef DEBUG
  Serial.println("Send USER");
#endif
  client.write("USER ");
  client.println(ftp_account);


  if (!eRcv()) return 0;
#ifdef DEBUG
  Serial.println("Send PASSWORD");
#endif
  client.write("PASS ");
  client.println(ftp_passwords);

  if (!eRcv()) return 0;
#ifdef DEBUG
  Serial.println("Send SYST");
#endif
  //client.println("SYST");
  client.write("SYST\r\n");

  if (!eRcv()) return 0;
#ifdef DEBUG
  Serial.println("Send Type I");
#endif
  //client.println("Type I");
  client.write("Type I\r\n");


  if (!eRcv()) return 0;
#ifdef DEBUG
  Serial.println("Send PASV");
#endif
  //client.println("PASV");
  client.write("PASV\r\n");

  if (!eRcv()) return 0;

  char *tStr = strtok(outBuf, "(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL, "(,");
    array_pasv[i] = atoi(tStr);
    if (tStr == NULL) {
#ifdef DEBUG
      Serial.println(F("Bad PASV Answer"));
#endif
    }
  }
  unsigned int hiPort, loPort;
  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;
#ifdef DEBUG
  Serial.print(F("Data port: "));
#endif
  hiPort = hiPort | loPort;
#ifdef DEBUG
  Serial.println(hiPort);
#endif
  if (dclient.connect(server, hiPort)) {
#ifdef DEBUG
    Serial.println(F("Data connected"));
#endif
  }
  else {
#ifdef DEBUG
    Serial.println(F("Data connection failed"));
#endif
    client.stop();
    return 0;
  }

  if (upload)
  {
#ifdef DEBUG
    Serial.println("Send STOR filename");
#endif
    //client.print("MKD ");
    // client.println(Folder_name);
    client.print("CWD ");
    client.println(Folder_name);
    client.print(F("STOR "));
    String temp_name = "";
    temp_name += fileName;
    temp_name += String(LineData.yearWhenRun);
    if (LineData.monthWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.monthWhenRun);
    }
    else temp_name += String(LineData.monthWhenRun);
    if (LineData.dayWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.dayWhenRun);
    }
    else temp_name += String(LineData.dayWhenRun);
    if (LineData.hourWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.hourWhenRun);
    }
    else temp_name += String(LineData.hourWhenRun);
    if (LineData.minuteWhenRun < 10) {
      temp_name += String(LineData.minuteWhenRun);
    }
    else temp_name += String(LineData.minuteWhenRun);
    temp_name += "03";
    temp_name += ".csv";

    client.println(temp_name);

  }
  else
  {
#ifdef DEBUG
    Serial.println("Send RETR filename");
#endif
    String temp_name = "";
    temp_name += fileName;
    temp_name += String(LineData.yearWhenRun);
    if (LineData.monthWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.monthWhenRun);
    }
    else temp_name += String(LineData.monthWhenRun);
    if (LineData.dayWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.dayWhenRun);
    }
    else temp_name += String(LineData.dayWhenRun);
    if (LineData.hourWhenRun < 10)
    {
      temp_name += '0';
      temp_name += String(LineData.hourWhenRun);
    }
    else temp_name += String(LineData.hourWhenRun);
    if (LineData.minuteWhenRun < 10) {
      temp_name += String(LineData.minuteWhenRun);
    }
    else temp_name += String(LineData.minuteWhenRun);
    temp_name += "03";
    temp_name += ".csv";
    client.print(F("RETR "));

    client.println(temp_name);
  }
  if (!eRcv())
  {
    dclient.stop();
    return 0;
  }
  if (upload)
  {
#ifdef DEBUG
    Serial.println(F("Writing to Server"));
#endif
    read_data_from_sd();
  }
  else
  {
    while (dclient.connected())
    {
      while (dclient.available())
      {
        char c = dclient.read();
#ifdef DEBUG
        Serial.print(c);
#endif
      }
    }
  }
  dclient.stop();
#ifdef DEBUG
  Serial.println(F("Data disconnected"));
#endif
  if (!eRcv()) return 0;

  client.println(F("QUIT"));
  if (!eRcv()) return 0;
  client.stop();
#ifdef DEBUG
  Serial.println(F("Command disconnected"));
  Serial.println(F("SPIFS closed"));
#endif
  return 1;
}  // doFTP()
bool callFTP()
{
  if (doFTP(upload))
  {
#ifdef DEBUG
    Serial.println(F("FTP OK"));
    Serial.println("");
#endif
    Send_data(CMD3);

    _index = 0;
    _old_index = 0;
    delete_after_send_done();
    return 1;
  }
  else
  {
#ifdef DEBUG
    Serial.println(F("FTP NOT CONNECTED."));
#endif
    Send_data(CMD2);
    return 0;

  }
}
void Reciver_data()
{
  if (ET.receiveData())
  {
    if (mydata.command == CMD5) // Recive
    {
      _index = (mydata.data4);
      mydata.command = CMD6;
      ET.sendData();
      Serial.print("Send Data: ");
      Serial.println(CMD6);
#ifdef DEBUG

      Serial.print("_index: ");
      Serial.println(_index);
#endif
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
  //"FA-BallB-L01000001","Motor","LDP_5SG","NCVP","2A","L01","FA_BallB","LS_BENT","2018/12/28","19:55:03","10","0","INITAL",""
  //"SerialName","LotNoName","ModelName","SiteName","FactoryName","LineName","ProcessName","InspectItemName",\
  "InspectDateTime", "InspectData", "JudgeName", "StatusName", "RemarkName"
  dataCommon1 = "\"";
  dataCommon1 += String(LineData.yearWhenRun);
  dataCommon1 += '/';
  if (LineData.monthWhenRun < 10) {
    dataCommon1 += '0';
    dataCommon1 += String(LineData.monthWhenRun);
  }
  else dataCommon1 += String(LineData.monthWhenRun);
  dataCommon1 += '/';
  if (LineData.dayWhenRun < 10)
  {
    dataCommon1 += '0';
    dataCommon1 += String(LineData.dayWhenRun);
  }
  else dataCommon1 += String(LineData.dayWhenRun);
  dataCommon1 += "\",\"";
  if (LineData.hourWhenRun < 10)
  {
    dataCommon1 += '0';
    dataCommon1 += String(LineData.hourWhenRun);
  }
  else dataCommon1 += String(LineData.hourWhenRun);
  dataCommon1 += ':';
  if (LineData.minuteWhenRun < 10) {
    dataCommon1 += '0';
    dataCommon1 += String(LineData.minuteWhenRun);
  }
  else dataCommon1 += String(LineData.minuteWhenRun);
  dataCommon1 += ":03\",\"";
  dataCommon0 = "";
  dataCommon0 += SerialName + "-" + LineName;
  if (LineData.CountOfLine < 10)
  {
    dataCommon0 += "00000";
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }
  else if (LineData.CountOfLine < 100)
  {
    dataCommon0 += "0000";
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }
  else if (LineData.CountOfLine < 1000)
  {
    dataCommon0 += "000";
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }
  else if (LineData.CountOfLine < 10000)
  {
    dataCommon0 += "00";
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }
  else if (LineData.CountOfLine < 100000)
  {
    dataCommon0 += "0";
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }
  else
  {
    dataCommon0 += String(LineData.CountOfLine) + "\"";
  }

  dataCommon0 += LotNoName + ModelName + SiteName + FactoryName + LineName + ProcessName;
  data1 += dataCommon0 + InspectItemName1 + dataCommon1 + String(LineData.countOfNG1) + dataCommon2;
  data2 += dataCommon0 + InspectItemName2 + dataCommon1 + String(LineData.countOfNG2) + dataCommon2;
}
void RTC_process()
{


  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  now = rtc.now();
  LineData.yearWhenRun = now.year();
  LineData.monthWhenRun = now.month();
  LineData.dayWhenRun = now.day();
  String now_time = "";
  //now_time += String(LineData.yearWhenRun);
  now_time += String(now.year());
  now_time += '/';
  //now_time += String(LineData.monthWhenRun);
  now_time += String(now.month());
  now_time += '/';
  //now_time += String(LineData.dayWhenRun);
  now_time += String(now.day());
  now_time += ",";
  //now_time += String(LineData.hourWhenRun);
  now_time += String(now.hour());
  now_time += ':';
  //now_time += String(LineData.minuteWhenRun);
  now_time += String(now.minute());
  now_time += ':';
  //now_time += String(LineData.secondWhenRun);
  now_time += String(now.second());
#ifdef DEBUG
  Serial.println(now_time);
#endif
  rtc.adjust(DateTime(LineData.yearWhenRun, LineData.monthWhenRun, LineData.dayWhenRun, \
                      LineData.hourWhenRun, LineData.minuteWhenRun, LineData.secondWhenRun));
  now_time += "\n CAL: \n";
  now_time += String(LineData.yearWhenRun);
  now_time += '/';
  now_time += String(LineData.monthWhenRun);
  now_time += '/';
  now_time += String(LineData.dayWhenRun);
  now_time += ",";
  now_time += String(LineData.hourWhenRun);
  now_time += ':';
  now_time += String(LineData.minuteWhenRun);
  now_time += ':';
  now_time += String(LineData.secondWhenRun);
#ifdef DEBUG
  Serial.print("Reset factory default time: ");

  Serial.println(now_time);
#endif


}
void write_backup_data()
{
  myFile = SD.open("backup.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile)
  {
#ifdef DEBUG
    Serial.print("Writing to send.csv...");
#endif
    myFile.println(data1);
    myFile.println(data2);
    // close the file:
    myFile.close();
#ifdef DEBUG
    Serial.println("done.");
#endif
  }
  else
  {
    // if the file didn't open, print an error:
#ifdef DEBUG
    Serial.println("error opening send.csv");
#endif
  }
}
void write_before_send_ftp()
{
  myFile = SD.open("send.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile)
  {
#ifdef DEBUG
    Serial.print("Writing to send.csv...");
#endif
    myFile.println(data1);
    myFile.println(data2);
    // close the file:
    myFile.close();
    data1 = "";
    data2 = "";
    data3 = "";
    data4 = "";
    data5 = "";
    data6 = "";
    data7 = "";
    data8 = "";
    data9 = "";
    data10 = "";
    data11 = "";
    data12 = "";
#ifdef DEBUG
    Serial.println("done.");
#endif
  }
  else
  {
    // if the file didn't open, print an error:
#ifdef DEBUG
    Serial.println("error opening send.csv");
#endif
  }
}
void read_data_from_sd()
{
  // re-open the file for reading:
  myFile = SD.open("send.csv");
  if (myFile)
  {
    // read from the file until there's nothing else in it:
    while (myFile.available())
    {
      uint8_t temp = myFile.read();
      dclient.write(temp);
#ifdef DEBUG
      Serial.write(temp);
#endif
    }
    // close the file:
    myFile.close();
  }
  else
  {
    // if the file didn't open, print an error:
#ifdef DEBUG
    Serial.println("error opening send.csv");
#endif
  }
}
void delete_after_send_done()
{
  if (SD.exists("send.csv"))
  {
#ifdef DEBUG
    Serial.println("send.csv exists.");
    Serial.println("Removing send.csv...");
#endif
    SD.remove("send.csv");
  }
  else
  {
#ifdef DEBUG
    Serial.println("send.csv doesn't exist.");
#endif
  }
}
bool ReadDataFromFlash()
{
  for (unsigned int t = 0; t < sizeOfData; t++)
  {
    *((char*)&LineData + t) = EEPROM.read(t);
  }
}
bool WriteDataToFlash()
{
  for (unsigned int t = 0; t < sizeOfData; t++)
  {
    EEPROM.write(t, *((char*)&LineData + t));
  }
  EEPROM.commit();
}
void reset_factory_default()
{
#ifdef DEBUG
  Serial.println("reset_factory_default");
#endif
  for (unsigned int t = 0; t < sizeOfData; t++)
  {
    EEPROM.write(t, 0x00);
  }
}
void process_index()
{
  /*
    long CountOfLine;
    long countOfNG1;
    long countOfNG2;
    long countOfNG3;
    long countOfNG4;
    long countOfNG6;
    long countOfNG7;
    long countOfNG8;
    long countOfNG9;
    long countOfNG10;
    long countOfNG11;
    long countOfNG12;
  */
/*
#ifdef NG_MODE
bool activeInput[16];
unsigned long activeInputCountTime[16];
#endif
*/
for( byte i=0;i<12;i++)
{
  if(millis() - activeInputCountTime[i] > TimeOutInputCount)
  {
    activeInput[i]=0;
  }
}
  
  if ((_index >> 0) & 0x01)
  {
    if(activeInput[0]==0)
    {
      activeInput[0]=1;
      activeInputCountTime[0]=millis();
      LineData.countOfNG1++;
    }
      
#ifdef DEBUG
    Serial.print("LineData.countOfNG1 event: ");
    Serial.println(LineData.countOfNG1);
#endif
  }
  if ((_index >> 1) & 0x01)
  {
    if(activeInput[1]==0)
    {
      activeInput[1]=1;
      activeInputCountTime[1]=millis();
      LineData.countOfNG2++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG2 event: ");
    Serial.println(LineData.countOfNG2);
#endif
  }
  if ((_index >> 2) & 0x01)
  {
    if(activeInput[2]==0)
    {
      activeInput[2]=1;
      activeInputCountTime[2]=millis();
      LineData.countOfNG3++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG3 event: ");
    Serial.println(LineData.countOfNG3);
#endif
  }
  if ((_index >> 3) & 0x01)
  {
    if(activeInput[3]==0)
    {
      activeInput[3]=1;
      activeInputCountTime[3]=millis();
      LineData.countOfNG4++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG4 event: ");
    Serial.println(LineData.countOfNG4);
#endif
  }
  if ((_index >> 4) & 0x01)
  {
    if(activeInput[4]==0)
    {
      activeInput[4]=1;
      activeInputCountTime[4]=millis();
      LineData.countOfNG5++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG5 event: ");
    Serial.println(LineData.countOfNG5);
#endif
  }
  if ((_index >> 5) & 0x01)
  {
    if(activeInput[5]==0)
    {
      activeInput[5]=1;
      activeInputCountTime[5]=millis();
      LineData.countOfNG6++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG6 event: ");
    Serial.println(LineData.countOfNG6);
#endif
  }
  if ((_index >> 6) & 0x01)
  {
    if(activeInput[6]==0)
    {
      activeInput[6]=1;
      activeInputCountTime[6]=millis();
      LineData.countOfNG7++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG7 event: ");
    Serial.println(LineData.countOfNG7);
#endif
  }
  if ((_index >> 7) & 0x01)
  {
    if(activeInput[7]==0)
    {
      activeInput[7]=1;
      activeInputCountTime[7]=millis();
      LineData.countOfNG8++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG8 event: ");
    Serial.println(LineData.countOfNG8);
#endif
  }
  if ((_index >> 8) & 0x01)
  {
    if(activeInput[8]==0)
    {
      activeInput[8]=1;
      activeInputCountTime[8]=millis();
      LineData.countOfNG9++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG9 event: ");
    Serial.println(LineData.countOfNG9);
#endif
  }
  if ((_index >> 9) & 0x01)
  {
    if(activeInput[9]==0)
    {
      activeInput[9]=1;
      activeInputCountTime[9]=millis();
      LineData.countOfNG10++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG10 event: ");
    Serial.println(LineData.countOfNG10);
#endif
  }
  if ((_index >> 10) & 0x01)
  {
    if(activeInput[10]==0)
    {
      activeInput[10]=1;
      activeInputCountTime[10]=millis();
      LineData.countOfNG11++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG11 event: ");
    Serial.println(LineData.countOfNG11);
#endif
  }
  if ((_index >> 11) & 0x01)
  {
    if(activeInput[11]==0)
    {
      activeInput[11]=1;
      activeInputCountTime[11]=millis();
      LineData.countOfNG12++;
    }
#ifdef DEBUG
    Serial.print("LineData.countOfNG12 event: ");
    Serial.println(LineData.countOfNG12);
#endif
  }
}

bool longPress()
{
  if (millis() - CheckFactoryTimer > 2000 && digitalRead(0) == 0)
  {
    return true;
  }
  else if (digitalRead(0) == 1)
  {
    CheckFactoryTimer = millis();
  }
  return false;
}
void send_data_to_server()
{
#ifdef DEBUG
  Serial.println("Process getdata");
#endif
  getdata();
  //write_backup_data();
#ifdef DEBUG
  Serial.println("Process write_before_send_ftp");
#endif
  write_before_send_ftp();
  Send_data(CMD2);
#ifdef DEBUG
  Serial.println("Process check wifi status");
#endif
  if (WiFi.status() != WL_CONNECTED)
  {
    Send_data(CMD0);
  }
  else
  {
    Send_data(CMD1);
    if (allowTransferData)
    {
#ifdef DEBUG
      Serial.println("Process callFTP");
#endif
      if (callFTP())
      {
        LineData.countOfNG1 = 0;
        LineData.countOfNG2 = 0;
        LineData.countOfNG3 = 0;
        LineData.countOfNG4 = 0;
        LineData.countOfNG6 = 0;
        LineData.countOfNG7 = 0;
        LineData.countOfNG8 = 0;
        LineData.countOfNG9 = 0;
        LineData.countOfNG10 = 0;
        LineData.countOfNG11 = 0;
        LineData.countOfNG12 = 0;
      }
    }
  }
  LineData.CountOfLine++;
  counterMinute = 0;
  LineData.lastminuteWhenRun = LineData.minuteWhenRun;
}
void ISRWatchDog()
{
  WatchDogCount++;

  if (WatchDogCount > 20)
  {
#ifdef DEBUG
    Serial.printf("System have issue... will be reset system.... ");
#endif
    ESP.restart();
  }
}
