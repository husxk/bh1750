#include <Wire.h>        
#include <BH1750.h>      

BH1750 lightMeter;

float wattsGenerated = 0; // w/m2
long examineTime = 0; // s
float insolationInDay = 0;
float overallInsolationInDay = 0;

void setup()
{
  Serial.begin(9600);         
  Wire.begin();               // Enable I2C pins of Arduino
  lightMeter.begin();
  delay(2000);
}

void displayInfo(float lux, float watts, float wattsGenerated, float insolationThisDay, float insolationNow)
{
  Serial.print(lux);                       
  Serial.print("lx now, watts now: "); 
  Serial.print(watts);
  Serial.print("W, overall watts generated: ");
  Serial.print(wattsGenerated);
  Serial.print("kW, in time ");
  Serial.print(examineTime);
  Serial.print("s, overall: ");
  Serial.print(insolationThisDay);
  Serial.print("kWh/m2/day, another measurement: insolation now:");
  Serial.print(insolationNow);
  Serial.print("Wh/m2/now, ");
  Serial.print(insolationInDay);
  Serial.print("Wh/m2/day, overall insolation: ");
  Serial.print(overallInsolationInDay);
  Serial.println("Wh/m2");
}

void loop()
{
  float lux = lightMeter.readLightLevel();
  float watts = lux * 0.0079; // w/m2
  
  wattsGenerated += (watts / 1000); // kW
  examineTime++;                            /* ~0.72W/m2 dziennie okolo 2,612 kWh/m2/dzien // luty srednio 0.99kwh/m2/day */

  float insolationThisDay = wattsGenerated / 3600; // wattsGenerated * 24 [kWh] / ( 24[hours examinated] * 3600[every examine] ) [kWh/m2/day]

  float insolationNow = (watts / 3600); // wh/m2
  overallInsolationInDay += insolationNow; 
  insolationInDay = (insolationInDay / 24) / 3600;  

  displayInfo(lux, watts, wattsGenerated, insolationThisDay, insolationNow);
  
  delay(1000);
}