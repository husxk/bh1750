#include <Wire.h>        
#include <BH1750.h>      

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

void displayInfo(float lux, float watts, float wattsGenerated, float isolationThisDay)
{
  Serial.print(lux);                       
  Serial.print("lx now, watts now: "); 
  Serial.print(watts);
  Serial.print("W, overall watts generated: ");
  Serial.print(wattsGenerated);
  Serial.print("kW, in time ");
  Serial.print(examineTime);
  Serial.print("s, overall: ");
  Serial.print(isolationThisDay);
  Serial.println("kWh/m2/day");
}

void loop()
{
  float lux = lightMeter.readLightLevel();
  float watts = lux * 0.0079;
  wattsGenerated += (watts / 1000); // kW
  examineTime++; /* ~0.72W/m2 dziennie okolo 2,612 kWh/m2/dzien 
                                              luty srednio 0.99kwh/m2/day */
  float isolationThisDay = wattsGenerated / 3600; // wattsGenerated * 24 [kWh] / ( 24[hours examinated] * 3600[every examine] ) [kWh/m2/day]

  displayInfo(lux, watts, wattsGenerated, isolationThisDay);
  
  delay(1000);
}