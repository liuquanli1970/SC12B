#include "SC12B.h"
#define touch_interrupt_pin 39
SC12B touchPannel;
boolean iftouch = false;
void checkkey() {  //ISR
  iftouch = true;
}
void setup() {
  Serial.begin(115200);
  pinMode(touch_interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(touch_interrupt_pin), checkkey, FALLING);
  touchPannel.begin();  //default SDA->GPIO21 SCL->GPIO22 ,if other pins,please touchPannel.begin(SDAPin,SCLPin);
}

void loop() {
  if (iftouch)   {
    uint16_t key = touchPannel.getKeyValue();
    Serial.println(key, HEX);
    Serial.println(touchPannel.getKeyChar(key));
    iftouch = false;
  }
}
