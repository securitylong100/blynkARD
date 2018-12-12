byte buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};     // the current reading from the input pin
byte lastButtonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}; // the previous reading from the input pin
byte reading[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
unsigned long lastDebounceTime[] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
byte buttons[] = {A0, A1, A2, A3, 6, 7, 8, 9};
byte index = 0, old_index = 0;
#define NUMBUTTONS sizeof(buttons)
/////////////////// for debug
//#define DEBUG
//////////////////
///////// for RTC
#include <Wire.h>
#include "RTClib.h"
DateTime now;
RTC_DS1307 rtc;
long time_get_RTC = 0;
int year;
byte month, day, hour, minute, second;
/////////////////////////
///////// for SD Card
#include <SPI.h>
#include <SD.h>
File myFile;
#define SD_CARD_CS 10
bool remove_file =1; // after send ok => delete file (1) or no detelte (0)
///
//////////////// for transfer data
#include <EasyTransfer.h>
EasyTransfer ET;
struct RECEIVE_DATA_STRUCTURE
{
  int16_t command;
  int16_t data1;// year
  int16_t data2;// month-day
  int16_t data3; //hour-minutes
  int16_t data4;//second - input
};
RECEIVE_DATA_STRUCTURE mydata;
// for process
String data1 = "";
byte send_file_status = 0;
long time_send_signal;
int time_delay_send_signal = 1000;
bool status_wifi = 0, status_led_wifi = OFF;
bool status_ftp = 1;
bool status_input = 0;
long time_wifi = 0;
// for transfer data
#define CMD0 0x01  // can't connect wifi
#define CMD1 0x02  // connect wifi
#define CMD2 0x03  // send ftp
#define CMD3 0x04  // can't send ftp
#define CMD4 0x05  // send ftp complete
#define CMD5 0x06  // send signal input
#define CMD6 0x07  //send signal input complete

#define LED_WIFI 2
#define LED_FTP 3
#define LED_INPUT 4
#define LED_SDCARD 5
#define ON LOW
#define OFF HIGH
//////////
//////////// for wdt
#include <avr/wdt.h>
void setup()
{
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  // init input
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  ///// init rtc
  if (! rtc.begin())
  {
#ifdef DEBUG
    Serial.println(F("Couldn't find RTC"));
#endif

  }
  else
  {
#ifdef DEBUG
    Serial.println(F("RTC init ok"));
#endif

  }
  if (! rtc.isrunning())
  {
#ifdef DEBUG
    Serial.println(F("RTC is NOT running!"));
#endif

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  //// init SD CARD

#ifdef DEBUG
  Serial.print(F("Initializing SD card..."));
#endif

  if (!SD.begin(SD_CARD_CS))
  {
#ifdef DEBUG
    Serial.println(F("initialization failed!"));
#endif

  }
  else
  {
#ifdef DEBUG
    Serial.println(F("initialization done."));
#endif

  }
  //// for led signal
  pinMode(LED_WIFI, OUTPUT);// Wifi
  pinMode(LED_FTP, OUTPUT);// FTP
  pinMode(LED_INPUT, OUTPUT);// Input
  pinMode(LED_SDCARD, OUTPUT);// SDCARD
  digitalWrite(LED_WIFI, OFF);
  digitalWrite(LED_FTP, OFF);
  digitalWrite(LED_INPUT, OFF);
  digitalWrite(LED_SDCARD, OFF);

  /// for wdt
  wdt_enable(WDTO_8S);
}

void loop()
{
  wdt_reset();
  Read_input();
  RTC_process();
  Status_process();
  Reciver_data();
  if ( (old_index != index) && index != 0)
  {
    status_input = 1;
#ifdef DEBUG
    Serial.println(F("have input => storage data"));
#endif

    getdata();
#ifdef DEBUG
    Serial.println(F("Data will write is: "));
    Serial.println(data1);
#endif
    SD_card_write();
    send_file_status = 1;
    old_index = index;
  }
  if (send_file_status == 1) // send data to esp
  {
    send_signal_to_esp();

  }
  else if (send_file_status == 2) // send data to esp done
  {
    if(remove_file)
    {
      delete_file();
    }
    index = 0;old_index =0;
    status_input = 0;
    send_file_status = 0;
  }
}
void Read_input()
{
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    reading[i] = digitalRead(buttons[i]);
  }
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    if (reading[i] != lastButtonState[i])
    {
      lastDebounceTime[i] = millis();
    }
  }
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    if ((millis() - lastDebounceTime[i]) > debounceDelay)
    {
      if (reading[i] != buttonState[i])
      {
        buttonState[i] = reading[i];
        if (buttonState[i] == HIGH)
        {

          index |= 1 << (i);
        }
#ifdef DEBUG
        Serial.print(F("index is:"));
        Serial.println(index);
#endif

      }
    }
  }
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    lastButtonState[i] = reading[i];
  }
}
void get_RTC()
{
  now = rtc.now();
  year = now.year();
  month = now.month();
  day = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
#ifdef DEBUG


  Serial.print(F( "Now is: "));
  Serial.print(year);
  Serial.print( F("/"));
  Serial.print(month);
  Serial.print(F( "/"));
  Serial.print(day);
  Serial.print( F(" "));
  Serial.print(hour);
  Serial.print(F( ":"));
  Serial.print(minute);
  Serial.print( F(":"));
  Serial.println(second);

#endif
}
void RTC_process()
{
  if (millis() - time_get_RTC > 1000)
  {
    get_RTC();
    time_get_RTC = millis();
  }
}
void getdata()
{
  //Bonding Machine,1,0,0,0,0,0,0,0,1000-01-01 00:00:00
  data1 = "";
  data1 += "Bonding Machine,";
  for (byte i = 0; i < 8; i++)
  {
    if ((index >> i) & 0x01)
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
void SD_card_write()
{
#ifdef DEBUG

#endif

  myFile = SD.open("test.csv", FILE_WRITE);
  if (myFile)
  {
#ifdef DEBUG
    Serial.print(F("Writing to test.csv..."));
#endif

    myFile.println(data1);
    myFile.close();
#ifdef DEBUG
    Serial.println(F("done."));
#endif

  }
  else
  {
#ifdef DEBUG
    Serial.println(F("error opening test.csv"));
#endif

  }
}
void delete_file()
{
  if (SD.exists("test.csv"))
  {
#ifdef DEBUG
    Serial.println(F("test.csv exists."));
    Serial.println(F("Removing test.csv..."));
#endif
    SD.remove("test.csv");
  }
  else
  {
#ifdef DEBUG
    Serial.println(F("example.txt doesn't exist."));
#endif
  }
}
void send_signal_to_esp()
{
  if (millis() - time_send_signal > time_delay_send_signal)
  {
#ifdef DEBUG

    Serial.println(F("send_signal_to_esp"));
#endif
    Send_data();
    time_send_signal = millis();
  }
}
void Status_process()
{
  if (!status_wifi)
  {
    if (millis() - time_wifi > 100)
    {
      status_led_wifi = !status_led_wifi;
      digitalWrite(LED_WIFI, status_led_wifi);
      time_wifi = millis();
    }
  }
  else
  {
    digitalWrite(LED_WIFI, OFF);
  }
  if (!status_ftp)
  {
    digitalWrite(LED_FTP, ON);
  }
  else
  {
    digitalWrite(LED_FTP, OFF);
  }
  if (status_input)
  {
    digitalWrite(LED_INPUT, ON);
  }
  else
  {
    digitalWrite(LED_INPUT, OFF);
  }
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
    if (mydata.command == CMD0) // can't connect wifi
    {
      status_wifi = 0;
    }
    if (mydata.command == CMD1)//connect wifi
    {
      status_wifi = 1;
    }
    if (mydata.command == CMD2) // ftp fail
    {
      status_ftp = 0;
    }
    if (mydata.command == CMD3)//ftp ok
    {
      status_ftp = 1;
    }
    if (mydata.command == CMD6)//send complete
    {
      send_file_status = 2;
    }
  }
}
void Send_data()
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
  /*
    byte command;
    uint16_t data1;// year
    uint16_t data2;// month-day
    uint16_t data3; //hour-minutes
    uint16_t data4;//second - input
  */
  /*
    int year
    byte month, day, hour, minute, second;
    byte index = 0
  */
  mydata.command = CMD5;
  mydata.data1 = year;
  mydata.data2 = month << 8 | day ;
  mydata.data3 = hour << 8 | minute;
  mydata.data4 = second << 8 | index;
  ET.sendData();
}

