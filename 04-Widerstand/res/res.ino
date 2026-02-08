const int analogPin = A1; // Pin connected to the voltage divider
const float R_REF = 9970.0; // Reference resistor value in ohms
const float VCC = 5.0; // Supply voltage

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
}

void loop() {
  // Read the analog value
  int rawValue = analogRead(analogPin);
  // Convert the analog value to voltage
  float u_x = rawValue * (VCC / 1023.0);
  // Calculate the resistance
  float r_x = R_REF * (u_x / (VCC - u_x));

  Serial.print(r_x);
  Serial.println(" Ohms");
  delay(1000);
}
