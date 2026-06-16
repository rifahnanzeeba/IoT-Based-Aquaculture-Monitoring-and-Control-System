#include <SimpleTimer.h>
#include<Wire.h>
#include<Servo.h>
#define RELAY_PIN 9

SimpleTimer timer;
Servo myservo;
float calibration_value = 21.34-0.7;
int phval = 0; 
int count=0;
int j;
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;

void setup(){
  Wire.begin();
  myservo.attach(6);
  pinMode(RELAY_PIN, OUTPUT);//pump pin
  pinMode(A0, INPUT);
  Serial.begin(9600);
  //timer.setInterval(5000);
}
void loop() {

  delay(3600);
  //timer.reset(); // Initiates SimpleTimer
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*3.3/4096/6 +1.3; 
 Serial.print("Voltage: ");
 Serial.println(volt);
  ph_act = -8.2 * volt + calibration_value;

 Serial.println("pH Val: ");
 Serial.print(ph_act);
 if(ph_act<=5.9){                   // wait for 2 seconds
   digitalWrite(RELAY_PIN, LOW);    // end signal
   delay(1000);
   Serial.println("pump on ");
   digitalWrite(RELAY_PIN, HIGH);
   delay(1000);
   Serial.println("pump off ");
  }
  else{
    digitalWrite(RELAY_PIN, HIGH);
    delay(1000);
    Serial.println("pump off ");
    }
 delay(3600);
 count=count+1;
 if(count==5){
   myservo.write(90);
   delay(50);
  
   for(j=90;j<=180;j=j+2)
  {
   myservo.write(j);  
   delay(500);
   }
   for(j=180;j>=90;j=j-2)
  {
  myservo.write(j);  
  delay(500);
  }
  count=0;
  delay(6000);

 
 }
 }


 
