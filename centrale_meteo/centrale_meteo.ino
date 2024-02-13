// LIBRARY
#include <Wire.h>
#include <DHT.h>
#include "rgb_lcd.h"
#include "AirQuality.h"
#include "Si115X.h"

// Const du programme
#define DHTPIN 2
#define DHTTYPE DHT11   // Modele du capteur avec lequel on travaille

DHT dht(DHTPIN, DHTTYPE); // Init la classe DHT
#define debug  Serial // Demander par la librarie DHT
rgb_lcd lcd;  // Init la class ecran
AirQuality airqualitysensor;  // Init la class airquality
Si115X si1151; // init la class st114X pour le capteur  de luminosite

void capteur_luminosite() {
    Serial.print("IR: ");
    Serial.println(si1151.ReadIR());
    Serial.print("Visible: ");
    Serial.println(si1151.ReadVisible());
}

void capteur_airquality() {
  int current_quality =-1;
  current_quality=airqualitysensor.slope();
  if (current_quality >= 0)// if a valid data returned.
  {
      if (current_quality==0)
          Serial.println("High pollution! Force signal active");
      else if (current_quality==1)
          Serial.println("High pollution!");
      else if (current_quality==2)
          Serial.println("Low pollution!");
      else if (current_quality ==3)
          Serial.println("Fresh air");
  }
}

void capteur_dht() {
  // Fonction pour récuperer la donnée du capteur DHT de température et humidité
 
  float temp_hum_val[2] = {0};
  
  if (!dht.readTempAndHumidity(temp_hum_val)) {
      Serial.print("Humidity: ");
      Serial.print(temp_hum_val[0]);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(temp_hum_val[1]);
      Serial.println(" *C");
  } else {
      Serial.println("Failed to get temprature and humidity value.");
  } 
}

void test_analog() {
  int valeur_pot = analogRead(A0);
  Serial.println(valeur_pot);
}

void setup() {
  Serial.begin(115200); // Initialise la communication via le cable entre l'arduino et le pc
  Wire.begin(); // Initialise I2C

  dht.begin();  // Start le capteur dht

  //airqualitysensor.init(A0);  // Init le capteur de qualite de l air

  // Init capteur sunlight
    if (!si1151.Begin()) {
        Serial.println("Si1151 is not ready!");
        while (1) {
            delay(1000);
            Serial.print(".");
        };
    }
    else {
        Serial.println("Si1151 is ready!");
    }
  
  lcd.begin(16,2);  // Set up l'ecran de taille 16 colonne 2 lignes
  lcd.print("Setup OK!");
  Serial.println("Setup OK"); // Pas d'erreur dans le setup
}

void loop() {
  //capteur_dht();
  //capteur_airquality();
  //test_analog();
  capteur_luminosite();
  delay(2000);
}

ISR(TIMER2_OVF_vect)
{
    if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
    {
        airqualitysensor.last_vol=airqualitysensor.first_vol;
        airqualitysensor.first_vol=analogRead(A0);
        airqualitysensor.counter=0;
        airqualitysensor.timer_index=1;
        PORTB=PORTB^0x20;
    }
    else
    {
        airqualitysensor.counter++;
    }
}
