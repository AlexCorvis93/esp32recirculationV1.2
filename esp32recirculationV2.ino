#include <Preferences.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <pgmspace.h>


Preferences preferences;
#define UVsensor 15
#define relay 12
#define buttPinRST 35
#define buttPinStart 26
#define buttPinMode 33
#define TFT_CS 5
#define TFT_RST  16
#define TFT_DC  17
boolean flag = 0;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
int64_t timer = 0;
boolean flag1 = 0;
boolean flag2 = 0;
boolean flag3 = 0;
boolean flag4 = 1;
boolean flag5 = 0;
boolean flag6 = 0;
int timer30 = 30;
int timer60 = 60;
int goTime = 0;
int timerr30 = 0;
int sensValue = 0;

void setup() {
  
 preferences.begin("coun-hour", false);
 goTime = preferences.getInt("goTime", 0);
 tft.initR(INITR_BLACKTAB); // initcialization
 tft.fillScreen(ST7735_BLACK);
 tft.setRotation(1);
 pinMode (relay, OUTPUT);
 digitalWrite(relay, LOW);
 pinMode (buttPinRST, INPUT); ///RESET
 pinMode(buttPinStart, INPUT);//START
 pinMode(buttPinMode, INPUT);//MODE
  ///logo
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold12pt7b);
  tft.fillScreen(ST7735_BLACK);
  delay(2000);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_BLUE);
  tft.setCursor(40, 25);
  tft.print("U-MTS");
  tft.setCursor(30, 55);
  tft.print("Medical");
  tft.setCursor(0, 75);
  tft.print("Technologies");
  delay(2000);

  //////MODE
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold9pt7b);
  tft.fillScreen(ST7735_BLACK);
  delay(2000);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Mode:");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 45);
  tft.print(">");            /////cursor
  tft.setCursor(20, 45);
  tft.print("continuously");
  tft.setCursor(20, 75);
  tft.print("30 min");
  tft.setCursor(20, 105);
  tft.print("60 min");
}


void loop () {
clear_Mem ();
  if (digitalRead(buttPinStart) == HIGH && digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 1)///если кнопку нажал один раз меню
  {
    flag1 = 0;
    flag2 = 1;
    flag3 = 1;
    flag4 = 0;
    tft.fillScreen(ST7735_BLACK);
    digitalWrite(relay, HIGH);
    delay(600);
    sensValue = analogRead(UVsensor);
    do {
      if (sensValue > 1160){ 
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(35, 15);
      tft.print("UV lamp-OK");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 105);
      tft.print("selected mode:");
      tft.setCursor(5, 120);
      tft.print("continuosly");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 55);
      tft.print("UV-TIME:");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 80);
      tft.print(goTime);
      }else if (sensValue < 1160){  
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(35, 15);
      tft.print("UV lamp-!");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 105);
      tft.print("selected mode:");
      tft.setCursor(5, 120);
      tft.print("continuosly");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 55);
      tft.print("UV-TIME:");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 80);
      tft.print(goTime);
      }
      ///////////////////////schetchik ////////////
      if (millis() - timer >= 3600000 && sensValue > 1160 ) {
        tft.fillScreen(ST7735_BLACK);
        goTime++;
      //  preferences.putInt("goTime", goTime);
        timer = millis();
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(60, 80);
        tft.print(goTime);
      }
    } while (digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 1 && flag3 == 1 && flag4 == 0);
  }

  if (digitalRead(buttPinStart) == LOW && digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 1 && flag3 == 1 && flag4 == 0)
  {
    flag1 = 0;
    flag2 = 1;
    flag3 = 1;
    flag4 = 0;
  }

  ///////////////////////////////////////////MODE SELECT 30////////////////////////////////////////////////////////////////////////////////
  /// if press mode 30
  if (digitalRead(buttPinMode) == HIGH && digitalRead(buttPinStart) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 1)///если кнопку нажал один раз меню
  {

    flag1 = 1;
    flag2 = 0;
    flag3 = 1;
    flag4 = 0;
    mode_30();
  }
  if (digitalRead(buttPinMode) == LOW && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0)
  {
    flag1 = 1;
    flag2 = 0;
    flag3 = 1;
    flag4 = 0;
  }
