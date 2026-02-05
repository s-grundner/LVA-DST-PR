const int SHIFT_IN=4;
const int SHIFT_OUTPUT=5;
const int SHIFT_CLK=6;

const int BUTTON_UP = 2;
const int BUTTON_DOWN = 3;

volatile int currentNumber = 0;
volatile bool needsUpdate = true;

unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;

const uint8_t segmentPatterns[] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100000, // 7
  0b11111110, // 8
  0b11110110  // 9
};

void setup() {
  pinMode(SHIFT_IN, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_OUTPUT, OUTPUT);
  
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), countUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), countDown, FALLING);
}
  
void loop() {
  if(needsUpdate) {
    needsUpdate = false;
    setShiftRegister(currentNumber);
  }
}

void countUp() {
  unsigned long time = millis();
  if (time - lastInterruptTime > debounceDelay) {
    if(currentNumber >= 9) {
      currentNumber = 0;
    } else {
      currentNumber++; 
    }
    needsUpdate = true;
  }
  lastInterruptTime = time;
}

void countDown() {
  unsigned long time = millis();
  if (time - lastInterruptTime > debounceDelay) {
    if(currentNumber <=0) {
      currentNumber = 9;
    } else {
      currentNumber--; 
    }
    needsUpdate = true;
  }
  lastInterruptTime = time;
}


void setShiftRegister(int number) {
  digitalWrite(SHIFT_OUTPUT, LOW);
  shiftOut(SHIFT_IN, SHIFT_CLK, LSBFIRST, segmentPatterns[number]);
  digitalWrite(SHIFT_OUTPUT, HIGH);
}
