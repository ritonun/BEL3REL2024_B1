// LIBRARY
#include <Wire.h>
#include <DHT.h>
#include "rgb_lcd.h"
#include "AirQuality.h"
#include "Si115X.h"

// PINOUT
#define PIN_PLUIE       A0
#define PIN_GIROUETTE   A1
#define PIN_ANEMOMETRE  A2
#define PIN_AIRQUALI    A3       

// Const du programme
#define DHTPIN 2
#define DHTTYPE DHT11   // Modele du capteur avec lequel on travaille

DHT dht(DHTPIN, DHTTYPE); // Init la classe DHT
#define debug  Serial // Demander par la librarie DHT
rgb_lcd lcd;  // Init la class ecran
AirQuality airqualitysensor;  // Init la class airquality
Si115X si1151; // init la class st114X pour le capteur  de luminosite

float niveau_pluie = 0.0;

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

void setup_capteur_airquality() {
    // Init capteur sunlight
    if (!si1151.Begin(false)) {
        Serial.println("Si1151 is not ready!");
        while (1) {
            delay(1000);
            Serial.print(".");
        };
    }
    else {
        Serial.println("Si1151 is ready!");
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

void test_pluviometre(){
  int BP = digitalRead(A0); // Lecture du capteur
  Serial.print(BP);
  if (BP == LOW) {
    digitalWrite(13, HIGH); // Allume la Led
    Serial.println("BP HIGH");
  }
  else {
    digitalWrite(13, LOW); // Eteind la Led
    Serial.println("BP LOW");
  }
}

void pluviometre() {
  const float capacite_bp = 0.2794;  // mm
  static float last_position = 0.0;
  static int nombre_de_vidage = 0;
  int BP = digitalRead(A0); // Lecture du capteur
  if (BP == LOW) {
    if (BP != last_position) {
      if (nombre_de_vidage % 2 == 0) {
        niveau_pluie += capacite_bp;
        nombre_de_vidage++;
      }
      else {
        nombre_de_vidage++;
      }
    }
  }
  last_position = BP;
}

void anemometre() {
  int BP = digitalRead(A2); // Lecture du capteur
  Serial.print("Anemometre: ");
  Serial.println(BP);
}

void girouette() {
  int sensorValue = analogRead(A1);
  Serial.print("Girouette: ");
  Serial.println(sensorValue);
}

void test_analog() {
  int valeur_pot = analogRead(A0);
  Serial.println(valeur_pot);
}

void print_ecrant(const char string[]) {
  lcd.print(string);
}

void setup() {
  Serial.begin(115200); // Initialise la communication via le cable entre l'arduino et le pc
  Wire.begin(); // Initialise I2C

  //dht.begin();  // Start le capteur dht

  //setup_capteur_airquality();

  //airqualitysensor.init(A3);  // Init le capteur de qualite de l air

  // pluviometre
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);

  // anenometre
  pinMode(A2, INPUT);

  //girouette
  pinMode(A1, INPUT);

  lcd.begin(16,2);  // Set up l'ecran de taille 16 colonne 2 lignes (16x2 characteres)
  
  print_ecrant("Setup OK");
  Serial.println("Setup OK"); // Pas d'erreur dans le setup
}

void loop() {
  //capteur_dht();
  //capteur_airquality();
  //test_analog();
  //capteur_luminosite();
  //pluviometre();
  //girouette();
  //anemometre();
  /*
  Serial.print("Niv pluie");
  Serial.println(niveau_pluie);
  */
  print_ecrant("loop");
  delay(1000);
  lcd.clear();
  print_ecrant("clear");
  delay(1000);
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
