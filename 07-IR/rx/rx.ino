#include "inttypes.h"

#define MORSE_TREE_LEN 31
#define F_IR_HZ 38000

// Number of UNITs representing a morse symbol
typedef enum {
  UNIT = 1,
  DOT = 5,
  DASH = 15,
  INTER_SYM = 3,
  PAUSE = 70
} morseUnit;

static const char morseTree[MORSE_TREE_LEN] = {
    '\0',                                       // 0
    'E',  'T',                                  // 1
    'I',  'A', 'N', 'M',                        // 2
    'S',  'U', 'R', 'W',  'D', 'K',  'G',  'O', // 3
    'H',  'V', 'F', '\0', 'L', '\0', 'P',  'J',
    'B',  'X', 'C', 'Y',  'Z', 'Q',  '\0', '\0' // 4
};

static const int RX_PIN = 3;
static const uint16_t UNIT_LEN_MS = 20;
static const uint32_t UNIT_LEN_US = UNIT_LEN_MS * 1000;
static const uint32_t TIMEOUT_US = (PAUSE - UNIT) * UNIT_LEN_US;

static const uint32_t DEBOUNCE_TIME_US = 10000;
static const uint32_t MIN_TIME_US = (DOT - 2*UNIT) * UNIT_LEN_US;
static const uint32_t DOT_THRESH_US = (DOT + UNIT) * UNIT_LEN_US;
static const uint32_t DASH_THRESH_US = (DASH + 4*UNIT) * UNIT_LEN_US;


uint32_t readDebouncedPulse() {
  uint32_t totalDuration = pulseIn(RX_PIN, LOW, TIMEOUT_US);
  if (totalDuration == 0) return 0;

  while (true) {
    uint32_t fragment = pulseIn(RX_PIN, LOW, DEBOUNCE_TIME_US);

    if (fragment == 0) {
      break;
    } else {
      totalDuration += fragment;
    }
  }
  
  return totalDuration;
}

void setup() {
  Serial.begin(9600);
  pinMode(RX_PIN, INPUT);
}

void loop() {
  uint8_t morseTreeIdx = 0;

  // IR Sensor yields LOW when receiving
  
  uint32_t meas_us = readDebouncedPulse();

  while (meas_us > MIN_TIME_US && morseTreeIdx < MORSE_TREE_LEN) {
    // Traverse binary morse tree
    if (meas_us < DOT_THRESH_US) {
      morseTreeIdx = 2 * morseTreeIdx + 1;
      Serial.print('.');
    } else if(meas_us < DASH_THRESH_US) {
      morseTreeIdx = 2 * morseTreeIdx + 2; 
      Serial.print('-');
    } else {
      break;
    }
    meas_us = readDebouncedPulse();
  }

  char letter = morseTree[morseTreeIdx];
  if (letter != '\0') {
    Serial.println(letter);
  }
}