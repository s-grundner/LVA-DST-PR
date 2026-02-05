const int chargePin = 7; 
const int measurePin = A0;   
const float resistorValue = 10000.0; // Measurement

const int targetReading = 1023 * 0.632; 

unsigned long startTime;
unsigned long endTime;
float capacity;                

void setup() {
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(chargePin, LOW);
  while(analogRead(measurePin) > 0){
    //wait till empty
  }

  digitalWrite(chargePin, HIGH);
  startTime = micros();

  while(analogRead(measurePin) < targetReading){
	//wait till charged
  }

  endTime = micros() - startTime;
  
  capacity = (endTime / resistorValue);

  Serial.print("\\item Charge Time: ");
  Serial.print(endTime);
  Serial.println(" us");
  Serial.print("\\item Kapazität: ");
  Serial.print(capacity);
  Serial.println(" uF");

  delay(2000);
}