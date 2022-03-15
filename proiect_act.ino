#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int PUMP_PIN= 5;

const int analogPin = A0;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(PUMP_PIN, OUTPUT);
}

void loop()
{ 
   Serial.println();

   float u = dht.readHumidity();
   float t = dht.readTemperature();
   int sensorValue = analogRead(analogPin);
   
     if(isnan(u) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity (%): ");
  Serial.println(u, 2);

  Serial.print("Temperature (C): ");
  Serial.println(t, 2);

  Serial.print("Moisture Humidity (%): ");
  Serial.println(sensorValue);


  int count = 0;
  if (u > 65)
          count = 30;
  else if (u < 45)
          count = -30;


  if( sensorValue>0 && sensorValue<=300-count )
  {
    digitalWrite(PUMP_PIN, HIGH); // pompa se opreste --- releul se inchide
  }
  
  else if ( sensorValue>=550-count && sensorValue<700 )  
  {
    digitalWrite(PUMP_PIN, LOW); //pompa porneste --- releul se deschide
     
  }

  
    
  delay(5000);
 

}

 
