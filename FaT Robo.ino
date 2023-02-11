// THE CODE I MADE 
#include <SoftwareSerial.h>
int IRSensor = 2; // CONNECT IR SESNOR TO ARDUINO PIN 2
int Flame_Sensor = 12; // CONNECT FLAME SENSOR TO ARDUINO PIN 3
int Green_LED = 6; // CONNECT GREEN LED TO ARDUINO PIN 4;
int Red_LED = 8; // CONNECT RED LED TO ARDUINO PIN 5;

SoftwareSerial mySerial(10,11); // CONNECT RX OF GSM TO 11 & TX OF GSM TO 10
int door ;
int fire ;

void setup() 
{
  mySerial.begin(9600); // SETTING BAUD RATE OF GSM MODULE
  Serial.begin(9600); // SETTING BAUD RATE OF SERIAL MONITOR 
  delay(100);

  pinMode(IRSensor, INPUT);
  pinMode(Flame_Sensor, INPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  
}

void loop()
{
  door = digitalRead(IRSensor);
  fire = digitalRead(Flame_Sensor);

  if (door == 0 && fire == 1){    
    digitalWrite(Green_LED, HIGH);
    digitalWrite(Red_LED, LOW); 
  } else 
    { 
      if(door == 1)
      {
        digitalWrite(Red_LED, HIGH);
        digitalWrite(Green_LED, LOW);
        Theft_Alert();
      } 
      else
      {
        digitalWrite(Red_LED, HIGH);
        digitalWrite(Green_LED, LOW);
        Fire_Alert();
      }  
   }
  Serial.println(door);
  Serial.println(fire);
}

void Theft_Alert()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919354737630\"\r"); 
  delay(1000);
  mySerial.println("DANGER!! SOMEONE IS TRYING TO ENTER");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

void Fire_Alert()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919354737630\"\r"); 
  delay(1000);
  mySerial.println("DANGER!! FIRE IN THE OFFICE");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
