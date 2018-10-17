#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "a72488240cb24d7e979684466c809887";        //Token cua blynk
//char ssid[] = "iPhone";        //Ten wifi
//char pass[] = "longcoi12345";         //Pass wifi
//char ssid[] = "TaoLaGa49";    
//char pass[] = "longcoi123";

char ssid[] = "Connectify-NSTV";    
char pass[] = "passpass2018";



void setup() {
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass);        // Ket noi voi blynk
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
}
BLYNK_WRITE(3)
{
  int i = param.asInt();
  if (i == 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(2, LOW);
  }
}

BLYNK_WRITE(2)
{
  int i = param.asInt();
  while (true)
  {
    if(i==0) break;
    {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay (100);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}
void loop()
{
  for (int i = 100; i < 1000; i = i + 50)
  {
    Blynk.virtualWrite(V1, i); //up
    Serial.printf("nhiet do dang la: %d \n", i);
    Blynk.run(); // Chay Blynk
    delay (100);
  }
}
