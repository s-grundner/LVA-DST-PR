#include "inttypes.h"

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

typedef struct {
  uint8_t code; // 0 for dot, 1 for dash
  uint8_t len;  // number of syms
} morseCode;

static const morseCode morseTable[26] = {
    {0b01, 2},   // A
    {0b1000, 4}, // B
    {0b1010, 4}, // C
    {0b100, 3},  // D
    {0b0, 1},    // E
    {0b0010, 4}, // F
    {0b110, 3},  // G
    {0b0000, 4}, // H
    {0b00, 2},   // I
    {0b0111, 4}, // J
    {0b101, 3},  // K
    {0b0100, 4}, // L
    {0b11, 2},   // M
    {0b10, 2},   // N
    {0b111, 3},  // O
    {0b0110, 4}, // P
    {0b1101, 4}, // Q
    {0b010, 3},  // R
    {0b000, 3},  // S
    {0b1, 1},    // T
    {0b001, 3},  // U
    {0b0001, 4}, // V
    {0b011, 3},  // W
    {0b1001, 4}, // X
    {0b1011, 4}, // Y
    {0b1100, 4}  // Z
};

const int TX_PIN = 3;
static const uint16_t UNIT_LEN_MS = 200;
static const uint32_t UNIT_LEN_US = 200000;

static void sendMorseChar(char c);
static void sendMorseChar(char c) {
  uint8_t idx = 0;
  if (c >= 'a' && c <= 'z') {
    idx = c - 'a';
  } else if (c >= 'A' && c <= 'Z') {
    idx = c - 'A';
  } else {
    return;
  }

  morseCode m = morseTable[idx];

  for (int i = m.len - 1; i >= 0; i--) {
    tone(TX_PIN, F_IR_HZ);
    if (m.code & (1 << i)) {
      delay(DASH * UNIT_LEN_MS);
    } else {
      delay(DASH * UNIT_LEN_MS);
    }
    noTone();
    delay(INTER_SYM * UNIT_LEN_MS);
  }
  delay(PAUSE * UNIT_LEN_MS);
}

void setup() {
  Serial.begin(F_BAUD_BPS);
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, HIGH);
}

void loop() {
  // if (Serial.available() > 0) {
  //  sendMorseChar(Serial.read());
  // }
  
  sendMorseChar('Q');
  sendMorseChar('S');
  sendMorseChar('L');
}