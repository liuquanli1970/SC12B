/*
  This library function can be called by Arduino IDE and it is suitable for esp32 and esp8266 MCU.
  Sc12b is a 12 channel capacitive touch keyboard IC.
  Author: Liu Quanli (liu_quanli@126.com)
  Tianjin honNewcom Technology Co., Ltd
  2021-06-06 Tianjin
*/

#ifndef _SC12B_H_
#define _SC12B_H_
#include <arduino.h>
#define SC12B_Addr 0x40             //pin ASEL NC:0x40 ,HIGH:0x44 LOW:0x42
//Register
#define REG_Senset0 0x00
#define REG_SensetCOM 0x01
#define REG_CTRL0 0x02
#define REG_CTRL1 0x03
#define REG_OUTPUT1 0x08
#define REG_OUTPUT2 0x09
#define REG_SAMPH 0x0A
#define REG_SAMPL 0x0B

typedef enum {
  LEVEL0 = 0x04,
  LEVEL1 = 0x15,
  LEVEL2 = 0x25,
  LEVEL3 = 0x36,
  LEVEL4 = 0x47,
  LEVEL5 = 0x58,
  LEVEL6 = 0x68,
  LEVEL7 = 0x79,
  LEVEL8 = 0x8A,
  LEVEL9 = 0x9B,
  LEVEL10 = 0xAC,
  LEVEL11 = 0xBC,
  LEVEL12 = 0xCD,
  LEVEL13 = 0xDE,
  LEVEL14 = 0xEF,
  LEVEL15 = 0xFF
} Sensitivity;

class SC12B {
  public:
    void begin(uint8_t SDA = 21, uint8_t SCL = 22);
    void init();      //It is equivalent to restoring the factory settings
    uint16_t getKeyValue();
    char getKeyChar(uint16_t keyvalue);
  private:
    uint8_t _SDA, _SCL;
    uint8_t  readRegister(uint8_t reg);
    bool writeRegister(uint8_t reg, uint8_t value);
    bool writeBuffer(uint8_t reg, void *buffer, uint8_t writeLen);
    bool readBuffer(uint8_t reg, void *buffer, uint8_t readLen);
};

#endif
