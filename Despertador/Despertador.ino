#include <LiquidCrystal_I2C.h>    // Inclui a Biblioteca
#include <RTClib.h>               // Inclui a Biblioteca
 
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);   // Inicia o display 16x2 no endereço 0x27
 
#define buzzer 11   // Define o buzzer como pino 11
 
int Hor;            // Inicia a variável Hor
int Min;            // Inicia a variável Min
int Seg;            // Inicia a variável Seg
 
void setup()  {
  pinMode(buzzer, OUTPUT);
  rtc.begin();              // Inicia o módulo RTC
  lcd.init();               // Inicia o Display
  lcd.backlight();          // Inicia o Backlight
}
 
void loop()   {
  DateTime now = rtc.now();
  Hor = rtc.now().hour();     // Chama o horário de Hor
  Min = rtc.now().minute();   // Chama o minuto de Min
  Seg = rtc.now().second();   // Chama os segundos de Seg
 
  // Define o horário do despertador e executa o som do buzzer
  if ( Hor == 15 &&  Min == 7) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
  }
 
  lcd.setCursor(3, 0);              // Posiciona o cursor na primeira linha
  lcd.print("Hora: ");              // Imprime o texto "Hora: "
  lcd.print(Hor);                   // Imprime a Hora
  lcd.print(":");                   // Imprime o texto entre aspas
  lcd.print(Min);                   // Imprime o Minuto
  lcd.print(":");                   // Imprime o texto entre aspas
  lcd.print(Seg);                   // Imprime o Segundo
 
  lcd.setCursor(2, 2);              // Posiciona o cursor na segunda linha
  lcd.print("Data: ");              // Imprime o texto entre aspas
  lcd.print(rtc.now().day());       // Imprime o Dia
  lcd.print("/");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().month());     // Imprime o Mês
  lcd.print("/");                   // Imprime o texto entre aspas
  lcd.print(rtc.now().year());      // Imprime o Ano
 
  delay(1000);                      // Aguarda 1 segundo e reinicia
  lcd.clear();
}
