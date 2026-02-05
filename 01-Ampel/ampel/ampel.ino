// Rv = (Vout - Vd)/Id
// Rv = (5-3)V / 15 mA = 200 Ohm
// E6 Reihe -> 220 Ohm

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
  digitalWrite(RED, HIGH);
  delay(15000);
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(15000);

  for(int i = 0; i < 4; i++) {
    digitalWrite(GREEN, LOW);
    delay(500);
    digitalWrite(GREEN, HIGH);
    delay(500);
  }

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  digitalWrite(YELLOW,LOW);
}
