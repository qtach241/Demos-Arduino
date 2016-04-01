#define led 13

int timer1_counter;
int count = 0;
char buffer[20];

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  digitalWrite(led, digitalRead(led) ^ 1);
}

void ProcessCommand(void)
{
  memset(buffer, 0, sizeof(buffer));
  if(Serial.available())
  {
    Serial.readBytesUntil('>', buffer, sizeof(buffer));
    Serial.write("Reply from Arduino: ");
    Serial.write(buffer);
  }
  if(buffer[0] != '<')
  {
    //Problem
  }
  switch(buffer[1])
  {
    case 'S': StartTest(buffer);
    case 'P': PauseTest();
    case 'R': ResetTest();
  }
}

void setup()
{
  pinMode(led, OUTPUT);

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  
  Serial.begin(115200);
  Serial.println("Initialization Complete");
}

void loop()
{
  ProcessCommand();
}
