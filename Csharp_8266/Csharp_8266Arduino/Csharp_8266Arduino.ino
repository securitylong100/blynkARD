#include <ESP8266WiFi.h>
int val = 8888;
int tranfer;
bool check = false;
int button = 16; // gan chân d2
int led4 = 4; //ok gan chân 0
int led6 = 12; //ok gan chân 0
int led7 = 13; //ok gan chân 0

int led = LED_BUILTIN;


void setup() {
  pinMode(button, INPUT);
  pinMode(led4, OUTPUT);
  pinMode (led6, OUTPUT);
  pinMode(led7, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  while (Serial.available())
  {
    val = Serial.read();
    // Serial.println(val);
    delay(200);
  }
  if (val == '5' )
  {
    digitalWrite(led4, LOW);
  }
  if (val == '6' )
  {
    digitalWrite(led6, LOW);
  }
  if (val == '7' )
  {
    digitalWrite(led7, LOW);
    Serial.println ("LED Dang Tat ");
  }
  else if (val == '1')
  {
    digitalWrite(led4, HIGH);
    Serial.println ("LED Dang Sáng ");
    delay (250);
    digitalWrite(led4, LOW);
  }
  else if (val == '2')
  {
    digitalWrite(led6, HIGH);
    Serial.println ("LED Dang Sáng ");
    delay (250);
    digitalWrite(led6, LOW);
  }
  else if (val == '3')
  {
    digitalWrite(led7, HIGH);
    Serial.println ("LED Dang Sáng ");
     delay (250);
    digitalWrite(led7, LOW);
  }

}
