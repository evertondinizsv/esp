#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>
#include <Ticker.h>
#include <Servo.h>

//WIFI Settings

const char* ssid = "hebert";
const char* password = "12112015";

byte ip[]      = { 192, 168, 3, 111};
byte gateway[] = { 192, 168, 3, 1 };
byte subnet[]  = { 255, 255, 255, 0 };


Servo myservo;
Ticker Stop;
ModbusTCPSlave Mb;  

const int inputPin = D6;
int led_status = D1;
int led = D2;
 


void monitoring(){

Mb.MBHoldingRegister[0] = digitalRead(inputPin);

}
void setup()

{
  pinMode(inputPin, INPUT);
  pinMode(led, OUTPUT);
  
  myservo.attach(inputPin);
   
//Configurações WIFI

 Serial.begin(115200);
 Mb.begin("hebert","12112015", ip, gateway, subnet);
 delay(500);
 Serial.println();
 Serial.print("Conectando a Rede: ");
 Serial.println(ssid);
 Serial.print("Com IP: ");
 Serial.println(WiFi.localIP());
 Serial.print("Mac Node MCU: ");
 Serial.println(WiFi.macAddress());

 if (WiFi.status() != WL_CONNECTED) {
   digitalWrite(led, LOW);
 }
 
 else{
  digitalWrite(led, HIGH);
  digitalWrite(led_status, LOW);
 Serial.println();
 Serial.print("CONECTADO A REDE: ");
 Serial.println(ssid);
  
  }
 
}

void loop()
{
  Mb.Run();
  //Ticket Function
  Stop.attach_ms(35,monitoring); 
  
}
