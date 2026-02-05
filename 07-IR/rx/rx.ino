#include "inttypes.h"

#define MORSE_TREE_LEN 31
#define F_IR_HZ 38000
#define F_BAUD_BPS 9600

// Number of UNITs representing a morse symbol
typedef enum {
  UNIT = 1,
  DOT = 1,
  DASH = 3,
  INTER_SYM = 1,
  PAUSE = 7
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
static const uint16_t UNIT_LEN_MS = 200;
static const uint32_t UNIT_LEN_US = 200000;
static const uint32_t TIMEOUT_US = (PAUSE - UNIT) * UNIT_LEN_US;
static const uint32_t DOT_THRESH_US = (DOT + UNIT) * UNIT_LEN_US;
static const uint32_t DASH_THRESH_US = (DASH + UNIT) * UNIT_LEN_US;

void setup() {
  Serial.begin(F_BAUD_BPS);
  pinMode(RX_PIN, INPUT);
}


void loop() {
  uint8_t morseTreeIdx = 0;

  // IR Sensor yields LOW when receiving
  uint32_t meas_us = pulseIn(RX_PIN, LOW, TIMEOUT_US);

  while (meas_us && morseTreeIdx < MORSE_TREE_LEN) {
    // Traverse binary morse tree
    if (meas_us < DOT_THRESH_US) {
      morseTreeIdx = 2 * morseTreeIdx + 1;
    } else if(meas_us < DASH_THRESH_US) {
      morseTreeIdx = 2 * morseTreeIdx + 2; 
    } else {
      break;
    }
    meas_us = pulseIn(RX_PIN, LOW, TIMEOUT_US);
  }

  char letter = morseTree[morseTreeIdx];
  if (letter != '\0') {
    Serial.println(letter);
  }
}