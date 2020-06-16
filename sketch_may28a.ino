#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>
#include <Modbus.h>
#include <Ticker.h>
#include <Servo.h>

//WIFI Settings

byte ip[]      = { 192, 168, 3, 110};
byte gateway[] = { 192, 168, 3, 1 };
byte subnet[]  = { 255, 255, 255, 0 };


Servo myservo;
Ticker Stop;
ModbusTCPSlave Mb;  

const int inputPin = D2;
const int cont = D5;
int contador = 0;



void monitoring(){

//Digital Inputs
Mb.MBHoldingRegister[0] = digitalRead(inputPin);
//Mb.MBHoldingRegister[1] = digitalRead(contador);
//Mb.MBHoldingRegister[1] = analogRead(contador);

Mb.MBHoldingRegister[2] = digitalRead(cont);
  
  if(digitalRead(cont) == 1){
    Mb.MBHoldingRegister[1] = random(contador);
    delay(1000);
    contador++;
    delay(1000);
     Serial.print("CONTADOR = ");
     Serial.println(contador);
     delay(5000);
            
  }
   if(digitalRead(cont) == 0){
    Mb.MBHoldingRegister[1] = random(contador);
    delay(1000);
    contador = 0;
    delay(1000);
     Serial.print("CONTADOR = ");
     Serial.println(contador);
               
  }
  

}


void setup()

{
  pinMode(inputPin, INPUT);
  pinMode(cont, INPUT);

  
  Serial.begin(9600);
  myservo.attach(inputPin);
  myservo.attach(cont);
  myservo.attach(contador);
  
  Mb.begin("hebert","12112015", ip, gateway, subnet);
 
  
  Serial.print("CONECTADO A :");
  Serial.println();
  Serial.println("ssid");
   delay(1000);
  
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 
}

void loop()
{
  Mb.Run();
  //Ticket Function
  Stop.attach_ms(35,monitoring); 


  
  
}
