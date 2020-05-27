#include<EEPROM.h>
#include<SoftwareSerial.h>

#define frq 9

long int u_id = 1;
long int f_id;
int count = 0;
SoftwareSerial r_t(2, 3);

void setup()
{
  Serial.begin(9600);
  r_t.begin(1200);
  tone(frq, 38000);
}

void loop()
{
  r_t.write(u_id);
  if (r_t.available() > 0)
  {
    f_id = r_t.read();
  }
  while (1)
  {
    if (EEPROM.read(count) == 0 && f_id != u_id)
    {
      EEPROM.write(count, f_id);
      count++;
      break;
    }
    else 
    count++;
  }
  Serial.println(f_id);
}
