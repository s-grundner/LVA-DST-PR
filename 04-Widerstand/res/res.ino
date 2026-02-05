const int analogPin = A1;
const float R_REF = 9970.0; // Measurement
const float VCC = 5.0;

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
}

void loop() {
  int rawValue = analogRead(analogPin);
  float u_x = rawValue * (VCC / 1024.0);
  float r_x = R_REF * (u_x / (VCC - u_x));

  Serial.print(r_x);
  Serial.print(", ");
  Serial.println(rawValue);

  delay(1000);
}
