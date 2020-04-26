
#include <FastLED.h>
//v2.0

#include         <Adafruit_Thermal.h>
#include         <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define NUM_LEDS 28
#define DATA_PIN 22
CRGB leds[NUM_LEDS];

static const uint8_t PROGMEM fetch_logo [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x7C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xC0, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xC1, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xC3, 0xDC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xC7, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE1, 0xCF, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xC1, 0xCE, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0xFE, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x01, 0xFC, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x01, 0xF8, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x01, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xE0, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x78, 0x01, 0xE0, 0x1C, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x1C,
  0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1C, 0x0F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x1C,
  0x07, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x03, 0xC0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x01, 0xE0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0xF0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x78, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x3C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x1E, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x0F, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x1C,
  0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xC0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xE0, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0xE1, 0xFF, 0xE0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0xE0, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x38, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x38, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x38, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x1C, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x0E, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x07, 0x1C, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x07, 0x1C,
  0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x07, 0x1C, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x03, 0x9C,
  0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x03, 0x9C, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x03, 0x9C,
  0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x01, 0x9C, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x01, 0xDC,
  0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void(* resetFunc) (void) = 0;

String RUS(String str) {                                                                                                                     // Определяем функцию которая преобразует код русских символов из кодировки UTF-8 в кодировку CP866
  uint32_t i = 0, j = 0;                                                                                                                  // Определяем переменные: i - счетчик входящих символов, j - счетчик исходящих символов
  while (str[i]) {                                                                                                                       // Проходим по всем символам строки str, пока не встретим символ конца строки (код 0)

    if (uint8_t(str[i]) == 0xD0 && uint8_t(str[i + 1]) >= 0x90 && uint8_t(str[i + 1]) <= 0xBF ) {

      str[j] = (uint8_t) str[i + 1] - 0x10;
      i++;

    } else // Символы «А-Я а-п» (код UTF-8: D090-D0AF D0B0-D0BF) сохраняем в кодировке CP866: код 80-9F A0-AF (символ занимал 2 байта, а стал занимать 1 байт)
      if (uint8_t(str[i]) == 0xD1 && uint8_t(str[i + 1]) >= 0x80 && uint8_t(str[i + 1]) <= 0x8F ) {

        str[j] = (uint8_t) str[i + 1] + 0x60;
        i++;
      } else // Символы «р-я»     (код UTF-8: D180-D18F)           сохраняем в кодировке CP866: код E0-EF       (символ занимал 2 байта, а стал занимать 1 байт)
        if (uint8_t(str[i]) == 0xD0 && uint8_t(str[i + 1]) == 0x81                              ) {

          str[j] = 0xF0;
          i++;
        } else // Символ «Ё»        (код UTF-8: D081)                сохраняем в кодировке CP866: код F0          (символ занимал 2 байта, а стал занимать 1 байт)
          if (uint8_t(str[i]) == 0xD1 && uint8_t(str[i + 1]) == 0x91                              ) {

            str[j] = 0xF1;
            i++;
          } else // Символ «ё»        (код UTF-8: D191)                сохраняем в кодировке CP866: код F1          (символ занимал 2 байта, а стал занимать 1 байт)
          {

            str[j] = (uint8_t) str[i];
          }  j++; i++;      // Остальные символы оставляем как есть, без преобразования, но их место в строке могло сдвинуться, если до них были встречены русские символы
  }   while (j < i) {

    str[j] = 0;
    j++;
  } return str;                                                                                             // Так как место занимаемое символами в строке могло уменьшиться, заполняем оставщиеся байты символами конца строки (код 0)
}

String            RUS(String);
String data;
String output;
String uptime = "[UPTIME ERROR]";
String queue;
char printing = 'X';
char beeping = 'X';
char showing = 'X';
int x;
uint32_t timer;
uint32_t CTtimer;
uint32_t upt_timer;
uint32_t WStick;
bool inMenu = false;
bool isCounting = false;
bool isAsleep = false;
bool inDev;
bool printed = false;
bool WSon;
int duty = 0;
int menupage = 0;


//  Подключаем библиотеку для работы с принтером
//Serial1   mySerial(18, 19);

Adafruit_Thermal printer(&Serial1, 46);
//String            RUS(String);

void setup() {
  pinMode(10, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(50, OUTPUT);
  digitalWrite(52, HIGH);
  digitalWrite(50, HIGH);
  digitalWrite(10, HIGH);

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  if (EEPROM.read(1) == 1) {
    WSon = true;
  } else {
    WSon = false;
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }
  }
  FastLED.show();
  Serial.begin(9600);
  Serial1.begin(9600);
  printer.begin();
  lcd.begin(16, 2);
  printer.setCodePage(CODEPAGE_CP866);
  printer.wake();


  lcd.print("FETCH");
  if (EEPROM.read(0) == 1) {
    inDev = true;
    lcd.setCursor(13, 0);
    lcd.print("[D]");
  } else {
    inDev = false;
  }
  lcd.setCursor(0, 1);
  lcd.print("DEVELOPMENT");
  delay(2000);
  lcd.clear();

  upt_timer = millis();
  WStick = millis();

  /*
    for (int i = 0 ; i < 24; i++ ) {
    leds[i].setRGB(0, 139, 255);
    }


    for (int i = 0 ; i < NUM_LEDS; i++ ) {
    for (int j = 50 ; j < 100; j++ ) {
      leds[i].setRGB( 0, j, j);
      leds[i + 1].setRGB(0, j - 50, j - 50);
      leds[i + 12].setRGB( 0, j, j);
      LEDS.show();


    }
    }
    for (int i = 0 ; i < NUM_LEDS; i++ ) {
    for (int j = 50 ; j < 100; j++ ) {
      leds[i].setRGB( 0, 0, j);
      leds[i + 1].setRGB(0, 0, j - 50);
      leds[i + 12].setRGB( 0, 0, j);
      LEDS.show();

    }
    }
  */
}



void loop() {

  x = analogRead (0);

  if (millis() - upt_timer > 120000) {
    uptime = "[UPTIME ERROR]";
  }

  if (inMenu == false) {
    if (printed == false) {
      digitalWrite(10, LOW);
      lcd.clear();
      printed = true;
    }
    if (millis() - WStick >= 30 && WSon) {
      int Position = 0;

      for (int i = 0; i < NUM_LEDS * 2; i++)
      {
        Position++; // = 0; //Position + Rate;
        for (int i = 0; i < NUM_LEDS; i += 2) {
          leds[i].setRGB(0,
                         ((sin(i + Position) * 127 + 128) / 255) * 255,
                         ((sin(i + Position) * 127 + 128) / 255) * 255);
          FastLED.show();
        }
        for (int i = 1; i < NUM_LEDS; i += 2) {

          leds[i].setRGB(0, 0, ((sin(i + Position) * 127 + 128) / 255) * 255);
          FastLED.show();
        }

        FastLED.show();

      }
      FastLED.show();
      WStick = millis();
    }  if (millis() - WStick >= 30 && WSon) {
      int Position = 0;

      for (int i = 0; i < NUM_LEDS * 2; i++)
      {
        Position++; // = 0; //Position + Rate;
        for (int i = 0; i < NUM_LEDS; i += 2) {
          leds[i].setRGB(0,
                         ((sin(i + Position) * 127 + 128) / 255) * 255,
                         ((sin(i + Position) * 127 + 128) / 255) * 255);
          FastLED.show();
        }
        for (int i = 1; i < NUM_LEDS; i += 2) {

          leds[i].setRGB(0, 0, ((sin(i + Position) * 127 + 128) / 255) * 255);
          FastLED.show();
        }

        FastLED.show();

      }
      FastLED.show();
      WStick = millis();
    }

  } else if (isCounting == false && menupage == 0) {
    if (printed == false) {
      digitalWrite(10, HIGH);
      lcd.clear();

      for (int i = 0; i < uptime.length(); i++) {
        lcd.print(uptime[i]);
        if (i == 15) lcd.setCursor(0, 1);
      }

      printed = true;
    }

  } else if (isCounting == false && menupage == 1) {
    if (printed == false) {
      digitalWrite(10, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("SILVERWING II");
      lcd.setCursor(0, 1);
      lcd.print("PWR I/O<");
      lcd.setCursor(9, 1);
      lcd.print(">REBOOT");
      printed = true;
    }
  }
  else if (isCounting == false && menupage == 2) {
    if (printed == false) {
      digitalWrite(10, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("THUNDERBIRD P1");
      lcd.setCursor(0, 1);
      lcd.print("RECALL<");
      lcd.setCursor(8, 1);
      if (isAsleep == false) lcd.print(">SLEEP"); else lcd.print(">WAKE");
      printed = true;
    }
  }
  else if (isCounting == false && menupage == 3) {
    if (printed == false) {
      digitalWrite(10, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("WolfSight S1");
      lcd.setCursor(0, 1);
      if(WSon)lcd.print("SWITCH OFF<"); else lcd.print("SWITCH ON<");
      lcd.setCursor(8, 1);
      printed = true;
    }
  }
  else if (isCounting == false && menupage == 4) {
    if (printed == false) {
      digitalWrite(10, HIGH);
      lcd.setCursor(0, 0);
      if (inDev == false) lcd.print("ENTER DEV MODE?"); else lcd.print("EXIT DEV MODE?");
      lcd.setCursor(0, 1);
      lcd.print("YES<");
      lcd.setCursor(8, 1);
      printed = true;
    }
  }

  if (x < 800 && x > 600) {
    printed = false;
    lcd.clear();
    isCounting = false;
    digitalWrite(10, HIGH);
    if (inMenu == false) {
      inMenu = true;
      menupage = 0;
      while (x < 800 && x > 600) {
        x = analogRead (0);
      }
    } else if (menupage == 0) menupage = 1; else if (menupage == 1) menupage = 2; else if (menupage == 2) menupage = 3; else if (menupage == 3) menupage = 4; else if (menupage == 4) menupage = 0;
    tone(49, 1500);
    delay(50);
    noTone(49);
    delay(150);
    timer = millis();
  }

  if (x < 600 && inMenu == true && menupage == 1) {
    timer = millis();
    duty = 1;
    lcd.clear();
    lcd.print("PERFORMING...");
    isCounting = true;
    lcd.setCursor(0, 1);
    tone(49, 1500);
    delay(300);
    noTone(49);
    CTtimer = millis();
  }

  if (x < 600 && x > 60 && inMenu == true && menupage == 2) {
    if (printing == 'X' || beeping == 'X' || showing == 'X') {
      lcd.clear();
      lcd.print("EMPTY BUFFER");
      tone(49, 1500);
      delay(100);
      noTone(49);
      delay(1900);
    } else {
      perform(printing, beeping, showing, data);
    }

  }

  if (x < 600 && x > 60 && inMenu == true && menupage == 3) {
    if (WSon) {
      WSon = false;
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(0, 0, 0);
      }
      FastLED.show();
      EEPROM.write(1, 0);
    }else{
      WSon = true;
      EEPROM.write(1, 1);
    }
     tone(49, 1500);
    delay(100);
    noTone(49);
    delay(1900);
    printed = false;
  }

  if (x < 600 && x > 60 && inMenu == true && menupage == 4) {
    lcd.clear();
    if (inDev == false) {
      lcd.print("DEV MODE ENABLED");
      inDev = true;
      EEPROM.write(0, 1);
    }
    else {
      lcd.print("DEV MODE DISABLE");
      inDev = false;
      EEPROM.write(0, 0);
    }
    tone(49, 1500);
    delay(100);
    noTone(49);
    delay(1900);
    printed = false;
  }

  if (x < 60 && inMenu == true && menupage == 1) {
    timer = millis();
    duty = 2;
    lcd.clear();
    lcd.print("REBOOTING...");
    isCounting = true;
    lcd.setCursor(0, 1);
    tone(49, 1500);
    delay(100);
    noTone(49);
    CTtimer = millis();
  }
  if (x < 60 && inMenu == true && menupage == 2) {
    if (isAsleep) {
      lcd.clear();
      printer.wake();
      isAsleep = false;
      lcd.print("NOW WOKEN");
    }
    else {
      lcd.clear();
      printer.sleep();
      isAsleep = true;
      lcd.print("NOW ASLEEP");
    }
    tone(49, 1500);
    delay(100);
    noTone(49);
    delay(1900);
    printed = false;
  }


  if ((millis() - timer >= 3000) && inMenu == true && isCounting == false) {
    inMenu = false;
    printed = false;
  }

  if (isCounting == true) {

    if (millis() - timer >= 1000) {
      lcd.print("-");
      timer = millis();
    }
    else if (millis() - CTtimer >= 16000) {

      if (duty == 1) {
        lcd.clear();
        lcd.print("PERFORMING...");
        digitalWrite(52, LOW);
        delay(1000);
        digitalWrite(52, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("DONE");
        delay(3000);
        isCounting = false;
        inMenu = false;
        printed = false;


      } else {
        lcd.clear();
        lcd.print("REBOOTING...");
        digitalWrite(50, LOW);
        delay(1000);
        digitalWrite(50, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("DONE");
        delay(3000);
        isCounting = false;
        inMenu = false;
        printed = false;
      }
    }
  }

  if (Serial.available() > 0) {




    data = "";
    printing = "";
    beeping = "";
    showing = "";
    output = "";

    data = Serial.readString();
    if (inDev == true) {
      lcd.clear();
      digitalWrite(10, HIGH);

      if (data.length() <= 16) {
        lcd.print(data);
        delay(1000);
        x = analogRead (0);
        while (!(x < 800 && x > 600)) {
          x = analogRead (0);
        }
        delay(100);
      } else if (data.length() > 32) {
        for (int j = 0; j < data.length() / 32; j++) {
          lcd.setCursor(0, 0);
          for (int i = 32 * j; i < (32 * j) + 16; i++) {
            lcd.print(data[i]);
          }
          lcd.setCursor(0, 1);
          for (int k = (32 * j) + 16; k < (32 * j) + 32; k++) {
            lcd.print(data[k]);
          }
          delay(1000);
          x = analogRead (0);
          while (!(x < 800 && x > 600)) {
            x = analogRead (0);
          }
          lcd.clear();
          delay(100);
        }
      }
      else {
        lcd.setCursor(0, 0);
        for (int i = 0; i < 16; i++) {
          lcd.print(data[i]);
        }
        lcd.setCursor(0, 1);
        for (int i = 16; i < data.length(); i++) {
          lcd.print(data[i]);
        }

        x = analogRead (0);
        while (!(x < 800 && x > 600)) {
          x = analogRead (0);
        }
        lcd.clear();
        delay(100);
      }
      delay(100);
      lcd.clear();
      lcd.print("EXECUTE?");
      lcd.setCursor(0, 1);
      lcd.print("Y<");
      lcd.setCursor(14, 1);
      lcd.print(">N");

      x = analogRead (0);
      while (!(x < 600 && x > 60) && !(x < 60)) {
        x = analogRead (0);
      }
      if (x < 60) {
        resetFunc();
      }
    }

    if (data[0] == '-') {
      printing = data[1];
      beeping = data[2];
      showing = data[3];
      perform(printing, beeping, showing, data);
    } else {
      Serial.println("!ER4: WRONG DATA BEGIN");
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(10, HIGH);
      lcd.print("ER4:");
      lcd.setCursor(0, 1);
      lcd.print("WRONG DATA BEGIN");
      delay(4000);
      lcd.clear();
      printed = false;
    }
    lcd.clear();
    printed = false;
  }



}



static void perform(char Fprinting, char Fbeeping, char Fshowing, String Fdata) {

  String Foutput;

  if ((Fprinting == 'S' || Fprinting == 'R' || Fprinting == 'M' || Fprinting == 'N' || Fprinting == 'D') && (Fbeeping == 'S' || Fbeeping == 'P' || Fbeeping == 'N') && (Fshowing == 'S' || Fshowing == 'P' || Fshowing == 'M' || Fshowing == 'U' || Fshowing == 'W' || Fshowing == 'N')) {

    if (Fshowing == 'S' || Fshowing == 'M' || Fshowing == 'P') {
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(10, HIGH);
      lcd.print("INCOMING -");
      lcd.print(Fprinting);
      lcd.print(Fbeeping);
      lcd.print(Fshowing);
      lcd.print("-");
      delay(100);
    }

    if (Fbeeping == 'S') {
      tone(49, 2019);
      delay(100);
      noTone(49);
      delay(100);
      tone(49, 2019);
      delay(100);
      noTone(49);
    }
    if (Fshowing == 'S' || Fshowing == 'M' || Fshowing == 'P') blink();


    if (Fdata.length() > 5) {
      for (int i = 5; i < Fdata.length(); i++) {
        if (Fdata[i] != '_' && Fdata[i] != '/') Foutput += Fdata[i]; else if (Fdata[i] == '/') Foutput += "\r\n"; else Foutput += ' ';
      }
      if (Fshowing == 'U') {
        uptime = Foutput;
        upt_timer = millis();
      }    else if (Fshowing == 'W') {
        if (Foutput == "on") {
          WSon = true;
          EEPROM.write(1, 1);
        } else {
          EEPROM.write(1, 0);
          WSon = false;
          for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].setRGB( 0, 0, 0);
            LEDS.show();
          }
        }
      }

      if (Fprinting != 'N') {
        lcd.setCursor(0, 1);
        lcd.print("PREPARING..");

        printer.wake();
        isAsleep = false;

        if (printer.hasPaper()) {
          lcd.setCursor(0, 1);
          lcd.print("RUNNING... ");

          if (Fprinting == 'S') {
            printer.println(Foutput);

            printer.feed(3);
            lcd.print("OK");
            delay(4000);
          }
          else if (Fprinting == 'R') {
            // char* prs_output[output.length()];

            // for(int i = 0; i < output.length(); i++){
            // prs_output[i] = output[i];
            //}

            printer.println(RUS(Foutput));
            printer.feed(3);
            lcd.print("OK");
            delay(4000);
          }
          else if (Fprinting == 'M') {
            printer.inverseOn();
            printer.justify('C');
            printer.println("THUNDERBIRD P1");
            printer.doubleHeightOn();
            printer.println(RUS("НОВОЕ СООБЩЕНИЕ"));
            printer.setDefault();
            printer.setCodePage(CODEPAGE_CP866);
            printer.println(RUS(Foutput));
            printer.printBitmap(64, 84, fetch_logo);
            printer.feed(3);
            printer.setDefault();
            printer.setCodePage(CODEPAGE_CP866);
            lcd.print("OK");
            delay(4000);
          }

          else if (Fprinting == 'D') {

            for (int i = 0; i < Foutput.length(); i++) {

              if (Foutput[i] == '"') Foutput[i] = '\r\n';
            }
            printer.inverseOn();
            printer.justify('C');
            printer.println("THUNDERBIRD P1");
            printer.doubleHeightOn();
            printer.println(RUS("ПОСЛЕДНИЕ НОВОСТИ"));
            printer.setDefault();
            printer.setCodePage(CODEPAGE_CP866);
            printer.print(RUS(Foutput));
            printer.printBitmap(64, 84, fetch_logo);
            printer.feed(3);

          }






        } else {
          lcd.print("FAULT");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          digitalWrite(10, HIGH);
          lcd.print("ER3: NO PAPER");
          Serial.println("!ER3: CHECK PAPER");
          delay(4000);
          printed = false;
        }
      }

      if (Fshowing == 'M') {
        uint32_t blinker;
        bool shown = true;
        blinker = millis();
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("NEW MESSAGE");
        lcd.setCursor(0, 1);
        lcd.print("PRESS TO SUPRESS");
        x = analogRead (0);
        while (x > 800) {
          x = analogRead (0);

          if (millis() - blinker > 500) {
            blinker = millis();
            if (shown == true) {
              if (Fbeeping == 'P') noTone(49);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("PRESS TO SUPRESS");
              shown = false;
            } else {
              if (Fbeeping == 'P') tone(49, 2019);
              lcd.setCursor(2, 0);
              lcd.print("NEW MESSAGE");
              lcd.setCursor(0, 1);
              lcd.print("PRESS TO SUPRESS");
              shown = true;
            }
          }
          if (Serial.available() > 0) {
            if (data[0] == '-' && data[3] == 'U') {
              printing = data[1];
              beeping = data[2];
              showing = data[3];
              perform(printing, beeping, showing, data);
            }
          }
        }
        noTone(49);
        delay(100);
      }

      if (Fshowing == 'P') {
        uint32_t count;
        int pgMax;
        int pg = 0;
        count = millis();
        lcd.clear();
        lcd.setCursor(0, 0);

        if (Foutput.length() <= 32) {
          for (int i = 0; i < Foutput.length(); i++) {
            lcd.print(Foutput[i]);
            if (i == 15) lcd.setCursor(0, 1);
          }
          x = analogRead (0);
          while (x > 800) x = analogRead (0);
        }
        else {
          if (Foutput.length() % 32 == 0) pgMax = Foutput.length() / 32 - 1; else pgMax = (Foutput.length() / 32);
          x = analogRead (0);

          while (x > 800) {
            x = analogRead (0);

            if (millis() - count > 2000) {

              count = millis();
              lcd.clear();

              if (pg == pgMax && Foutput.length() % 32 != 0) {
                for (int i = pg * 32; i < Foutput.length(); i++) {
                  lcd.print(Foutput[i]);
                  if ((i + 1) % 16 == 0 && i != -1) lcd.setCursor(0, 1);
                }
              } else {
                for (int i = pg * 32; i < (pg * 32) + 32; i++) {
                  lcd.print(Foutput[i]);
                  if ((i + 1) % 16 == 0 && i != -1) lcd.setCursor(0, 1);
                }
              }

              if (pg < pgMax) pg++; else pg = 0;
            }

            if (Serial.available() > 0) {
              if (data[0] == '-' && data[3] == 'U') {
                printing = data[1];
                beeping = data[2];
                showing = data[3];
                perform(printing, beeping, showing, data);
              }
            }

          }
          delay(100);
        }
      }

    } else {
      lcd.print("FAULT");
      delay(1000);
      Serial.println("!ER5: NO TEXT PROVIDED");
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(10, HIGH);
      lcd.print("ER5:");
      lcd.setCursor(0, 1);
      lcd.print("EMPTY COMMAND");
      delay(4000);
      lcd.clear();
      printed = false;
    }
  }
  else {
    Serial.println("!ER6: CHECK OPERATORS");
    lcd.clear();
    lcd.setCursor(0, 0);
    digitalWrite(10, HIGH);
    lcd.print("ER6:");
    lcd.setCursor(0, 1);
    lcd.print("CHECK OPERATORS");
    delay(4000);
    lcd.clear();
    printed = false;
  }

  delay(50);
  lcd.clear();
  printed = false;
}
static void blink() {
  for (int i = 0 ; i < 11; i++ ) {
    //LEDS.setBrightness(200 * (-4 * (g - 0.5) * (g - 0.5) + 1));

    for (int j = 50 ; j < 100; j++ ) {
      leds[i].setRGB( 0, j, j);
      leds[i + 1].setRGB(0, j - 50, j - 50);
      leds[i + 12].setRGB( 0, j, j);
      leds[i + 13].setRGB(0, j - 50, j - 50);
      LEDS.show();


    }
  }

  for (int i = 0 ; i < 14; i++ ) {
    leds[i].setRGB( 0, 0, 0);
    leds[i + 11].setRGB( 0, 0, 0);
    LEDS.show();
    delay(20);
  }
  for (float g = 0.0; g < 1.1; g += 0.1) {
    for (int i = 24; i < NUM_LEDS; i++) {
      leds[i].setRGB( g * 255, g * 255, g * 255);
      LEDS.show();
      delay(5);
    }
  }

  for (float g = 1.0; g > -0.1; g -= 0.1) {
    for (int i = 24; i < NUM_LEDS; i++) {
      leds[i].setRGB( g * 255, g * 255, g * 255);
      LEDS.show();
      delay(10);
    }

  }

}
