
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "a72488240cb24d7e979684466c809887";        //Token cua blynk
char ssid[] = "iPhone";        //Ten wifi
char pass[] = "longcoi12345";         //Pass wifi
//char ssid[] = "TaoLaGa49";
//char pass[] = "longcoi123";

void setup() {
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass);        // Ket noi voi blynk
  pinMode(16, OUTPUT);//phong khach V1
  pinMode(0, OUTPUT); //phong ngu V2
  pinMode(3, OUTPUT); //nha tam V3

}
BLYNK_WRITE(1) //khoi tao phong khach
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(16, HIGH);
  }
  else
  {
    digitalWrite(16, LOW);
  }
}

BLYNK_WRITE(2) //khoi tao phong ngu
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(0, HIGH);
  }
  else
  {
    digitalWrite(0, LOW);
  }
}
BLYNK_WRITE(3) //khoi tao nha tam
{
  int i = param.asInt();
  if (i == 1)
  {
    digitalWrite(3, HIGH);
  }
  else
  {
    digitalWrite(3, LOW);
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
