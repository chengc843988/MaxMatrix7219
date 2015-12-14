

#include "Arduino.h"
#include "MaxMatrix.h"


#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08
#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0a
#define max7219_reg_scanLimit   0x0b
#define max7219_reg_shutdown    0x0c
#define max7219_reg_displayTest 0x0f


MaxMatrix::MaxMatrix(byte _data, byte _load, byte _clock, byte _num,void (* _debugPrint)()) 
{
	data = _data;
	load = _load;
	clock = _clock;
        rows=2;
        cols=2;
	num = _num;
        debugPrint = _debugPrint;
	for (int i=0; i<MAX_BUFFER_SIZE; i++) buffer[i] = 0;
}

void MaxMatrix::init()
{
	pinMode(data,  OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(load,  OUTPUT);
	digitalWrite(clock, HIGH); 

	setCommand(max7219_reg_scanLimit, 0x07);      
	setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
	setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
	setCommand(max7219_reg_displayTest, 0x00); // no display test
	
	// empty registers, turn all LEDs off
	clear();
	
	setIntensity(0x0f);    // the first 0x0f is the value you can set
}

void MaxMatrix::setIntensity(byte intensity)
{
	setCommand(max7219_reg_intensity, intensity);
}

void MaxMatrix::clear()
{
	for (int i=0; i<MAX_BUFFER_SIZE; i++)
		buffer[i] = 0;
	for(int i=0;i<8;i++) refreshRow(i);
}

void MaxMatrix::setCommand(byte command, byte value)
{
	digitalWrite(load, LOW);    
	for (int i=num; i>0; i--) 
	{
		shiftOut(data, clock, MSBFIRST, command);
		shiftOut(data, clock, MSBFIRST, value);
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
}
void MaxMatrix::refreshRow(byte row)
{
	// byte d= ((row >>3 ) & 0x07) +1;
	int r = (row & 0x07) ;
	digitalWrite(load, LOW);    
	for (int i=num-1; i>=0; i--) 
	{
		shiftOut(data, clock, MSBFIRST, r+1);
		// shiftOut(data, clock, MSBFIRST, ((i==d)?(r+1):max7219_reg_noop));
		shiftOut(data, clock, MSBFIRST, buffer[i*8+r]);
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
}

void MaxMatrix::refresh(){
	for(int i=0;i<8;i++) refreshRow(i);
}
 

void MaxMatrix::setRow(byte row, byte value) {
	buffer[row] = value;
	refreshRow(row);
}

void MaxMatrix::setColumn(byte col, byte value) {
	byte c = col & 0x07;
	byte base=col & 0xf8;
	byte a=(1<<c);
	for(byte i=0;i<8;i++) {
		byte b=value & (1 << i);
		if(b!=0) buffer[base+i] |= (a); 
                else buffer[base+i] &= ~(a);
	}
	refresh();
}


void MaxMatrix::setDot(byte col, byte row, byte value)
{
    if(col>=8) {
	row+=16;
        col-=8;
    }
    if(value) buffer[row] |= (1<<col);
    else  buffer[row] &= ~(1<<col);
    refreshRow(row);
}

void MaxMatrix::shiftRight(bool rotate, bool fill_zero)
{
	for(int i=0;i<16;i++) {
          byte a=buffer[i] & 0x80, b=buffer[i+16] & 0x80;
	  buffer[i] <<=1; buffer[i+16]<<=1;
          if(a) buffer[i+16] |=0x01; 
          if(b) buffer[i] |=0x01; 
	}
	refresh();
}

void MaxMatrix::shiftLeft(bool rotate, bool fill_zero)
{
	uint8_t a, b,c;
	for(byte i=0;i<16;i++) {
          a=buffer[i]    & 0x01;
          b=buffer[i+16] & 0x01;
	  c=(buffer[i]   >>1)& 0x7f;
	  buffer[i]   =c; 
	  c=(buffer[i+16]>>1) & 0x7f;
          buffer[i+16]=c;
          if(a!=0) buffer[i+16] = buffer[i+16] | 0x80; 
          if(b!=0) buffer[i] = buffer[i] | 0x80; 
	}
	refresh();
}

void MaxMatrix::shiftUp(bool rotate, bool fill_zero)
{
	byte a=buffer[15], b=buffer[31];
	for (int i=31; i>0; i--)
	{
            buffer[i]=buffer[i-1];
	}
	buffer[0]=a;
	buffer[16]=b;
	refresh();
}

void MaxMatrix::shiftDown(bool rotate, bool fill_zero)
{
	byte a=buffer[0], b=buffer[16];
	for(int i=0;i<31;i++) {
            buffer[i]=buffer[i+1];
            // buffer[i+16]=buffer[i+17];
	}
	buffer[15]=a;
	buffer[31]=b;
	refresh();
}
//////////////////////////////////////////////////
byte MaxMatrix::bitReverse( byte x )
{
  //          01010101  |         10101010
  x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
  //          00110011  |         11001100
  x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
  //          00001111  |         11110000
  x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
  return x;

}
void MaxMatrix::loadCharBuffer(const PROGMEM byte *p, byte *charBuffer, int len) {
  for (int i = 0; i < len; i++) {
    charBuffer[i] = pgm_read_byte(p++);
  }
}

void MaxMatrix::displayChar(const byte chars[] PROGMEM, int len) {
  clear();
  byte p, x;
  for (int i = 0; i < len; i++) {
    x = 31 - i;
    p = (i & 0x01) ? 0 : 16;
    setRow(i / 2 + p, bitReverse(chars[x]));
  }
}


void MaxMatrix::shiftDownIn(const byte bitmap[], int len, uint32_t delayTime) {
  for (int i = 0; i < 2; i++) {
    shiftDown();
    setRow(15, 0);
    setRow(31, 0);
    delay(delayTime);
  }

  for (int i = 0; i < len; i += 2) {
    shiftDown();
    setRow(15, bitReverse(bitmap[30 - i]));
    setRow(31, bitReverse(bitmap[31 - i]));
if(debugPrint) debugPrint();
    delay(delayTime);
  }
}

void MaxMatrix::shiftUpIn(const byte bitmap[], int len, uint32_t delayTime) {
  for (int i = 0; i < 2; i++) {
    shiftUp();
    setRow(0, 0);
    setRow(16, 0);
    delay(delayTime);
  }

  for (int i = 0; i < len; i += 2) {
    shiftUp();
    setRow(0, bitReverse(bitmap[i]));
    setRow(16, bitReverse(bitmap[i + 1]));

if(debugPrint) debugPrint();
    delay(delayTime);
  }
}




void MaxMatrix::shiftLeftIn(const byte bitmap[], int len, uint32_t delayTime) {
  for (int i = 0; i < 0; i++) {
    shiftLeft();
    setColumn(23, 0);
    setColumn(31, 0);
    delay(delayTime);
  }

  uint8_t x = 0x00, b;
  for (int c = 0; c < 16; c++) {
    shiftLeft();

    if (c == 0 || c == 8) {
      x = 0x80;
    } else x >>= 1;


    b = 0;
    // for (int k = 0, p = (c < 8) ? 31 : 30; k < 8; k++, p -= 2) {
    for (int k = 0, p = (c < 8) ? 16 : 17; k < 8; k++, p += 2) {
      b <<= 1;
      if ( (bitmap[p] & x) != 0) {
        b |= 0x01;
      }
    }
    setColumn(23, b);

    b = 0;
    // for (int k = 0, p = (c < 8) ? 31 : 30; k < 8; k++, p -= 2) {
    for (int k = 0, p = (c < 8) ? 0 : 1; k < 8; k++, p += 2) {
      b <<= 1;
      if ( (bitmap[p] & x) != 0) {
        b |= 0x01;
      }
    }
    setColumn(31, b);

if(debugPrint) debugPrint();

    delay(delayTime);
  }

}

void MaxMatrix::shiftRightIn(const byte bitmap[], int len, uint32_t delayTime) {
  for (int i = 0; i < 0; i++) {
    shiftRight();
    setColumn(23, 0);
    setColumn(31, 0);
    delay(delayTime);
  }

  uint8_t x = 0x00, b;
  for (int c = 0; c < 16; c++) {
    shiftRight();
    
    if (c == 0 || c == 8) {
      x = 0x01;
    } else x <<= 1;


    b = 0;
    for (int k = 0, p = (c < 8) ? 31 : 30; k < 8; k++, p -= 2) {
    // for (int k = 0, p = (c < 8) ? 16 : 17; k < 8; k++, p += 2) {
      b >>= 1;
      if ( (bitmap[p] & x) != 0) {
        b |= 0x80;
      }
    }
    setColumn(0, b);

    b = 0;
    for (int k = 0, p = (c < 8) ? 15 : 14; k < 8; k++, p -= 2) {
    // for (int k = 0, p = (c < 8) ? 16 : 17; k < 8; k++, p += 2) {
      b >>= 1;
      if ( (bitmap[p] & x) != 0) {
        b |= 0x80;
      }
    }
    setColumn(8, b);

if(debugPrint) debugPrint();
    delay(delayTime);
  }
}

