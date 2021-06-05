#include "SC12B.h"
#include <Wire.h>

void SC12B::begin(uint8_t SDA , uint8_t SCL) {
  _SDA = SDA;
  _SCL = SCL;
  if (_SDA == 21 || _SCL == 22)   //ESP32 default I2C pinset
    Wire.begin();
  else
    Wire.begin(_SDA, _SCL);
}
void SC12B::init() {
  writeRegister(REG_Senset0, LEVEL7);   //LEVEL7 is default,Unless you have a special purpose, it is not recommended to modify
  writeRegister(REG_SensetCOM, LEVEL7); //LEVEL7 is default
  writeRegister(REG_CTRL0, 0x83);
  writeRegister(REG_CTRL1, 0x08);
}
uint16_t SC12B::getKeyValue() {
  uint16_t keyvalue = 0xFFFF;
  uint8_t value = 0;
  value = readRegister(REG_OUTPUT1);
  keyvalue = (uint16_t)value << 8 | readRegister(REG_OUTPUT2);
  return keyvalue;
}


uint8_t SC12B::readRegister(uint8_t reg)
{
  uint8_t value = 0;
  readBuffer(reg, &value, 1);
  return value;
}
bool SC12B::writeRegister(uint8_t reg, uint8_t value)
{
  return writeBuffer(reg, &value, 1);
}

bool SC12B::writeBuffer(uint8_t reg, void *buffer, uint8_t writeLen)
{
  Wire.beginTransmission(SC12B_Addr);
  Wire.write(reg);
  for (uint8_t i = 0; i < writeLen; i++) {
    Wire.write(((uint8_t *)buffer)[i]);
  }
  if (Wire.endTransmission(true) != 0) {
    return false;
  }
  return true;
}

bool SC12B::readBuffer(uint8_t reg, void *buffer, uint8_t readLen)
{
  Wire.beginTransmission(SC12B_Addr);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) {
    return false;
  }
  Wire.requestFrom((uint8_t)SC12B_Addr, readLen);
  for (uint8_t i = 0; i < readLen; i++) {
    ((uint8_t *)buffer)[i] = (uint8_t)Wire.read();
  }
  return true;
}
//Modify the corresponding characters below according to the actual printed characters on your touch pannel
char SC12B::getKeyChar(uint16_t keyvalue) {
  char convert2char;
  switch (keyvalue) {
    case 0x0:
      convert2char = '\0';
      break;
    default:
      convert2char = '\0';
      break;
  }
  return convert2char;
}
