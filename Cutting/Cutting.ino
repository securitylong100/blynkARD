//#include <ModbusRtu.h>
#include <stdlib.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
int addr = 0;
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <avr/wdt.h>
RTC_DS1307 rtc;

const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include <SD.h>

// set up variables using the SD utility library functions:
//Sd2Card card;
//SdVolume volume;
//SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 4;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char outBuf[128];
char outCount;
String fileName,path;

// change for diffence machine
String Folder_name="459qb";
const String int_fileName = "NC01.csv";
const String int_path = "/NC01_";


//const String ftp_account = "long.vespa";  //test gia lap
//const String ftp_passwords = "6666ncvp";  //test gia lap

// Set the static IP address to use if the DHCP fails to assign
//const char *server = "192.168.1.1";   //test gia lap
//IPAddress ip(192, 168, 1, 10);        //test gia lap
//IPAddress subnet(255, 255, 255, 0);   //test gia lap
//IPAddress gateway(192, 168, 1, 1);    //test gia lap


const String ftp_account = "ftpin";      //chay thuc te
const String ftp_passwords = "ftppass";  //chay thuc te

// Set the static IP address to use if the DHCP fails to assign
const char *server = "192.168.145.7";    //chay thuc te
IPAddress ip(192, 168, 148, 60);         //chay thuc te
IPAddress subnet(255, 255, 240, 0);      //chay thuc te
IPAddress gateway(192, 168, 144, 254);   //chay thuc te


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
EthernetClient dclient;
boolean debug = true;

// dinh nghia ten
#define X 37
#define D 36
#define V 35

#define ON 0
#define OFF 1


unsigned long u32wait;
//static unsigned char current_state=stop_status;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

