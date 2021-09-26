#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;

#include <RH_ASK.h>
#include <SPI.h>

#define WIRE Wire
RH_ASK driver;

void setup() {

  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
  
  Serial.begin(115200);
  while (!Serial) {};
  LIS.begin(WIRE, 0x19);

  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  LIS.setHighSolution(true);

  if (!driver.init())
         Serial.println("init failed");
}

float x = 0, y = 0;
char t = 's';

char buf[2];

void loop() {
  
  x = 0.1 * LIS.getAccelerationX() + 0.9 * x;
  y = 0.1 * LIS.getAccelerationY() + 0.9 * y;


  if (x*10 < -3)
    buf[0] = 'l';

  else if (x*10 > 3)
    buf[0] = 'r';

  else
    buf[0] = 's';


  if (y*10 > 3)
    buf[1] = 'f';

  else if (y*10 < -3)
    buf[1] = 'b';

  else
    buf[1] = 's';







  driver.send((uint8_t *)buf, 2);
  driver.waitPacketSent();

  Serial.print(x);
  Serial.print("  ");
  Serial.println(y);

}
