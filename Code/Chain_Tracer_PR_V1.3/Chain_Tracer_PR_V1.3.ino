#include<EEPROM.h>
#include<SoftwareSerial.h>

#define frq 9                 // defining pin 9 for TSOP1738 input        
#define buzzer 10             // defining pin 10 for buzzer output

String u_id = String(13);     // declaring a variable u_id to store user ID or badge ID and initialising it
String f_id;                  // declaring a variable f_id to store foreign ID
int count = 0;
SoftwareSerial r_t(2, 3);     // defining software serial at pin 2(RX) and 3(TX)

void setup()
{
  Serial.begin(9600);
  r_t.begin(1200);
  tone(frq, 38000);           // setting the frequecy at 38KHZ for TSOP1738 reciever
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  r_t.write(&u_id);           // this will transmit the user ID      
  if (r_t.available())        // checking if some data is recieved
  {
    f_id = r_t.readString();  // reading the available data(ID) and storing it in f_id
  }
  if (f_id.equals(u_id))      // if f_id is equal to u_id (this means the transmitted data is reflected back and someone is close)
  {
    digitalWrite(buzzer, HIGH); // this will make the buzzer to beep
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
  while (1)
  {
    if (EEPROM.read(count) == 0 && f_id.equals(u_id)!=0)    // this will store the received foreign ID in the EEPROM memory 
    {
      EEPROM.write(count, &f_id);
      count++;
      break;
    }
    else
    count++;
  }
  for(int i=0;EEPROM.read(i)!=0;i++) // printing the stored ID at the hardware serial
  Serial.println(EEPROM.read(i));
}
