const int ledPins[] = {3, 4, 5, 6, 7};
const int buttonPin = 2;
const int targetLed = 5;

int currentLed = 0;
unsigned long lastUpdate = 0;
int interval = 1000;

volatile bool wasPressed = false;
volatile int pressedLed = -1;
volatile unsigned long lastInterruptTime = 0;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handlePress, FALLING);
  digitalWrite(ledPins[currentLed], HIGH);
  Serial.begin(9600);
}
void loop() {
  if (wasPressed) {
    checkPressed();
    wasPressed = false; 
  }

  if (millis() - lastUpdate >= interval) {
    lastUpdate = millis();
    digitalWrite(ledPins[currentLed], LOW);
    currentLed = (currentLed + 1) % 5;
    digitalWrite(ledPins[currentLed], HIGH);
  }
}

void checkPressed() {
  if(ledPins[pressedLed] != targetLed) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 5; j++) {
        digitalWrite(ledPins[j], HIGH);
      }
      delay(200);
      for (int j = 0; j < 5; j++) {
        digitalWrite(ledPins[j], LOW);
      }
      delay(200);
    }
    interval = 1000;
    currentLed = 0;
    digitalWrite(ledPins[currentLed], HIGH);
    lastUpdate = millis();
  } else {
    interval /= 2;
    lastUpdate = millis();
  }
}

void handlePress() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    wasPressed = true;
    pressedLed = currentLed;
    lastInterruptTime = interruptTime;
  }
}
