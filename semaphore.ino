
#include "src/macros.h"
#include "src/debounceClass.h"

const int inrijPin =  3 ;
const int uitrijPin = 4 ;                                                       // voer pinnen naar keuze in
const int relayPin  = 5 ;

Debounce inrijSensor(  inrijPin ) ;
Debounce uitrijSensor( uitrijPin ) ;

void setup()
{
    pinMode( relayPin, OUTPUT ) ;
    digitalWrite( relayPin, HIGH ) ;                                            // SIGNAL ON DANGER 
    
    inrijSensor.debounce() ;
    uitrijSensor.debounce() ;
    delay(100) ;
    inrijSensor.debounce() ;
    uitrijSensor.debounce() ;

    Serial.begin( 115200 ) ;
    Serial.println("goodmorning hans") ;
}

void loop()
{
    REPEAT_MS( 500 )
    {
        inrijSensor.debounce() ;                                                // read and debounce sensor every 500ms
        uitrijSensor.debounce() ;                                               // read and debounce sensor every 500ms
    } END_REPEAT
    
    byte sensorState = sensor.getState() ;

    if( inrijSensor == FALLING )                                                // inrij sensor gemaakt -> sein = safe
    {
        digitalWrite( relayPin, LOW ) ;         
    }

    if( uitrijSensor == RISING )                                                // inrij sensor verbroken -> sein = danger
    {
        // delay( 5000 ) ;                                                      // je kan hier bij het afvallen van het uitrijsensor een vertraging toevoegen voordat het relais schakelt
        digitalWrite( relayPin, HIGH ) ;
    }
}