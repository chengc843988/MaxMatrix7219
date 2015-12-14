
#include <Arduino.h>
#include "MaxMatrix.h"
#include <avr/pgmspace.h>

#define DATA_PIN 12
#define CS_PIN 11
#define CLOCK_PIN 10

#define MATRIX_DEVICES 4
#define MAXMATRIX_DELAY 50
MaxMatrix lc(DATA_PIN, CS_PIN, CLOCK_PIN, MATRIX_DEVICES);

byte charBuffer[32];


const PROGMEM byte char_WORM[]  = {
  0x00, 0x00,
  0x00, 0x3C,
  0x03, 0xC3,
  0x79, 0x22,
  0x48, 0x94,
  0x48, 0x00,
  0x4B, 0xFE,
  0x78, 0x80,
  0x4F, 0xFF,
  0x48, 0x80,
  0x48, 0xFC,
  0x79, 0x84,
  0x4A, 0x48,
  0x44, 0x30,
  0x00, 0xCC,
  0x07, 0x03
};
const byte PROGMEM char_SPRING[] = {
  0x00, 0x00,
  0x01, 0x80,
  0x01, 0x00,
  0x3F, 0xFE,
  0x02, 0x00,
  0x1F, 0xFC,
  0x04, 0x00,
  0x7F, 0xFF,
  0x08, 0x08,
  0x10, 0x04,
  0x6F, 0xFB,
  0x08, 0x08,
  0x0F, 0xF8,
  0x08, 0x08,
  0x0F, 0xF8,
  0x08, 0x08
};

const byte PROGMEM char_FLOWER[] = {
  0x00, 0x00,
  0x06, 0x18,
  0x04, 0x10,
  0x7F, 0x7F,
  0x04, 0x10,
  0x00, 0x00,
  0x0C, 0xC0,
  0x08, 0x80,
  0x10, 0x84,
  0x10, 0xFE,
  0x30, 0x80,
  0x50, 0x80,
  0x10, 0x82,
  0x10, 0x82,
  0x10, 0x83,
  0x10, 0x7E
};

const byte PROGMEM char_OPEN[] = {
  0x00, 0x00,
  0x21, 0x42,
  0x3F, 0x7F,
  0x21, 0x42,
  0x3F, 0x7E,
  0x21, 0x42,
  0x3F, 0x7E,
  0x20, 0x02,
  0x27, 0xF2,
  0x22, 0x22,
  0x22, 0x22,
  0x2F, 0xFA,
  0x22, 0x22,
  0x22, 0x22,
  0x24, 0x2E,
  0x20, 0x04
};
const byte char_QUICK[] PROGMEM = {
  0x00, 0x00,
  0x18, 0x60,
  0x10, 0x40,
  0x10, 0x44,
  0x13, 0xFE,
  0x58, 0x44,
  0x54, 0x44,
  0x54, 0x44,
  0x10, 0x44,
  0x17, 0xFF,
  0x10, 0x40,
  0x10, 0x50,
  0x10, 0x88,
  0x10, 0x84,
  0x11, 0x06,
  0x16, 0x02
};
const byte char_MUSIC[] PROGMEM = {
  0x00, 0x00,
  0x18, 0x86,
  0x11, 0x04,
  0x27, 0xE9,
  0x7A, 0x3E,
  0x13, 0xE4,
  0x2A, 0x2A,
  0x7B, 0xFF,
  0x4A, 0x31,
  0x00, 0x80,
  0x7F, 0xFF,
  0x00, 0x80,
  0x04, 0x98,
  0x08, 0x86,
  0x10, 0x83,
  0x60, 0x81
};

