#include "inttypes.h"
#define WT_SIZE 20
#define DAC_MASK 0xF0
#define DAC_SHIFT 4

const uint8_t sinTable[WT_SIZE] = {
  0x8, 0xA, 0xC, 0xE,
  0xF, 0xF, 0xF, 0xE,
  0xC, 0xA, 0x8, 0x5,
  0x3, 0x2, 0x0, 0x0,
  0x0, 0x2, 0x3, 0x5
};
const uint16_t octaveFreqs[12] = {
  262, // C
  277, // C#
  294, // D
  311, // D#
  330, // E
  349, // F
  370, // F#
  392, // G
  315, // G#
  440, // A
  466, // A#
  494, // B
};

uint16_t keyboardToFreq(char key) {
  switch (key) {
    case 'a': return octaveFreqs[0];
    case 'w': return octaveFreqs[1];
    case 's': return octaveFreqs[2];
    case 'e': return octaveFreqs[3];
    case 'd': return octaveFreqs[4];
    case 'f': return octaveFreqs[5];
    case 't': return octaveFreqs[6];
    case 'g': return octaveFreqs[7];
    case 'z': return octaveFreqs[8];
    case 'h': return octaveFreqs[9];
    case 'u': return octaveFreqs[10];
    case 'j': return octaveFreqs[11];
  }
}

// Plays a 4-bit sine on the MSBs of PORTD
void playSine(uint16_t freq, uint16_t duration_ms) {
  uint32_t dt_us = 1000000 / (freq * WT_SIZE);

  uint32_t elapsed_us = 0;
  while (elapsed_us < duration_ms * 1000) {
    for (uint8_t i = 0; i < WT_SIZE; i++) {
      PORTD = (PORTD & ~DAC_MASK) | (sinTable[i] << DAC_SHIFT);
      delayMicroseconds(dt_us);
    } 
    elapsed_us += dt_us;
  }
}

void setup() {
  DDRD |= DAC_MASK; // Configure as output
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    uint16_t freq = noteToFreq(Serial.read());
    playSine(freq, 1000);
    delay(500);
  }
}
