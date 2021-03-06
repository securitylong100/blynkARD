#include <EasyTransfer.h>
#include <avr/wdt.h>
//create object
EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  byte id;
  byte command;
  uint16_t data0;
  uint16_t data1;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;
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
#define CMD16 0x10 //auto send data from slave
#define CMD17 0x11 //auto send data from slave
#define CMD18 0x12 //disconnect/don't connect to wifi
#define CMD19 0x13 //connect to wifi
#define CMD20 0x14 //disconnect/don't connect to wifi
#define CMD21 0x15 //connect to wifi
#define CMD22 0x16 //don't have SD Card
#define CMD23 0x17 // have SD Card
/* define pin option*/
#define ANALOG 0
#define DIGITAL 1
#define ON LOW
#define OFF HIGH
/* define  6 channel analog/digital CMD: 16 ->21*/

/* define  6 channel analog/digital CMD: 16 ->21*/
/* Read 6 channel analog*/
/* */
#define ID 0x01
#define IN0 A0
#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 10
#define IN5 11
#define IN6 12
#define IN7 13
#define RELAY1 6
#define RELAY2 7
#define RELAY3 8
#define RELAY4 9
#define LED_WIFI 2
#define LED_FTP 3
#define LED_INPUT 4
#define LED_SDCARD 5
#define OLD_VERSION
uint16_t data = 0x00;
long old_time, time_delay = 100, time_sent;
#ifdef OLD_VERSION
byte old_version = 0;
#endif
byte have_data = 0, _data = 0;
bool debug = 0;
bool status_wifi = 0, status_led_wifi = OFF;
bool status_ftp = 0, status_sd = 0;
long time_wifi = 0;
void setup() {
  Serial.begin(9600);
  /* Relay*/
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  // Status
  pinMode(LED_WIFI, OUTPUT);// Wifi
  pinMode(LED_FTP, OUTPUT);// FTP
  pinMode(LED_INPUT, OUTPUT);// Input
  pinMode(LED_SDCARD, OUTPUT);// SDCARD
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  pinMode(IN0, INPUT_PULLUP);
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(IN3, INPUT_PULLUP);
  pinMode(IN4, INPUT_PULLUP);
  pinMode(IN5, INPUT_PULLUP);
  pinMode(IN6, INPUT_PULLUP);
  pinMode(IN7, INPUT_PULLUP);
  //Serial1.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial);
  wdt_enable(WDTO_8S);
}

