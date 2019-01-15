byte buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};   // the current reading from the input pin
byte lastButtonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}; // the previous reading from the input pin
byte reading[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int lastDebounceTime[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int debounceDelay = 50,debounceDelayHigh =700; // the debounce time; increase if the output flickers
long countTimeLight =0;
uint16_t _index = 0, old_index = 0;
#define NUMBUTTONS 16
#define LED_WIFI PB12
#define LED_FTP PB13
#define LED_INPUT PB14
#define LED_SDCARD PB15
/*
  #define INPUT1  PB0
  #define INPUT2  PB1
  #define INPUT3  PB10
  #define INPUT4  PB11
  #define INPUT5  PA8
  #define INPUT6  PA12
  #define INPUT7  PA15
  #define INPUT8  PB4
  #define INPUT9  PB5
  #define INPUT10 PB6
  #define INPUT11 PB9
  #define INPUT12 PB7
  #define INPUT13 PB8
  #define INPUT14 PC13
  #define INPUT15 PA1
  #define INPUT16 PA2
*/
#define INPUT1  PA15 
#define INPUT2  PA12
#define INPUT3  PA11
#define INPUT4  PA8
#define INPUT5  PB11
#define INPUT6  PB10
#define INPUT7  PB1
#define INPUT8  PB0

#define INPUT9  PA3
#define INPUT10 PB4
#define INPUT11 PB5
#define INPUT12 PB8
#define INPUT13 PB9
#define INPUT14 PC13
#define INPUT15 PA1
#define INPUT16 PA2
byte buttons[] = {INPUT1, INPUT2, INPUT3, INPUT4, INPUT5, INPUT6, INPUT7, INPUT8, \
                  INPUT9, INPUT10, INPUT11, INPUT12, INPUT13, INPUT14, INPUT15, INPUT16
                 };
/////////////////// for debug
#define DEBUG
#define ON LOW
#define OFF HIGH
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
void setup()
{
  Serial1.begin(9600);
  //Serial2.begin(9600);
  ET.begin(details(mydata), &Serial1);
  //Serial2.println("test");
  // init input
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }

#ifdef DEBUG
  Serial1.println(F("initialization done."));
#endif


  //// for led signal
  pinMode(LED_WIFI, OUTPUT);// Wifi
  pinMode(LED_FTP, OUTPUT);// FTP
  pinMode(LED_INPUT, OUTPUT);// Input
  pinMode(LED_SDCARD, OUTPUT);// SDCARD
  digitalWrite(LED_WIFI, ON);
  digitalWrite(LED_FTP, ON);
  digitalWrite(LED_INPUT, ON);
  digitalWrite(LED_SDCARD, ON);
  delay(1000);
  digitalWrite(LED_WIFI, OFF);
  digitalWrite(LED_FTP, OFF);
  digitalWrite(LED_INPUT, OFF);
  digitalWrite(LED_SDCARD, OFF);
  /// for wdt
  //wdt_enable(WDTO_8S);
}

void loop()
{
  /*if(Serial1.available())
    {
    Serial1.println(Serial1.read());
    }*/
  Read_input();
  Status_process();
  Reciver_data();
  if ( (old_index != _index) && _index != 0)
  {
#ifdef DEBUG
    Serial1.print(F("index is:"));
    Serial1.println(_index);
#endif
    status_input = 1;
    send_file_status = 1;
    old_index = _index;
  }
  if (send_file_status == 1) // send data to esp
  {
    send_signal_to_esp();

  }
  if (send_file_status == 2) // send data to esp done
  {
    send_file_status = 0;
    status_input = 0;
    countTimeLight = millis();
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
    if (((millis() - lastDebounceTime[i]) > debounceDelay)&&((millis() - lastDebounceTime[i]) < debounceDelayHigh))
    {
      if (reading[i] != buttonState[i])
      {
        buttonState[i] = reading[i];
        if (buttonState[i] == HIGH)
        {
          _index |= 1 << (i);
        }
      }
    }
  }
  for (byte i = 0; i < NUMBUTTONS; i++)
  {
    lastButtonState[i] = reading[i];
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
    if(millis()- countTimeLight>1000)
    {
      digitalWrite(LED_INPUT, OFF);
    }
    
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
      //Serial2.println("send done");
      send_file_status = 2;
      _index = 0;
      old_index = 0;
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
  /*mydata.data1 = year;
    mydata.data2 = month << 8 | day ;
    mydata.data3 = hour << 8 | minute;*/
  mydata.data4 = _index;
  ET.sendData();
}
