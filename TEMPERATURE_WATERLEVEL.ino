#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;

#define PUMP_PIN 9

#define SIGNAL_PIN A5

int value = 0; // variable to store the sensor value

void setup() {
  
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUMP_PIN,OUTPUT);
  pinMode(SIGNAL_PIN, INPUT); 
  sensors.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:
     
                         // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
    

  Serial.print("Sensor value: ");
  Serial.println(value);
 if (value<=0){
  digitalWrite(PUMP_PIN, LOW);
  delay(5000);
  Serial.println("Pump ON");
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);
  Serial.println("Pump OFF");
  }
 else{
  digitalWrite(PUMP_PIN, HIGH);
  delay(1000);
  Serial.println("Pump OFF");
 }
  delay(1000);
   sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  

  Serial.println(Celsius);
  Serial.print(" C  ");


  if(Celsius>=27.00){
    digitalWrite(PUMP_PIN,LOW);
    Serial.println("pump on");
    delay(1000);
    
    digitalWrite(PUMP_PIN,HIGH);
    Serial.println("pump off");
    delay(1000);
    }
   else{
    digitalWrite(PUMP_PIN,HIGH);
    Serial.println("pump off");
    delay(1000);
    }   
    }