const byte char_MOON[] PROGMEM = {
  0x00, 0x00,
  0x08, 0x08,
  0x0F, 0xFC,
  0x08, 0x08,
  0x08, 0x08,
  0x0F, 0xF8,
  0x08, 0x08,
  0x08, 0x08,
  0x08, 0x08,
  0x0F, 0xF8,
  0x08, 0x08,
  0x08, 0x08,
  0x08, 0x08,
  0x10, 0x08,
  0x10, 0x78,
  0x20, 0x10
};
const byte char_CYCLE[] PROGMEM = {
  0x00, 0x00,
  0x20, 0x02,
  0x3F, 0xFF,
  0x20, 0x02,
  0x23, 0xE2,
  0x22, 0x22,
  0x27, 0xF2,
  0x24, 0x12,
  0x27, 0xF2,
  0x24, 0x12,
  0x27, 0xF2,
  0x21, 0x42,
  0x26, 0x32,
  0x20, 0x02,
  0x3F, 0xFE,
  0x20, 0x02
};

const byte char_GOOD[] PROGMEM = {
  0x00, 0x00,
  0x18, 0x02,
  0x10, 0xFF,
  0x12, 0x02,
  0x7F, 0x04,
  0x12, 0x18,
  0x12, 0x10,
  0x22, 0x12,
  0x25, 0xFF,
  0x74, 0x10,
  0x18, 0x10,
  0x0C, 0x10,
  0x12, 0x10,
  0x22, 0x10,
  0x40, 0x70,
  0x00, 0x20
};

const byte char_MERRY_1[] PROGMEM = {
  0x00, 0x00,
  0x01, 0x00,
  0x7F, 0xA2,
  0x11, 0x3F,
  0x1F, 0x22,
  0x11, 0x22,
  0x1F, 0x22,
  0x11, 0x3E,
  0x7F, 0x22,
  0x21, 0x00,
  0x00, 0xF8,
  0x1F, 0x80,
  0x00, 0x88,
  0x3F, 0xFC,
  0x00, 0x80,
  0x7F, 0xFF
};

const byte char_MERRY_2[] PROGMEM = {
  0x00, 0x00,
  0x20, 0x06,
  0x10, 0x9C,
  0x13, 0xC4,
  0x7C, 0x84,
  0x00, 0x84,
  0x3D, 0x14,
  0x01, 0xD7,
  0x3D, 0x54,
  0x00, 0x54,
  0x25, 0x54,
  0x3D, 0x54,
  0x24, 0xBF,
  0x24, 0xC0,
  0x3D, 0x30,
  0x25, 0x0F
};




void setup() {
  lc.init();
  lc.setIntensity(0);
  lc.clear();
  Serial.begin(115200);
  Serial.println("Start test....");
}

void rowTest() {
  for (int d = 0; d < MATRIX_DEVICES; d++) {
    Serial.print("Test:"); Serial.println(d, HEX);
    for (int r = 0; r < 8; r++) {
      byte row = r + d * 8;
      lc.clear();
      lc.setRow(row, 0xff);
      delay(MAXMATRIX_DELAY);
      lc.setRow(row, 0x00);
      delay(100);
    }
  }
}

void columnTest() {
  for (int d = 0; d < MATRIX_DEVICES; d++) {
    Serial.print("Test:"); Serial.println(d, HEX);
    for (int r = 0; r < 8; r++) {
      byte row = r + d * 8;
      lc.clear();
      lc.setColumn(row, 0xff);
      delay(MAXMATRIX_DELAY);
      lc.setColumn(row, 0x00);
      delay(50);
    }
  }
}

void dotTest() {
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 16; x++) {
      lc.setDot(x, y, 1);
      delay(1);
      lc.setDot(x, y, 0);
    }
  }
  lc.clear();
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 16; x++) {
      lc.setDot(y, x, 1);
      delay(1);
      lc.setDot(y, x, 0);
    }
  }
}

void downTest() {
  //lc.setDot(0,0,1);
  // lc.setDot(8,8,1);
  lc.setRow(0, 0xff);
  lc.setRow(8, 0xff);
  lc.setRow(16, 0xff);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.shiftDown(true, false);
      delay(300);
    }
    // lc.shiftUp(true);
  }
}
void upTest() {
  //lc.setDot(0,0,1);
  // lc.setDot(8,8,1);
  lc.setRow(0, 0xff);
  lc.setRow(8, 0xff);
  lc.setRow(16, 0xff);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.shiftUp(true, false);
      delay(300);
    }
    // lc.shiftUp(true);
  }
}

