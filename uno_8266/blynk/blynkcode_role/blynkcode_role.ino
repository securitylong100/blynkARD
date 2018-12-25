/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EasyTransfer.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a72488240cb24d7e979684466c809887";// token ==> nhận từ email

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";// dien Tên điểm phát wifi
char pass[] = "longcoi123";// password
byte state = 0;
byte change = 0;
byte frist_run = 1;
long old_time = 0, time_delay = 5000;
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
//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
BLYNK_WRITE(V0) //Button Widget is writing to pin V1
{
  int pinData = param.asInt();
  mydata.command = CMD1;
  mydata.data0 = pinData;
  change = 1;
}
BLYNK_WRITE(V1) //Button Widget is writing to pin Relay1
{
  int pinData = param.asInt();
  mydata.command = CMD2;
  mydata.data0 = pinData;
  //send the data
  change = 1;
}
BLYNK_WRITE(V2) //Button Widget is writing to pin Relay2
{
  int pinData = param.asInt();
  mydata.command = CMD3;
  mydata.data0 = pinData;
  //send the data
  change = 1;
}
BLYNK_WRITE(V3) //Button Widget is writing to pin Relay3
{
  int pinData = param.asInt();
  mydata.command = CMD4;
  mydata.data0 = pinData;
  //send the data
  change = 1;
}
WidgetLED led0(V4);
WidgetLED led1(V5);
WidgetLED led2(V6);
WidgetLED led3(V7);
BLYNK_WRITE(V8) //Button Widget is writing to pin Relay3
{
 
  int pinData = param.asInt();
  mydata.command = CMD0;
  mydata.data0 = pinData;
  Blynk.virtualWrite(V0, pinData);
  if(pinData)
  {
    led0.on();
  }
  else
  {
    led0.off();
  }
  //send the data
  change = 1;

}
BLYNK_WRITE(V9) //Button Widget is writing to pin Relay3
{
 
  int pinData = param.asInt();
  mydata.command = CMD1;
  mydata.data0 = pinData;
  Blynk.virtualWrite(V1, pinData);
  if(pinData)
  {
    led0.on();
  }
  else
  {
    led0.off();
  }
  //send the data
  change = 1;

}
BLYNK_WRITE(V10) //Button Widget is writing to pin Relay3
{
 
  int pinData = param.asInt();
  mydata.command = CMD2;
  mydata.data0 = pinData;
  Blynk.virtualWrite(V2, pinData);
  if(pinData)
  {
    led0.on();
  }
  else
  {
    led0.off();
  }
  //send the data
  change = 1;

}
BLYNK_WRITE(V11) //Button Widget is writing to pin Relay3
{
 
  int pinData = param.asInt();
  mydata.command = CMD3;
  mydata.data0 = pinData;
  Blynk.virtualWrite(V3, pinData);
  if(pinData)
  {
    led0.on();
  }
  else
  {
    led0.off();
  }
  //send the data
  change = 1;

}

void setup()
{
  // Debug console
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  mydata.data0 = 0;
  Blynk.begin(auth, ssid, pass);
  mydata.id = 0x01;
  old_time = millis();
}

void loop()
{
  Blynk.run();
  if (change)
  {

    ET.sendData();
    change = 0;
  }
  if (frist_run)
  {
    if (millis() - old_time > time_delay)
    {
      led0.off();
      led1.off();
      led2.off();
      led3.off();
      Blynk.virtualWrite(V0, 0);
      Blynk.virtualWrite(V1, 0);
      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 0);
      frist_run = 0;
      mydata.command = 0x00;
      mydata.data0 = 0x00;
      ET.sendData();
    }
  }
  if (ET.receiveData())
  {
    if (mydata.id == 0x01 )
    {
      if (mydata.command == CMD1) // read output
      {
        if ( (mydata.data0) & 0x01)
        {
          led0.on();
          Blynk.virtualWrite(V0, 1);
        }
        else
        {
          led0.off();
          Blynk.virtualWrite(V0, 0);
        }
      }
      if (mydata.command == CMD2) // read output
      {
        if ( (mydata.data0) & 0x01)
        {
          led1.on();
          Blynk.virtualWrite(V1, 1);
        }
        else
        {
          led1.off();
          Blynk.virtualWrite(V1, 0);
        }
      }
      if (mydata.command == CMD3) // read output
      {
        if ( (mydata.data0) & 0x01)
        {
          led2.on();
          Blynk.virtualWrite(V2, 1);
        }
        else
        {
          led2.off();
          Blynk.virtualWrite(V2, 0);
        }
      }
      if (mydata.command == CMD4) // read output
      {
        if ( (mydata.data0) & 0x01)
        {
          led3.on();
          Blynk.virtualWrite(V3, 1);
        }
        else
        {
          led3.off();
          Blynk.virtualWrite(V3, 0);
        }
      }
      if (mydata.command == CMD5) // read output
      {
        if ( (mydata.data1 & 0x01))
        {
          led0.on();
          Blynk.virtualWrite(V0, 1);
        }
        else
        {
          led0.off();
          Blynk.virtualWrite(V0, 0);
        }
        if ( ((mydata.data1 >> 1) & 0x01))
        {
          led1.on();
          Blynk.virtualWrite(V1, 1);
        }
        else
        {
          led1.off();
          Blynk.virtualWrite(V1, 0);
        }
        if ( ((mydata.data1 >> 2) & 0x01))
        {
          led2.on();
          Blynk.virtualWrite(V2, 1);
        }
        else
        {
          led2.off();
          Blynk.virtualWrite(V2, 0);
        }
        if ( ((mydata.data1 >> 3) & 0x01))
        {
          led3.on();
          Blynk.virtualWrite(V3, 1);
        }
        else
        {
          led3.off();
          Blynk.virtualWrite(V3, 0);
        }
      }
    }
  }
}
