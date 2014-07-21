#include <TinyGPS++.h>//nicht benötigte Funktionen aus der Library entfernt, um SRAM zu sparen
#include <DHT.h>
#include "ascii.h"

//Temperatur- und Luftfeuchtigkeitssensor
DHT dht(4, 11);

//GPS via Serial
TinyGPSPlus gps;


//FORMAT: GRB
#define ARRAYLEN 43
uint8_t buffer[ARRAYLEN][8][3];

volatile uint32_t time;

uint8_t mode = 0;
uint8_t modeprev = 0;

uint8_t hours = 0;
uint8_t minutes = 0;
volatile uint8_t seconds = 0;

boolean minutePassed = true;

uint8_t hum = 0;
uint8_t temp = 0;


void setup() {
  //Serial zur Kommunikation mit GPS Modul
  Serial.begin(9600);
  
  //Timer 1 als uhrzeitgeber via interrupt
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;// 16 MHZ / 1024 -> alle 15625 schritte 1s um, 1 takt zum rücksetzen
  TCCR1B |= (1 << WGM12); // CTC modus
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler  auf 1024
  TIMSK1 |= (1 << OCIE1A); //compare interrupt an
  
  //Kompletten PORTB auf OUTPUT schalten
  DDRB = 0xFF;

  //GPS Daten empfangen
  while (!gps.time.isUpdated() || !gps.date.isUpdated() && millis() < 10000) {
    while (Serial.available() > 0)
      gps.encode(Serial.read());
  }
  if (gps.time.isUpdated()) {
    hours = gps.time.hour() + 2;
    minutes = gps.time.minute();
    seconds = gps.time.second();
  }

  pinMode(2, INPUT_PULLUP);
  
  attachInterrupt(0, hallInterrupt, FALLING);
  
  dht.begin();
}

ISR(TIMER1_COMPA_vect) {
  seconds++;
  if (seconds > 59) {
    minutes++;
    minutePassed = true;
    seconds = 0;
  }
  if (minutes > 59) {
    hours++;
    minutes = 0;
  }
  if (hours > 23)
    hours = 0;
}

void loop() {
  
  //Automatischer Moduswechsel
  if (seconds > 20 && seconds <= 40) {
    mode = 1;
  }
  else if (seconds > 40) {
    mode = 2;
  }
  else {
    mode = 0;
  }

  if (mode != modeprev) {
    clearBuffer();
    modeprev = mode;
  }

  
  
  //1 mal pro Minute Temperatur und Luftfeuchtigkeit updaten
  if (minutePassed){
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    minutePassed = false;
  }

  // Implementierung der Funktionen
  // UHR
  if (mode == 0) {
    char bufferH[3];
    char bufferS[3];
    char bufferM[3];

    sprintf(bufferH, "%02d", hours);
    sprintf(bufferM, "%02d", minutes);
    sprintf(bufferS, "%02d", seconds);
    
    strToAry(bufferH, 0, 255, 0, 255);
    
    strToAry(":", 11, 128, 0, 255);
    
    strToAry(bufferM, 15, 255, 0, 255);
    
    strToAry(":", 26, 128, 0, 255);
    
    strToAry(bufferS, 30, 255, 0, 255);
  }
  
  // Datum
  if(mode == 1){
      char bufferY[3];
      char bufferM[3];
      char bufferD[3];
      
      sprintf(bufferY,"%02d",gps.date.year() - 2000);
      sprintf(bufferM,"%02d",gps.date.month());
      sprintf(bufferD,"%02d",gps.date.day());
      
      strToAry(bufferD, 0, 255, 128, 0);
      
      byteToRGB(0b01000000, 12, 255, 255, 0);
      
      strToAry(bufferM, 15, 255, 128, 0);
      
      byteToRGB(0b01000000, 26, 255,255, 0);
      
      strToAry(bufferY, 30, 255, 128, 0);
    }

  // Thermo- und Hygrometer
  if (mode == 2) {
    char bufferT[3];
    char bufferH[3];

    sprintf(bufferH, "%02d", hum);
    sprintf(bufferT, "%02d", temp);

    strToAry(bufferT, 0, 0, 0, 255);
    
    //Gradzeichen
    byteToRGB(0b00000010, 12, 255, 255, 255);
    byteToRGB(0b00000101, 13, 255, 255, 255);
    byteToRGB(0b00000010, 14, 255, 255, 255);
    
    strToAry("C", 15, 255, 255, 255);
    
    strToAry(bufferH, 25, 0, 0, 255);
    
    strToAry("%", 38, 255, 255, 255);
  }

  //Demo der Textfunktionen
  if (mode == 3) {
    monoToRGB('P', 0, 255, 0, 0);
    monoToRGB('I', 5, 0, 255, 0);
    monoToRGB('N', 10, 0, 0, 255);
    monoToRGB('G', 15, 255, 0, 255);
    delay(1000);
    clearBuffer();
    strToAry("Gruppe", 0, 255, 0, 0);
    delay(1000);
    clearBuffer();
    strToAry("M 5", 0, 0, 0, 255);
    delay(1000);
  }
}

