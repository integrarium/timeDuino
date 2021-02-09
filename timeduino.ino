#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include <LiquidCrystal.h>                // Подключяем библиотеку
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );    // Указываем порты         

tmElements_t tm;
tmElements_t tm_start;                  // время начала периода
int x;                                  // Создаем переменную x
int t = 30; // начальное значение таймера 30минут
 
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("TimeDuino");
  Serial.println("-------------------");

  lcd.begin(16, 2);                       // Инициализируем LCD 16x2  
  lcd.setCursor(0,0);                     // Установить курсор на первую строку  
  lcd.print("TimeDuino");                   // Вывести текст
  lcd.setCursor(0,1);                     // Установить курсор на вторую строку
  lcd.print("integrarium.ru");          // Вывести текст


}

void loop() {

  

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();

    lcd.setCursor(0,1);                     // Установить курсор на вторую строку
    lcd.print(tm.Hour);          // Вывести текст
    lcd.print(":"); 
    lcd.print(tm.Minute);          // Вывести текст
    lcd.print(":"); 
    lcd.print(tm.Second);          // Вывести текст
    lcd.print(" "); 
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }

    delay(9000);
  }

x = analogRead (0);                     // Задаем номер порта с которого производим считывание 
  lcd.setCursor(10,1);                     // Установить курсор на первую строку  
  if (x < 100) {                          // Если x меньше 100 перейти на следующею строк
  lcd.print ("Stop");                   // Вывести текст 
}
  else if (x < 200) {                     // Если х меньше 200 перейти на следующию строку
  lcd.print ("+5");                   // Вывести текст 
}
  else if (x < 400){                      // Если х меньше 400 перейти на следующию строку
  lcd.print ("-5");                   // Вывести текст
}
  else if (x < 600){                      // Если х меньше 600 перейти на следующию строку
  lcd.print ("Start");                   // Вывести текст
  RTC.read(tm_start);                 // запоминаем время старта
  lcd.setCursor(0,0);                     // Установить курсор на первую строку
  lcd.print("Start "); 
    lcd.print(tm_start.Hour);          // часы
    lcd.print(":"); 
    lcd.print(tm_start.Minute);          // минуты
    lcd.print(":"); 
    lcd.print(tm_start.Second);          // секунды
    lcd.print(" "); 
}
  else if (x < 800){                      // Если х меньше 800 перейти на следующию строку
  lcd.print ("Select");                   // Вывести текст
}

if 
}

void print2digits(int number) 
{
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