void loop()
{
  wdt_reset();
  scan_input();
  /*if (millis() - time_sent > time_delay)
    {
    if (have_data)
    {
      mydata.command = CMD15;
      mydata.data1 = _data;
      ET.sendData();
    }
      time_sent=millis();
    }*/


  //check and see if a data packet has come in.
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
  if (!status_sd)
  {
    digitalWrite(LED_SDCARD, ON);
  }
  else
  {
    digitalWrite(LED_SDCARD, OFF);
  }
  if (ET.receiveData())
  {
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out.
    /*Serial.print(" blinks: ");
      Serial.println(mydata.blinks);
      Serial.print(" pause: ");
      Serial.println(mydata.pause);*/
    if (mydata.id == ID )
    {
      //Serial.println(mydata.data0,HEX);
      if (mydata.command == CMD0)
      {
        digitalWrite(RELAY1, (mydata.data0) & 0x01);
        digitalWrite(RELAY2, (mydata.data0 >> 1) & 0x01 );
        digitalWrite(RELAY3, (mydata.data0 >> 2) & 0x01);
        digitalWrite(RELAY4, (mydata.data0 >> 3) & 0x01);

#ifdef OLD_VERSION
        old_version = 0;
        old_version = (byte)mydata.data0;
#endif
      }
      if (mydata.command == CMD1)
      {
        digitalWrite(6, mydata.data0);
#ifdef OLD_VERSION
        if (mydata.data0)
        {
          old_version |= 1 << 0 ;
        }
        else
        {
          old_version = old_version & 0xfe;
        }
#endif
        ET.sendData();
      }
      if (mydata.command == CMD2)
      {
        digitalWrite(7, mydata.data0);

#ifdef OLD_VERSION
        if (mydata.data0)
        {
          old_version |= 1 << 1 ;
        }
        else
        {
          old_version = old_version & 0xfd;
        }
#endif
        ET.sendData();
      }
      if (mydata.command == CMD3)
      {
        digitalWrite(8, mydata.data0);

#ifdef OLD_VERSION
        if (mydata.data0)
        {
          old_version |= 1 << 2 ;
        }
        else
        {
          old_version = old_version & 0xfb;
        }
#endif
        ET.sendData();
      }
      if (mydata.command == CMD4)
      {
        digitalWrite(9, mydata.data0);

#ifdef OLD_VERSION
        if (mydata.data0)
        {
          old_version |= 1 << 3 ;
        }
        else
        {
          old_version = old_version & 0xf7;
        }
#endif
        ET.sendData();
      }
      if (mydata.command == CMD5)
      {
        mydata.data1 = 0;

#ifdef OLD_VERSION
        mydata.data1 = old_version;
#else
        /* new board */
        mydata.data1 |= (digitalRead(6));
        mydata.data1 |= (digitalRead(7)) << 1;
        mydata.data1 |= (digitalRead(8)) << 2;
        mydata.data1 |= (digitalRead(9)) << 3;
#endif
        ET.sendData();
      }
      if (mydata.command == CMD6)
      {
        mydata.data1 = _data;
        ET.sendData();
      }
      if (mydata.command == CMD7)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN0);
        ET.sendData();
      }
      if (mydata.command == CMD8)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN1);
        ET.sendData();
      }
      if (mydata.command == CMD9)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN2);
        ET.sendData();
      }
      if (mydata.command == CMD10)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN3);
        ET.sendData();
      }
      if (mydata.command == CMD11)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN4);
        ET.sendData();
      }
      if (mydata.command == CMD12)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN5);
        ET.sendData();
      }
      if (mydata.command == CMD13)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN6);
        ET.sendData();
      }
      if (mydata.command == CMD14)
      {
        mydata.data1 = 0;
        mydata.data1 = digitalRead(IN7);
        ET.sendData();
      }
      if (mydata.command == CMD16)
      {
        digitalWrite(2, !((mydata.data0) & 0x01));
        digitalWrite(3, !((mydata.data0 >> 1) & 0x01 ));
        ET.sendData();
      }
      if (mydata.command == CMD17)// input prcessed
      {
        have_data = 0;
        _data = 0;
        digitalWrite(4, HIGH);
      }
      if (mydata.command == CMD18) // can't connect wifi
      {
        status_wifi = 0;
      }
      if (mydata.command == CMD19)//connect wifi
      {
        status_wifi = 1;
      }
      if (mydata.command == CMD20) // ftp fail
      {
        status_ftp = 0;
      }
      if (mydata.command == CMD21)//ftp ok
      {
        status_ftp = 1;
      }
      if (mydata.command == CMD22) // don't have sd card
      {
        status_sd = 0;
      }
      if (mydata.command == CMD23)//have sd card
      {
        status_sd = 1;
      }
    }
  }

  //you should make this delay shorter then your transmit delay or else messages could be lost
  //delay(250);
}

uint8_t read_input()
{
  uint8_t temp = 0x00;
  if (millis() - old_time > time_delay)
  {
    if (digitalRead(IN0) == 0) {
      temp |= 1 << 0;
    }
    if (digitalRead(IN1) == 0) {
      temp |= 1 << 1;
    }
    if (digitalRead(IN2) == 0) {
      temp |= 1 << 2;
    }
    if (digitalRead(IN3) == 0) {
      temp |= 1 << 3;
    }
    if (digitalRead(IN4) == 0) {
      temp |= 1 << 4;
    }
    if (digitalRead(IN5) == 0) {
      temp |= 1 << 5;
    }
    if (digitalRead(IN6) == 0) {
      temp |= 1 << 6;
    }
    if (digitalRead(IN7) == 0) {
      temp |= 1 << 7;
    }
    old_time = time_delay;
  }
  return temp;
}
void scan_input()
{
  uint8_t temp = 0x00;
  temp = read_input();
  if (temp != 0)
  {
    have_data = 1;
    _data |= temp;
    digitalWrite(4, LOW);
    if (debug) Serial.println(temp);
  }
}