void printTheBuffer() { //Ausgabe des Display buffer Arrays auf die LEDs
  for (int i = 0; i < ARRAYLEN; i++) {
    showBuffer(i);
    delayMicroseconds(time / 128);
  }
}

void clearBuffer() {//Displaybuffer leeren
  uint8_t start = 0;
  for (int i = 0; i < ARRAYLEN; i++) {
    byteToRGB(0, start++, 0, 0, 0);
  }
}

void strToAry(char *s, int start, int r, int g, int b) {//string nach position start in den Displaybuffer einfügen
  while ( *s != '\0') {
    monoToRGB(*s, start, r, g, b);
    *s++;
    start += 6;
  }

}

void hallInterrupt() {//Interrupt durch Hallsensor, Messung der Umlaufzeit und einleiten der Ausgabe
  static uint32_t alt;
  time = micros() - alt;
  alt = micros();
  printTheBuffer();
}

void monoToRGB(int letter, int start, int r , int g, int b) {//buchstaben aus dem Ascii array in Farbe in den Displaybuffer schreiben
    for (int i = start; i < start + 5; i++) {
      byteToRGB(ascii[letter - 32 ][i - start],i,r,g,b);
    }
}

void byteToRGB(uint8_t val, int start, int r , int g, int b) {//einzelnes byte in den Displaybuffer schreiben
  if (start < ARRAYLEN - 1) {
    for (int j = 0; j < 8; j++) {
      if (val & 1) {
        buffer[start][7 - j][0] = g;
        buffer[start][7 - j][1] = r;
        buffer[start][7 - j][2] = b;
      }
      else {
        buffer[start][7 - j][0] = 0;
        buffer[start][7 - j][1] = 0;
        buffer[start][7 - j][2] = 0;
      }
      val >>= 1;
    }
  }
}


void showBuffer(int spalte) {//eine Spalte des Buffers an die LEDs weitergeben
  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 3; j++) {
      send12Bit(buffer[spalte][i][j]);
    }
  }
  latch();
}



/*
Zum Ansteuern der LEDs wird ein TLC5947 (http://www.ti.com/lit/ds/symlink/tlc5947.pdf ) verwendet.
Pro LED müssen bei diesem 12 bit(4096 stufen) an helligkeitsdaten seriell übertragen werden. Da 
die hardwareseitig eingebaute SPI- schnittstelle des arduino nur jeweils 8 bit ausgeben kann werden
die daten hier "manuell" übertragen. Da digitalWrite() viel zu langsam ist werden die Ports direkt angesprochen.
(erreichte geschwindigkeit ~= 70% der von SPI, es lohnt sich also nicht aufwändige bitmanipulation zu betreiben,
um das schnellere spi verwenden zu können)
*/
void send12Bit(uint16_t data)
{
  for (int i = 0; i < 12; i++)
  {
    if (data & 2048)
    {//          PINS
      //    Signal:10|9:Clock
      PORTB = 0b00000100;
      PORTB = 0b00000110;
      PORTB = 0b00000000;
      //Signal wird bei rising Edge der CLK eingelesen, deswegen ist gleichzeitig aus ok
    }
    else {
      
      PORTB = 0b00000000;
      PORTB = 0b00000010;
      //oben werden vom compiler 2 Takte Verschenkt, deswegen hier 2 "unnötige" damit das Timing konstant bleibt
      PORTB = 0b00000010;
      PORTB = 0b00000010;

      PORTB = 0b00000000;
    }

    data <<= 1 ;
  }

}

void latch() //Pin8 nach dem übertragen der 288 bit kurz umschalten, damit die Daten vom tlc5947 ausgegeben werden
{
  PORTB = 0b00000001;
  PORTB = 0b00001001;
  PORTB = 0;
}






