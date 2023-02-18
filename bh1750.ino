#include <Wire.h>         // adds I2C library 
#include <BH1750.h>       // adds BH1750 library file 

BH1750 lightMeter;

float wattsGenerated = 0; // w/m2
long examineTime = 0; // s

void setup()
{
  Serial.begin(9600);         
  Wire.begin();               // Enable I2C pins of Arduino
  lightMeter.begin();
  delay(2000);
}

void displayInfo(float lux, float watts, float wattsGenerated, float toNow)
{
  Serial.print(lux);                       
  Serial.print("lx now, watss now: "); 
  Serial.print(watts);
  Serial.print("W, overall watts generated: ");
  Serial.print(wattsGenerated);
  Serial.print("kW, avarage to now: ");
  Serial.print(toNow * 3600);
  Serial.print("kWh/m2, in time ");
  Serial.print(examineTime);
  Serial.print("s, in hours: ");
  Serial.print(float(examineTime / 3600));
  Serial.print("h, overall: ");
  Serial.print(wattsGenerated / 24);
  Serial.println("kWh/m2/day");
}

void loop()
{
  float lux = lightMeter.readLightLevel();
  float watts = lux * 0.0079;
  wattsGenerated += watts / 1000; // kW
  examineTime++;
  float toNow = wattsGenerated / examineTime; /* ~0.72W/m2 dziennie okolo 2,612 kWh/m2/dzien 
                                              luty srednio 0.99kwh/m2/day */

  displayInfo(lux, watts, wattsGenerated, toNow);
  
  delay(1000);
}