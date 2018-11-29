
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "a72488240cb24d7e979684466c809887";        //Token cua blynk
//char auth[] = "4a21fc54ff7742b489e99c161c1e42df"; //key thuy
char ssid[] = "Kumi";        //Ten wifi
char pass[] = "kumi12345";         //Pass wifi
//char ssid[] = "82 LAU 1";
//char pass[] = "123456789";

void setup() {
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass);        // Ket noi voi blynk
  pinMode(12, OUTPUT);//phong khach V1
  pinMode(13, OUTPUT); //phong ngu V2
  pinMode(14, OUTPUT); //nha tam V3

}
BLYNK_WRITE(1) //khoi tao phong khach
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(12, HIGH);
  }
  else
  {
    digitalWrite(12, LOW);
  }
}

BLYNK_WRITE(2) //khoi tao phong ngu
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}
BLYNK_WRITE(3) //khoi tao nha tam
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(14, HIGH);
  }
  else
  {
    digitalWrite(14, LOW);
  }
}
//ket thuc 3 nut nhan.
void loop()
{
  for (int i = 100; i < 1000; i = i + 50)
  {
    Blynk.virtualWrite(V0, i); //chay bien nhiet do
    Serial.printf("nhiet do dang la: %d \n", i);
    Blynk.run(); // Chay Blynk
    delay (1000);
  }
}
