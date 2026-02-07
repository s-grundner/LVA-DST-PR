const int chargePin = 7; 
const int measurePin = A0; // Pin connected to the capacitor
const float R_REF = 9970.0; // Reference resistor value in ohms

const int targetReading = 1023 * 0.632; // Target reading for 63.2% charge

unsigned long startTime;
unsigned long endTime;
float capacity;                

void setup() {
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
  Serial.begin(9600); 
}

void loop() {
  // Discharge the capacitor
  digitalWrite(chargePin, LOW);
  while(analogRead(measurePin) > 0){
    //wait till empty
  }

  digitalWrite(chargePin, HIGH);
  startTime = micros();

  // Wait until the capacitor is charged to the target reading
  while(analogRead(measurePin) < targetReading){
	  //wait till charged
  }

  endTime = micros() - startTime;
  // Calculate the capacity
  capacity = (endTime / R_REF);

  Serial.print("Charge Time: ");
  Serial.print(endTime);
  Serial.println(" us");
  Serial.print("Kapazität: ");
  Serial.print(capacity);
  Serial.println(" uF");

  delay(2000);
}