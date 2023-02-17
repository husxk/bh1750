#include <Wire.h>         // adds I2C library 
#include <BH1750.h>       // adds BH1750 library file 
#include <EEPROM.h>

BH1750 lightMeter;

  float wattsGenerated = 0; // w/m2
  int examineTime = 0; // s

  float wattsGeneratedReaded;
  int examineTimeReaded;

void readDataFromEEPROM(int);

void setup()
{
 
  Serial.begin(9600);         
  Wire.begin();               // Enable I2C pins of Arduino
  lightMeter.begin();
  EEPROM.begin(sizeof(float)+ sizeof(int));
  delay(2000);

  readDataFromEEPROM(0);
  Serial.println();
  Serial.print(wattsGeneratedReaded);
  Serial.print("kW overall, examineded in time (s): ");
  Serial.println(examineTimeReaded);
  delay(5000);

}

void displayInfo(float lux, float watts, float wattsGenerated, float toNow)
{
  Serial.print(lux);                       
  Serial.print("lx, watss now: "); 
  Serial.print(watts);
  Serial.print("W, overall watts generated: ");
  Serial.print(wattsGenerated);
  Serial.print("kW, to now: ");
  Serial.print(toNow);
  Serial.println("W ");
}

bool writeDataToEEPROM(int address, int data)
{
  if(data == 1)
    EEPROM.write(address, wattsGenerated);
  else
    EEPROM.write(address, examineTime);
  
  return EEPROM.commit();
}

void isSuccess(bool success)
{
  Serial.print("Saving to EEPROM... Return:  ");
  Serial.println(success);
}

void saveData(int address) // 0
{
  bool success = writeDataToEEPROM(address, 1);
  isSuccess(success);

  success = writeDataToEEPROM(address + sizeof(float), 2);
  isSuccess(success);
}

void readDataFromEEPROM(int address) // 0
{
  wattsGeneratedReaded = EEPROM.read(address);
  examineTimeReaded = EEPROM.read(address + sizeof(float));
}

void loop()
{
  float lux = lightMeter.readLightLevel();
  float watts = lux * 0.0079;
  wattsGenerated += watts/1000; //kW
  examineTime++;
  float toNow = wattsGenerated/examineTime; /* ~0.72W/m2 dziennie okolo 2,612 kWh/m2/dzien 
                                              luty srednio 0.99kwh/m2/day */
  
  displayInfo(lux, watts, wattsGenerated, toNow);
  
  saveData(0);
  
  delay(1000);
}