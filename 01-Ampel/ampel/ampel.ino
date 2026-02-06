const uint8_t RED = 4;
const uint8_t YELLOW = 3;
const uint8_t GREEN = 2;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop()
{
  // Red for 15 seconds
  digitalWrite(RED, HIGH);
  delay(15000);
  // Red and Yellow for 2 seconds
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  // Green for 15 seconds
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(15000);

  // Flashing Green 4 times
  for(int i = 0; i < 4; i++) {
    digitalWrite(GREEN, LOW);
    delay(500);
    digitalWrite(GREEN, HIGH);
    delay(500);
  }
  // Yellow for 2 seconds
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  digitalWrite(YELLOW,LOW);
}
