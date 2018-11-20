int val = 8888;
int tranfer;
int button = 9; // là tx Gắn D9
int led1 = 3;
int led = LED_BUILTIN;
void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
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
    digitalWrite(led1, LOW);
    digitalWrite(led, LOW);
    tranfer = '00';
    Serial.println ("LED Dang Tat ");
    delay (1000);
  } else if (val == '1')
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led, HIGH);
    tranfer = '11';
    Serial.println ("LED Dang Sáng ");
    delay (1000);
  }
  /*
  if (digitalRead(button) == HIGH)
  {
    digitalWrite(led, HIGH);
    Serial.println ("Button làm sáng");
    delay (1000);
  }
  else { // ngược lại
    digitalWrite(led, LOW);
    Serial.println ("Button làm tắt ");
    delay (1000);
  }
  */
  // Serial.write(tranfer);
  //delay (1000);
}
