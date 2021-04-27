#include <OneWire.h>//temp
#include <DallasTemperature.h>//temp

#include <Wire.h>
#include <RTClib.h>


RTC_DS1307 rtc;
OneWire pino(3);//temp
DallasTemperature barramento(&pino);//temp
DeviceAddress sensor;//temp


void setup(void)//temp
{
char texto[255];
char diasDaSemana[7][10] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
char mesDoAno[13][10] = {"", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};


 Serial.begin(9600);//temp
  barramento.begin();//temp
  barramento.getAddress(sensor, 0);  //temp



 // Serial.begin(9600);
//delay(1000);

if (rtc.begin()) {
DateTime now = rtc.now();
int dia = now.day();
int mes = now.month();
int ano = now.year();
int hora = now.hour();
int minuto = now.minute();
int segundo = now.second();

sprintf(texto, "Hoje: %s, %02d/%02d/%04d Hora: %02d:%02d:%02d", diasDaSemana[now.dayOfTheWeek()], dia, mes, ano, hora, minuto, segundo);
Serial.println(texto);

sprintf(texto, "Hoje: %s, %02d/%s/%04d Hora: %02d:%02d:%02d", diasDaSemana[now.dayOfTheWeek()], dia, mesDoAno[mes], ano, hora, minuto, segundo);
Serial.println(texto);
}
else {
Serial.println("Modulo RTC nao encontrado!");
}

  
 
}
void loop()
{

  
  barramento.requestTemperatures(); //temp
  float temperatura = barramento.getTempC(sensor);//temp
  Serial.print(temperatura);//temp
  delay(500);//temp

}
