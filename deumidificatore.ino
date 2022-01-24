#include <Wire.h>
#include <dht_nonblocking.h>
//#include <LiquidCrystal_I2C.h>

#define MODEL DHT_TYPE_11

static const int PIN_DATA = 2;
static const int INTERR = 3;

DHT_nonblocking sens(PIN_DATA, MODEL);

//LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(INTERR, OUTPUT);
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++){
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == false){
      
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded
    }
   }
   Serial.print("Found ");
   Serial.println(count, DEC);
/*
   lcd.init();
   lcd.clear();
   lcd.backlight();
   lcd.print("Weather Station");
   lcd.setCursor(0, 1);
   lcd.print("Virgo Obs. M15");
*/
   digitalWrite(INTERR, LOW);
   delay(3000);
   
   
}

void loop() {
  float t;
  float h;
  if (sens.measure(&t, &h) == true) {
    
   
    Serial.print("Valore Temperatura =  ");
    Serial.print(t, 1);
    Serial.print("\n");
    
    
    Serial.print("Valore Umidità =  ");
    Serial.print(h, 1);
    Serial.print("\n");
    
    if( h > 80 ) {
      //accendo la luce IR
      digitalWrite(INTERR, HIGH);
      
    }
    if ( h < 50 ) {
      //spegnere la lucw IR
      digitalWrite(INTERR, LOW);
      
    }
  }
 
}
