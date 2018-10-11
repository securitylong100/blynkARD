#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "2d6ec2f6e3bd4cb6b5ab9c0de16e0f64";        //Token cua blynk
char ssid[] = "Redmi";        //Ten wifi
char pass[] = "12345678";         //Pass wifi

void setup() {
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass);        // Ket noi voi blynk
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  for (int i = 100; i < 1000; i = i + 50)
  {
    Blynk.virtualWrite(V4, i); //up
    digitalWrite(LED_BUILTIN, LOW);
    delay (500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay (500);
   Serial.printf("nhiet do dang la: %d \n", i);
    Blynk.run(); // Chay Blynk
  }

}
