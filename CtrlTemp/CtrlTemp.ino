#include <OneWire.h> 
#include <DallasTemperature.h>
#include <DS1307.h> //RTC

/********************************************************************/
//O fio de dados est� conectado ao pino 2 no Arduino

#define ONE_WIRE_BUS 2 

DS1307 rtc(A4, A5); // RTC


// Configure uma inst�ncia oneWire para se comunicar com qualquer dispositivo OneWire
// n�o apenas ICs de temperatura Maxim / Dallas)

OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Passe nossa refer�ncia oneWire para Dallas Temperature.

DallasTemperature sensors(&oneWire);
/********************************************************************/ 


int porta_rele1 = 5; // REL�

float maxima = 30.00;
float minima = 25.00;
float temp_sensor = 0.00;


void setup(void) 
{ 

//Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT);


  
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin(); 


// RTC Aciona o relogio
  rtc.halt(false);
   
  //As linhas abaixo setam a data e hora do modulo
  //comentar apos a primeira utiliza��o se necessario
  rtc.setDOW(TUESDAY);      //Define o dia da semana
  rtc.setTime(15, 48, 0);     //Define o horario
  rtc.setDate(27, 4, 2021);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
   
  Serial.begin(9600); // RTC



  
} 

void loop(void) 
{ 
 // chamar sensores.requestTemperatures () para emitir uma temperatura global

 // pedido para todos os dispositivos no �nibus

/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: ");

 temp_sensor = sensors.getTempCByIndex(0);
 
 Serial.print(temp_sensor); // Por que "byIndex"?
   // Voc� pode ter mais de um DS18B20 no mesmo barramento.
   //0 refere-se ao primeiro IC no fio
   //delay(1000); 


if (temp_sensor<maxima){
  Serial.print(" [LOW!] ");
digitalWrite(porta_rele1, LOW);  //Desliga rele
}

if (temp_sensor>=maxima){
  Serial.print(" [HIGH!] ");
digitalWrite(porta_rele1, HIGH);  //Liga rele
   }

// RTC Mostra as informa��es no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
   
  //Aguarda 1 segundo e repete o processo
  delay (1000); // RTC




} //main