#define UNIT_LEN_MS 10
#define UNIT_LEN_US (UNIT_LEN_MS * 1000)
#define F_IR_HZ 38000
#define F_BAUD_BPS 9800

// Number of UNITs representing a morse symbol
typedef enum {
  UNIT = 1,
  DOT = 1,
  DASH = 3,
  INTER_SYM = 1,
  PAUSE = 7
} morseUnit;
