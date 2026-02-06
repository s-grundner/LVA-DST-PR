const int pinA = 3;
const int pinB = 4;
const int pinY = 2;

void setup() {
  Serial.begin(9600);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinY, INPUT);
}

void loop() {
  int result00, result01, result10, result11;
  // Test all input combinations
  setInputs(0, 0);
  result00 = digitalRead(pinY);

  setInputs(0, 1);
  result01 = digitalRead(pinY);

  setInputs(1, 0);
  result10 = digitalRead(pinY);

  setInputs(1, 1);
  result11 = digitalRead(pinY);

  identifyGate(result00, result01, result10, result11);
  delay(1000);
}

void setInputs(int a, int b) {
  digitalWrite(pinA, a);
  digitalWrite(pinB, b);
  delay(50);
}

void identifyGate(int r00, int r01, int r10, int r11) {
  // Identify the logic gate based on the results
  if (r00 == 0 && r01 == 0 && r10 == 0 && r11 == 1) {
    Serial.println("AND Gate");
  } else if (r00 == 0 && r01 == 1 && r10 == 1 && r11 == 1) {
    Serial.println("OR Gate");
  } else if (r00 == 1 && r01 == 1 && r10 == 1 && r11 == 0) {
    Serial.println("NAND Gate");
  } else if (r00 == 1 && r01 == 0 && r10 == 0 && r11 == 0) {
    Serial.println("NOR Gate");
  } else if (r00 == 0 && r01 == 1 && r10 == 1 && r11 == 0) {
    Serial.println("XOR Gate");
  } else if (r00 == 1 && r01 == 0 && r10 == 0 && r11 == 1) {
    Serial.println("XNOR Gate");
  } else {
    Serial.println("Error");
  }
}
