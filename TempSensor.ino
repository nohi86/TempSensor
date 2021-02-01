#include <Arduino.h>
#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw(void) {
  u8g2_prepare();
  char TempString[6];
  dtostrf(sensors.getTempCByIndex(0),2,2, TempString);
  
  u8g2.drawStr(0,10,"TEAG");
  u8g2.drawStr(0,30,"Temperatur: ");
  u8g2.drawStr(70,30,TempString);
  u8g2.drawStr(105,30,"C");
}

void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
  sensors.begin();
}

void loop(void) {
  sensors.requestTemperatures();
  Serial.println(sensors.getTempCByIndex(0)); 
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  delay(1000);
}