////////////////////////////////////////TIMER 30/////////////////////////////////////////////////////////////////////////////////// 
  if (digitalRead(buttPinMode) == LOW && digitalRead(buttPinStart) == HIGH && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0 && flag5 == 0)
  {
    flag1 = 1;
    flag2 = 0;
    flag3 = 1;
    flag4 = 0;
    flag5 = 1;
    tft.fillScreen(ST7735_BLACK);
    digitalWrite(relay, HIGH);
    delay(600);
    sensValue = analogRead(UVsensor);
    do{ 
      if (sensValue > 1160){
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(35, 15);
      tft.print("UV lamp-OK");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 109);
      tft.print("selected mode:");
      tft.setCursor(5, 125);
      tft.print("30 min");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 68);
      tft.print("TIMER :");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer30);
      }else if (sensValue < 1160){
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(35, 15);
      tft.print("UV lamp-!");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 109);
      tft.print("selected mode:");
      tft.setCursor(5, 125);
      tft.print("30 min");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 68);
      tft.print("TIMER :");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer30);
      }
      /////////////////NARABOTKA/////////////
      if (millis() - timer >= 60000 && sensValue > 1160) {
      tft.fillScreen(ST7735_BLACK);
      timer30--;
      timer = millis();
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer30);
      tft.setFont(&FreeMono9pt7b);
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(5, 40);
      tft.print("uv-time:");
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(90, 40);
      tft.print(goTime);
      }else if (timer30 == 0){
       digitalWrite(relay, LOW);
       timer30 = 30;
       tft.fillScreen(ST7735_BLACK);
       timer = millis();
       flag5 = 0;
       flag1 = 0;
       flag2 = 0;
       flag3 = 0;
       flag4 = 1;
       mode_main();
       }
      }while (digitalRead(buttPinMode) == LOW && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0 && flag5 == 1); 
  } 
     
  if (digitalRead(buttPinMode) == LOW && digitalRead(buttPinStart) == LOW && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0 && flag5 == 1)
   {
    flag1 = 1;
    flag2 = 0;
    flag3 = 1;
    flag4 = 0;
    flag5 = 1;
   }
   //////////////////////////////////////////////////EXIT IN MODE MAIN///////////////////TIMER30///////////////
  if (digitalRead(buttPinMode) == HIGH & digitalRead(buttPinStart) == LOW && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0 && flag5 == 1)
         {
          digitalWrite(relay, LOW);
          timer30 = 30;
          flag5 = 0;
          flag1 = 0;
          flag2 = 0;
          flag3 = 0;
          flag4 = 1;
          mode_main();
         }
  /// //////////////////MODE SELECT 60//////////////////////////////////////////////////////////////////
  if (digitalRead(buttPinMode) == HIGH && flag1 == 1 && flag2 == 0 && flag3 == 1 && flag4 == 0)
  {

    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 0;
    mode_60();
  }
  if (digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0)
  {
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 0;
  }
