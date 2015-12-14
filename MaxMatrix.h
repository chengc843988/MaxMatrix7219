

#ifndef _MaxMatrix_H_
#define _MaxMatrix_H_

#include "Arduino.h"
#define MAX_BUFFER_SIZE 80
class MaxMatrix
{
  private:
    byte data;
    byte load;
    byte clock;
    byte rows,cols;
    byte num;
    uint8_t buffer[MAX_BUFFER_SIZE];
    void (*debugPrint)()=0;

  public:
    MaxMatrix(byte data, byte load, byte clock, byte num,void (* debugPrint)() = 0 );
    
    void init();
    void clear();
    void setCommand(byte command, byte value);
    void setIntensity(byte intensity);
    void setRow(byte row, byte value);
    void setColumn(byte column, byte value);
    void refreshRow(byte row);
    void refresh();
    void setDot(byte col, byte row, byte value);
    inline uint8_t *getBuffer() { return buffer;};
    /////////////////////////
    void displayChar(const byte chars[] PROGMEM, int len);
    void loadCharBuffer(const PROGMEM byte *p, byte *charBuffer, int len);
    void shiftDownIn(const byte bitmap[], int len, uint32_t delayTime=100);
    void shiftUpIn(const byte bitmap[], int len, uint32_t delayTime=100);
    void shiftRightIn(const byte bitmap[], int len, uint32_t delayTime=100);
    void shiftLeftIn(const byte bitmap[], int len, uint32_t delayTime=100);
    byte bitReverse( byte x );

    /////////////////////////

    void shiftLeft(bool rotate = false, bool fill_zero = true);
    void shiftRight(bool rotate = false, bool fill_zero = true);
    void shiftUp(bool rotate = false, bool fill_zero = true);
    void shiftDown(bool rotate = false, bool fill_zero = true);
};

#endif