void leftTest() {
  //lc.setDot(0,0,1);
  // lc.setDot(8,8,1);
  lc.setColumn(0, 0xff);
  lc.setColumn(8, 0xff);
  lc.setColumn(16, 0xff);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.shiftLeft(true, false);
      delay(300);
    }
    // lc.shiftUp(true);
  }
}

void rightTest() {
  //lc.setDot(0,0,1);
  // lc.setDot(8,8,1);
  lc.setColumn(0, 0xff);
  lc.setColumn(8, 0xff);
  lc.setColumn(16, 0xff);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.shiftRight(true, false);
      delay(300);
    }
    // lc.shiftUp(true);
  }
}

///////////////////////////////////
void charTest() {
  lc.loadCharBuffer(char_QUICK, charBuffer, 32);
  lc.displayChar(charBuffer, 32);
  delay(1000);

  lc.loadCharBuffer(char_MUSIC, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(5000);

  lc.loadCharBuffer(char_SPRING, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_WORM, charBuffer, 32);
  lc.shiftRightIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_FLOWER, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_OPEN, charBuffer, 32);
  lc.shiftRightIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_FLOWER, charBuffer, 32);
  lc.shiftUpIn(charBuffer, 32);
  delay(3000);
  lc.loadCharBuffer(char_GOOD, charBuffer, 32);
  lc.shiftDownIn(charBuffer, 32);
  delay(3000);
  lc.loadCharBuffer(char_MOON, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_CYCLE, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);



  lc.loadCharBuffer(char_MERRY_1, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_MERRY_2, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_QUICK, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);

  lc.loadCharBuffer(char_MUSIC, charBuffer, 32);
  lc.shiftLeftIn(charBuffer, 32);
  delay(3000);
}

/*
  void displayChar(const byte chars[] PROGMEM, int len) {
  lc.clear();
  byte p, x;
  for (int i = 0; i < len; i++) {
    x = 31 - i;
    p = (i & 0x01) ? 0 : 16;
    lc.setRow(i / 2 + p, Bit_Reverse(chars[x]));
  }
  debufPrint();
  delay(100);
  }
*/


// =====================================================
void randomtest() {
  for (int i = 0; i < 100; i++) {
    long now = millis();
    byte b = millis() & 0x07;
    switch (b) {
      case 0:
        lc.setDot((now & 0x58) >> 3, (now & 0xf0) >> 5, 1 );
        break;
      case 1:
        lc.setDot((now & 0x58) >> 3, (now & 0xf0) >> 5, 0 );
        break;
      case 2:
        lc.shiftRight(1, 1);
        break;
      case 3:
        lc.shiftUp(1, 1);
        break;
      case 4:
        lc.shiftDown(1, 1);
        break;
      case 5:
        lc.shiftLeft(1, 1);
        break;
      case 6:
        lc.setColumn((now & 0xf0) >> 4, now & 0xff );
        break;
      case 7:
        lc.setRow((now & 0xf0) >> 4, now & 0xff);
        break;
    }
    delay(100);
  }
}


void loop() {
  Serial.print("Loop....."); Serial.println(millis(), HEX);
  // rowTest();
  // columnTest();
  // dotTest();
  // downTest();
  // upTest();
  // leftTest();
  // rightTest();
  // put your main code here, to run repeatedly:
  //   randomtest();
  charTest();
}

// const byte clearESC[] = {033, 0133, 062, 0112};
const char *clearESC = "\033\0133\062\012";
void debufPrint() {
  uint8_t *p = lc.getBuffer();

  Serial.println(clearESC);
  Serial.println("------------------------------------------------------------");
  uint8_t ch, b;
  for (int i = 15; i >= 0; i--) {
    ch = p[i];
    for (int c = 0; c < 8; c++) {
      b = ch & 0x01;
      Serial.print( (b) ? '*' : ' ');
      ch >>= 1;
    }
    ch = p[i + 16];
    for (int c = 0; c < 8; c++) {
      b = ch & 0x01;
      Serial.print( (b) ? '*' : ' ');
      ch >>= 1;
    }
    Serial.println("/");
  }

}
