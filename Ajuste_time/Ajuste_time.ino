#include <LiquidCrystal_I2C.h>    // Inclui a Biblioteca
#include <RTClib.h>               // Inclui a Biblioteca
 
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Inicia o display 16x2 no endereço 0x27
 
void setup()  {
  rtc.begin();                                        // Inicia o módulo RTC
 
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     // Ajuste Automático da hora e data
  //rtc.adjust(DateTime(2019, 11, 29, 10, 23, 00));   // Ajuste Manual (Ano, Mês, Dia, Hora, Min, Seg)
 
  lcd.init();           // Inicia o Display
  lcd.backlight();      // Inicia o Backlight
}
 
void loop()   {
  DateTime now = rtc.now();
 
  lcd.setCursor(1, 0);              // Posiciona o cursor na primeira linha
  lcd.print("Hora: ");              // Imprime o texto "Hora: "
  lcd.print(rtc.now().hour());      // Imprime a Hora
  lcd.print(":");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().minute());    // Imprime o Minuto
  lcd.print(":");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().second());    // Imprime o Segundo
 
  lcd.setCursor(0, 1);              // Posiciona o cursor na segunda linha
  lcd.print("Data: ");              // Imprime o texto entre aspas
  lcd.print(rtc.now().day());       // Imprime o Dia
  lcd.print("/");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().month());     // Imprime o Mês
  lcd.print("/");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().year());      // Imprime o Ano
 
  delay(1000);                      // Aguarda 1 segundo e reinicia
  lcd.clear();
}
