int led = 13;
int count = 0;

void KeepRolling(void)
{
  digitalWrite(led, HIGH);
  Serial.println("Led High");
  delay(1000);
  digitalWrite(led, LOW);
  Serial.println("Led Low");
  delay(1000);
  Serial.println(count++);
}

void setup()
{
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Initialization Complete");
}

void loop()
{
  KeepRolling();
}
