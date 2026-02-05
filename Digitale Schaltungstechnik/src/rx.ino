#include "Arduino.h"
#include "inttypes.h"
#include "ir.h"

#define MORSE_TREE_LEN 31

static const char morseTree[MORSE_TREE_LEN] = {
    '\0',                                       // 0
    'E',  'T',                                  // 1
    'I',  'A', 'N', 'M',                        // 2
    'S',  'U', 'R', 'W',  'D', 'K',  'G',  'O', // 3
    'H',  'V', 'F', '\0', 'L', '\0', 'P',  'J',
    'B',  'X', 'C', 'Y',  'Z', 'Q',  '\0', '\0' // 4
};

const int RX_PIN = 1;

static morseUnit usToMorseUnit(uint32_t us);
static morseUnit usToMorseUnit(uint32_t us) {
  morseUnit unit = PAUSE;

  // Add one unit as threshold
  uint32_t dotThreshold_us = (DOT + UNIT) * UNIT_LEN_US;
  uint32_t dashThreshold_us = (DASH + UNIT) * UNIT_LEN_US;

  if (us < dotThreshold_us) {
    unit = DOT;
  } else if (us < dashThreshold_us) {
    unit = DASH;
  }
  return unit;
}

void setup() { Serial.begin(F_BAUD_BPS); }

void loop() {
  uint8_t morseTreeIdx = 0;
  uint32_t timeout = (PAUSE - UNIT) * UNIT_LEN_US;

  // IR Sensor yields LOW when receiving
  uint32_t meas_us = pulseIn(RX_PIN, LOW, timeout_us);

  while (meas_us && morseTreeIdx < MORSE_TREE_LEN) {
    enum morseUnit u = usToMorseUnit(meas_us);

    // Traverse binary morse tree
    morseTreeIdx = 2 * morseTreeIdx + (u == DOT) ? 1 : 2;
    meas_us = pulseIn(RX_PIN, LOW, timeout_us);
  }

  char letter = morseTree[morseTreeIdx];
  if (letter != '\0') {
    Serial.print(letter);
  }
}
