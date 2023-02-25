#include <Wire.h>        
#include <BH1750.h>      

BH1750 luxMeter;

float insolationGenerated = 0; // kW/m2
long examineTime = 0; // s
float averageInsolationForDay = 0;

void setup()
{
  Serial.begin(9600);         
  Wire.begin();               // Enable I2C pins of Arduino
  luxMeter.begin();
  delay(2000);
}

void displayInfo(float lux, float insolationInMoment, float insolationGenerated)
{
  Serial.print(lux);                       
  Serial.print("lx now, insolation now: "); 
  Serial.print(insolationInMoment);
  Serial.print("W/m2, overall insolationGenerated: ");
  Serial.print(insolationGenerated);
  Serial.print("kW/m2, in time ");
  Serial.print(examineTime);
  Serial.print("s, averageInsolationForDay ");
  Serial.print(averageInsolationForDay);
  Serial.println("W/m2/today");
}

void loop()
{
  float lux = luxMeter.readLightLevel();
  float insolationInMoment = lux * 0.0079; // w/m2
  
  insolationGenerated += (insolationInMoment / 1000); // kW/m2
  examineTime++; // s

  averageInsolationForDay = (insolationGenerated * 1000) / (24 * 3600); // (every measurement) / (number of measures in whole day) // W/m2/today

  displayInfo(lux, insolationInMoment, insolationGenerated);
  
  delay(1000);
}