long index;
int status_machine;
String data1,data2;
void setup() {
  init_ios();
  Ethernet.begin(mac, ip, dns, gateway, subnet);
    
  Serial.begin(9600);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if ( !rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // give the Ethernet shield a second to initialize:
  Serial.println("Waiting for init...");
  delay(5000);
  
//  Serial.print("Initializing SD card...");
//  if (!SD.begin(chipSelect)) {
//    Serial.println("Card failed, or not present");
//    digitalWrite(Xanh, LOW);
//    digitalWrite(Do, HIGH);
//    digitalWrite(Vang, LOW);
//    digitalWrite(Coi, HIGH);
//    while(1);
//  }
//  Serial.println("card initialized.");
//  Serial.println("");
//
//  SD.remove("datalog.txt");
  //index=0;
  //EEPROM.put(addr, index);
  //index=0;
  EEPROM.get(addr,index);
  Serial.print("Index=");
  Serial.println(index);
  delay(5000);
  wdt_enable(WDTO_8S);
}
long count=millis();
long count1=millis();
int year,month,day,hour,minute,second;
boolean status_lamp;
boolean status_connect=true;
boolean upload = true; 
int countX,countD,countV;  
void loop() {
  wdt_reset();
  if ((millis() - count) > 2000) {
    RTC_print();

    if (digitalRead(X) == ON) {
      ++countX;
      if (countX>=5) {Serial.println("XANH ON ");status_machine=0;countX=5;}
    }
    else {
             Serial.println("XANH OFF ");
             countX=0;
    }

    if (digitalRead(D) == ON) {
      ++countD;
      if (countD>=5){Serial.println("DO ON ");status_machine=3;countD=5;}
    }
    else {
             Serial.println("DO OFF ");
             countD=0;
    }

    if (digitalRead(V) == ON) {
      ++countV;
      if (countV>=5) {Serial.println("VANG ON ");status_machine=1;countV=5;}
    }
    else {
             Serial.println("VANG OFF ");
             countV=0;
    }

    if ((digitalRead(X) == OFF)&&(digitalRead(D) == OFF)&&(digitalRead(V) == OFF)) status_machine=4;
     
    Serial.print("STATUS=");Serial.println(status_machine);
    
    count = millis();
  }
  
  if ((millis() - count1) > 20000) {
    
    index+=1;
    EEPROM.put(addr, index);
    getdata();
    if (doFTP(upload)) {
         Serial.println(F("FTP OK"));
         Serial.println("");
         //if (status_connect==false) SD_card_read();
         status_connect=true;
         
    }
    else {
         Serial.println(F("FTP FAIL"));
         Serial.println("");
         //SD_card_write();
         status_connect=false;
         
    }
    count1 = millis();
  }
   
}

void init_ios()
{
  pinMode(X, INPUT_PULLUP); pinMode(D, INPUT_PULLUP); pinMode(V, INPUT_PULLUP);
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
//-------------- FTP receive
byte eRcv() {
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
}  // eRcv()
//--------------- FTP handling
byte doFTP(boolean upload) {
    
  //if (debug) Serial.println(F("SPIFFS opened"));
 
  
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
  
//  if (upload) {
//    if (debug) Serial.println("Send STOR filename");
//    client.print(F("STOR "));
//    client.println(fileName);
//  } else {
//    if (debug) Serial.println("Send RETR filename");
//    client.print(F("RETR "));
//    client.println(fileName);
//  }

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

void RTC_print() {
  DateTime now = rtc.now();
  year=now.year();
  Serial.print(year, DEC);
  Serial.print('/');
  month=now.month();
  Serial.print(month, DEC);
  Serial.print('/');
  day=now.day();
  Serial.print(day, DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  hour=now.hour();
  Serial.print(hour, DEC);
  Serial.print(':');
  minute=now.minute();
  Serial.print(minute, DEC);
  Serial.print(':');
  second=now.second();
  Serial.print(second, DEC);
  Serial.println();
}

void SD_card_write(){
   // ghi vao the nho
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
    //dataFile = SD.open("datalog.txt");
        Serial.println("Writing data to SD : datalog.txt...");
        dataFile.println(data1);
        dataFile.println(data2);
        dataFile.close();
        Serial.println(data1);
        Serial.println(data2);
    }
    // if the file isn't open, pop up an error:
    else {
        Serial.println("error opening datalog.txt");
    }
 
}
void SD_card_read(){
     
     // re-open the file for reading:
     File dataFile = SD.open("datalog.txt", FILE_WRITE);
     dataFile = SD.open("datalog.txt");
     char data;
     if (dataFile ) {
        Serial.println("Reading data from SD: datalog.txt...");

        // read from the file until there's nothing else in it:
        char i=0;
        data1="";
        data2="";  
        while (dataFile.available()) {
            data=dataFile.read();
             
            if (data=='\n') {
               ++i;
               
               if (i==2){
                    i=0;
                       Serial.println(data1);
                       Serial.println(data2);
                       Serial.println("");
                       if (doFTP(upload)) {
                            Serial.println(F("FTP OK"));
                       }
                       else {
                            Serial.println(F("FTP FAIL"));
                       }
                        data1="";
                        data2="";

                        delay(1000);
               }
               
            }
            else 
               if (data!='\r')
               { if (i==0) data1+=data;
                 else  if (i==1) data2+=data;
               }  
        }
        // close the file:
        dataFile.close();
        SD.remove("datalog.txt");
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening datalog.txt");
        }
        //while(1);
}
void getdata(){
    
    
    fileName = int_fileName;
    
//    fileName +=String(year);
//    if (month<10) {fileName +='0';fileName +=String(month);}
//    else fileName +=String(month);
//    if (day<10) {fileName +='0';fileName +=String(day);}
//    else fileName +=String(day);
//    if (hour<10) {fileName +='0';fileName +=String(hour);}
//    else fileName +=String(hour);
//    if (minute<10) {fileName +='0';fileName +=String(minute);}
//    else fileName +=String(minute);
//    if (second<10) {fileName +='0';fileName +=String(second);}
//    else fileName +=String(second);
   
    path = int_path;
    path +=String(year);
    if (month<10) { path +='0'; path +=String(month);}
    else  path +=String(month);
    if (day<10) { path +='0'; path +=String(day);}
    else  path +=String(day);
    if (hour<10) { path +='0'; path +=String(hour);}
    else  path +=String(hour);
    if (minute<10) { path +='0'; path +=String(minute);}
    else  path +=String(minute);
    if (second<10) { path +='0'; path +=String(second);}
    else  path +=String(second);
    
    data1="\"";
    data1 +=String(index);
    data1 += "\",\"NC01\",\"CUTTING\",\"NCVP\",\"1B\",\"L01\",\"IOT\",\"STATUS\"";
   
    data1 +=",\"";
    data1 +=String(year);
    data1 +='/';
    if (month<10) { data1 +='0'; data1 +=String(month);}
    else data1 +=String(month);
    data1 +='/';
    if (day<10) { data1 +='0'; data1 +=String(day);}
    else data1 +=String(day);
    data1 +="\",\"";
    if (hour<10) { data1 +='0'; data1 +=String(hour);}
    else data1 +=String(hour);
    data1 +=':';
    if (minute<10) { data1 +='0'; data1 +=String(minute);}
    else data1 +=String(minute);
    data1 +=':';
    if (second<10) { data1 +='0'; data1 +=String(second);}
    else data1 +=String(second); 
    data1 +="\",\"";
    data1 +=String(status_machine); 
    data1 +="\",\"";
    data1 +=String(0);
    data1 +="\",\"INITIAL\",\"\""; 
      
}


void ResetBoard( uint8_t time) 
{
  wdt_enable(time);
  while(1) {}
}
