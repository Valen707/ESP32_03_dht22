#include "DHT.h"

#define DHTPIN 4  //Pin de datos del sensor DHT11/22

#define DHTTYPE DHT11  //Especificamos el tipo de sensor DHT11 DHT22 DHT21

DHT dht(DHTPIN, DHTTYPE);  //Creamos el objeto que representa al sensor


void setup(){
   Serial.begin(9600);
   Serial.println("Ensayo del DHT22!");
   dht.begin();
}

void loop(){
   delay(2000);
   float humedad = dht.readHumidity(); //Leemos la humedad en % de humedad relativa (0 al 100%)
   float temperatura = dht.readTemperature(); //Leemos la temperatura en °C
   float tempFarenheit = dht.readTemperature(true); //Leemos la temperatura en grados farenheit
   
   //Verificamos las lecturas del sensor
   if(isnan(humedad) || isnan(temperatura) || isnan(tempFarenheit)){
     Serial.println("Fallo la lectura del sensor");
     return;
   }

   //Calculamos la sensacion termica o indice de calor
   float indice = dht.computeHeatIndex(tempFarenheit, humedad);

   //Calculamos la sensacion termica o indice de calor en celsius
   float indiceCelsius = dht.computeHeatIndex(temperatura, humedad, false);

//La F() siginifica que lo que esta dentro del parentesis se escribe en la FLASH
   Serial.print(F("Humedad: ")); 
   Serial.print(humedad);
   Serial.print(F("%  Temperatura: ")); 
   Serial.print(temperatura);
   Serial.print(F("°C  Indice de calor: ")); 
   Serial.print(indice);
   Serial.print(F("°F  Indice de calor: ")); 
   Serial.print(indiceCelsius);
   Serial.println(F("°C")); 
}