////////////////////////////////////////TIMER 60/////////////////////////////////////////////////////////////////////////////////// 
  if (digitalRead(buttPinMode) == LOW && digitalRead(buttPinStart) == HIGH && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag6 == 0)
  {
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 0;
    flag6 = 1;
    tft.fillScreen(ST7735_BLACK);
    digitalWrite(relay, HIGH);
    delay(600);
    sensValue = analogRead(UVsensor);
    do{
      if (sensValue > 1160){
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(35, 15);
      tft.print("UV lamp-OK");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 109);
      tft.print("selected mode:");
      tft.setCursor(5, 125);
      tft.print("60 min");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 68);
      tft.print("UV-TIME:");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer60);
      }else if (sensValue < 1160){
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(35, 15);
      tft.print("UV lamp-!");
      tft.setFont(&FreeSansBold9pt7b);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(5, 109);
      tft.print("selected mode:");
      tft.setCursor(5, 125);
      tft.print("60 min");/// write mode!!
      tft.setTextColor(ST7735_WHITE);
      tft.setFont(&FreeSansBold12pt7b);
      tft.setCursor(15, 68);
      tft.print("UV-TIME:");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer60);
      }
      if (millis() - timer >= 60000 && sensValue > 1160) {
      tft.fillScreen(ST7735_BLACK);
      timer60--;
      timer = millis();
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(60, 90);
      tft.print(timer60);
      tft.setFont(&FreeMono9pt7b);
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(5, 40);
      tft.print("uv-time:");
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(90, 40);
      tft.print(goTime);
      }else if (timer60 == 0 ){
       digitalWrite(relay, LOW);
       timer60 = 60;
       goTime++;
       tft.fillScreen(ST7735_BLACK);
       timer = millis();
       flag6 = 0;
       flag1 = 0;
       flag2 = 0;
       flag3 = 0;
       flag4 = 1;
       mode_main();
       }
      }while (digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag6 == 1); 
  } 
     
  if (digitalRead(buttPinMode) == LOW && digitalRead(buttPinStart) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag6 == 1)
   {
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 0;
    flag6 = 1;
   }
   //////////////////////////////////////////////////EXIT IN MODE MAIN///////////////////TIMER60///////////////
  if (digitalRead(buttPinMode) == HIGH & digitalRead(buttPinStart) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag6 == 1)
         {
          digitalWrite(relay, LOW);
          flag5 = 0;
          flag1 = 0;
          flag2 = 0;
          flag3 = 0;
          flag4 = 1;
          flag6 = 0;
          mode_main();
         }
  /////////////////////////////////////SELECT continuosly////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(buttPinMode) == HIGH && digitalRead(buttPinStart) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0)
  {

    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 1;
    mode_continuosly();
  }

  if (digitalRead(buttPinMode) == LOW && digitalRead(buttPinStart) == LOW && flag1 == 1 && flag2 == 1 && flag3 == 1 && flag4 == 1)
  {

    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 1;
  }

  ///////////////////////////////EXIT IN MAIN MENU////////////////////////////CONTINUOSLY//////////////////////////
  if (digitalRead(buttPinMode) == HIGH && digitalRead(buttPinStart) == LOW && flag1 == 0 && flag2 == 1 && flag3 == 1 && flag4 == 0 )
  {
    digitalWrite(relay, LOW);
   // preferences.end();
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 1;
    mode_main();

  }



  if (digitalRead(buttPinMode) == LOW && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 1)
  {
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flag4 = 1;
  }
}

//////////////////////////////////////////CLEAR MEMORY/////////////////////
void clear_Mem () {
  if (digitalRead(buttPinStart) == HIGH && digitalRead(buttPinMode) == HIGH && digitalRead(buttPinRST) == HIGH) {
    delay(300);
    goTime = preferences.getInt("goTime", 0);
    preferences.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////
void mode_main() {
  delay(300);
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Mode:");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 45);
  tft.print(">");            /////cursor
  tft.setCursor(20, 45);
  tft.print("continuously");
  tft.setCursor(20, 75);
  tft.print("30 min");
  tft.setCursor(20, 105);
  tft.print("60 min");

}
//////////////////////////////////////////////////////////
void mode_continuosly() {
  delay(300);
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Mode:");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 45);
  tft.print(">");            /////cursor
  tft.setCursor(20, 45);
  tft.print("continuously");
  tft.setCursor(20, 75);
  tft.print("30 min");
  tft.setCursor(20, 105);
  tft.print("60 min");
}

void mode_30() {
  delay(300);
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Mode:");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(20, 45);
  tft.print("continuously");
  tft.setCursor(5, 75);
  tft.print(">");    //cursor
  tft.setCursor(20, 75);
  tft.print("30 min");
  tft.setCursor(20, 105);
  tft.print("60 min");

}

///////////////////////////////////////////////////////////////////////
void mode_60() {
  delay(300);
  tft.fillScreen(ST7735_BLACK);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Mode:");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(20, 45);
  tft.print("continuously");
  tft.setCursor(20, 75);
  tft.print("30 min");
  tft.setCursor(5, 105);
  tft.print(">");        ///cursor
  tft.setCursor(20, 105);
  tft.print("60 min");

}
