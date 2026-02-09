const int SHIFT_IN=4;
const int SHIFT_OUTPUT=5;
const int SHIFT_CLK=6;

const int BUTTON_UP = 2;
const int BUTTON_DOWN = 3;

volatile int currentNumber = 0;
volatile bool needsUpdate = true;

unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;


const int MOTOR_LED_OFF=9;
const int MOTOR_LED_ON=8;
const int MOTOR_PWM_LEFT=10;
const int MOTOR_PWM_RIGHT=11;

volatile int motorSpeed = 0;

const int SENSOR_TRIGGER = 13;
const int SENSOR_ECHO = 12;

unsigned long lastSensorTime = 0;
unsigned long sensorPeriodMillis = 60;

volatile boolean turnsRight = true;
volatile boolean motorOff = false;
  
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

void setup()
{
  Serial.begin(9600);
  
  pinMode(SHIFT_IN, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_OUTPUT, OUTPUT);
  
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_LED_OFF, OUTPUT);
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  
  pinMode(MOTOR_LED_OFF, OUTPUT);
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_RIGHT, OUTPUT);
  
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(MOTOR_LED_ON, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), countUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), countDown, FALLING);

  pinMode(SENSOR_TRIGGER, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
  
  setShiftRegister(currentNumber);
  setMotorSpeed(currentNumber, turnsRight, motorOff);
  digitalWrite(SENSOR_TRIGGER, HIGH);
}
  
void loop()
{
  if(needsUpdate) {
    needsUpdate = false;
    setShiftRegister(currentNumber);
    setMotorSpeed(currentNumber, turnsRight, motorOff);
  }
  
  unsigned long time = millis();
  if(time - sensorPeriodMillis > lastSensorTime) {
    float distance = getDistance();
    Serial.print(distance);
    Serial.println(" cm");
    
    if((distance < 30.0) != motorOff) {
      motorOff = distance < 30.0;
      setMotorSpeed(currentNumber, turnsRight, motorOff);
    }
    lastSensorTime = time;
  }
}

void countUp() {
  int time = millis();
  if (time - lastInterruptTime > debounceDelay) {
    if(turnsRight) {
      turnsRight = false;
      currentNumber = 0;
    } else {
      if(currentNumber >= 9) {
        currentNumber = 0   ;
      } else {
        currentNumber++; 
      }
    }
    needsUpdate = true;
  }
  lastInterruptTime = time;
}

void countDown() {
  int time = millis();
  if (time - lastInterruptTime > debounceDelay) {
    if(!turnsRight) {
      turnsRight = true;
      currentNumber = 0;
    } else {
      if(currentNumber >= 9) {
        currentNumber = 0   ;
      } else {
        currentNumber++; 
      }
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

void setMotorSpeed(int number, bool turnsRight, bool motorOff) {
  int currentPin;
  int otherPin;
  
  if(motorOff) {
    analogWrite(MOTOR_PWM_LEFT, 0);
    analogWrite(MOTOR_PWM_RIGHT, 0);
    digitalWrite(MOTOR_LED_ON, LOW);
    digitalWrite(MOTOR_LED_OFF, HIGH);
    return;
  }
  
  if(turnsRight) {
    currentPin = MOTOR_PWM_RIGHT;
    otherPin = MOTOR_PWM_LEFT;
  } else {
    currentPin = MOTOR_PWM_LEFT;
    otherPin = MOTOR_PWM_RIGHT;
  }
  analogWrite(otherPin, 0);
  
  int pwmValue = map(number, 0, 9, 0, 255);
  analogWrite(currentPin, pwmValue);
  
  if(number != 0) {
    digitalWrite(MOTOR_LED_OFF, LOW);
    digitalWrite(MOTOR_LED_ON, HIGH);
  } else {
    digitalWrite(MOTOR_LED_ON, LOW);
    digitalWrite(MOTOR_LED_OFF, HIGH);
  }
}

float getDistance() {
  digitalWrite(SENSOR_TRIGGER, LOW);
  delayMicroseconds(20);
    
  long duration = pulseIn(SENSOR_ECHO, HIGH, 200000);
  if (duration <= 0) duration = 200000;  
  float distance = (duration * 0.0343) / 2;
  
  digitalWrite(SENSOR_TRIGGER, HIGH);
  return distance;
}