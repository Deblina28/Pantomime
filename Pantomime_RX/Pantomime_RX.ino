#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK driver;

void setup()
{
    Serial.begin(9600);	
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    char buf[2];
    uint8_t buflen = 2;

    if (driver.recv(buf, &buflen)) 
    {
	int i;

  Serial.println(String(buf));
    }
}
