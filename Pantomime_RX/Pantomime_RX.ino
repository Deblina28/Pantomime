#include <RH_ASK.h>
#include <SPI.h>

#define base 200

#define R2 9
#define R1 6
#define L1 5
#define L2 3

RH_ASK driver;

void setup()
{
  pinMode (R1, OUTPUT);
  pinMode (R2, OUTPUT);
  pinMode (L1, OUTPUT);
  pinMode (L2, OUTPUT);

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
    if (buf[1] == 'f' && buf[0] == 's')
      forward();

    else if (buf[1] == 'b' && buf[0] == 's')
      back();

    else if (buf[1] == 's' && buf[0] == 's')
      stop();

    else if (buf[1] == 's' && buf[0] == 'l')
      left();

    else if (buf[1] == 's' && buf[0] == 'r')
      right();

    else 
    stop();



   /* else if (buf[0] == 'l' && buf[1] == 'f')
    {
      left();
      delay(100);
      forward();
      delay(100);
    }

    else if (buf[0] == 'r' && buf[1] == 'f')
    {
      right();
      delay(100);
      forward();
      delay(100);
    }

    else if (buf[0] == 'l' && buf[1] == 'b')
    {
      left();
      delay(100);
      back();
      delay(100);
    }

    else if (buf[0] == 'r' && buf[1] == 'b')
    {
      right();
      delay(100);
      back();
      delay(100);
    }*/


    Serial.println(String(buf));
  }
}

void forward()
{ analogWrite (L1, base);
  digitalWrite (L2, LOW);
  digitalWrite (R2, LOW);
  analogWrite(R1, base);
}

void back()
{ analogWrite (L2, base);
  digitalWrite (L1, LOW);
  digitalWrite (R1, LOW);
  analogWrite(R2, base);
}

void right()
{ analogWrite (L1, base);
  digitalWrite (L2, LOW);
  analogWrite (R2, base);
  digitalWrite (R1, LOW);
}

void left()
{
  digitalWrite (L1, LOW);
  analogWrite (L2, base);
  digitalWrite (R2, LOW);
  analogWrite (R1, base);
}

void stop()
{
  analogWrite (L1, 255);
  analogWrite (L2, 255);
  analogWrite (R2, 255);
  analogWrite (R1, 255);
}
