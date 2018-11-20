int val = 8888;
int tranfer;

int led = LED_BUILTIN;
int output = 9;
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  while (Serial.available())
  {
    val = Serial.read();
    Serial.println(val);
    delay(200);
  }
  if (val == '0' )
  {
    digitalWrite(led, LOW);
    tranfer = '00';
    digitalWrite(output, LOW);

  } else if (val == '1')
  {
    digitalWrite(led, HIGH);
    tranfer = '11';
    digitalWrite(output, HIGH);
  }
 // Serial.write(tranfer);
  //delay (1000);
}
