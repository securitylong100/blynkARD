#include <ESP8266WiFi.h>
int val = 8888;
int tranfer;
bool check = false;
int button = 16; // là tx Gắn D9
int led8 = 0;
int led = LED_BUILTIN;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led8, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  while (Serial.available())
  {
    val = Serial.read();
    // Serial.println(val);
    delay(200);
  }
  if (val == '0' )
  {
    digitalWrite(led8, HIGH);
    digitalWrite(led, LOW);
    tranfer = '00';
    Serial.println ("LED Dang Tat ");

  } else if (val == '1')
  {
    digitalWrite(led8, LOW);
    digitalWrite(led, HIGH);
    tranfer = '11';
    Serial.println ("LED Dang Sáng ");
  }

  if (digitalRead(button) == HIGH)
  {
    digitalWrite(led8, HIGH);
    digitalWrite(led, LOW);
    Serial.write("on");
    delay (200);
  }
  else { // ngược lại
    digitalWrite(led8, LOW);
    digitalWrite(led, HIGH);
    Serial.write("off");
    delay (200);
  }

  //Serial.write(tranfer);
  //delay (1000);
}
