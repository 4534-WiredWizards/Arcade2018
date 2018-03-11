#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#define PIN 9
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,

  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +

  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,

  NEO_GRB            + NEO_KHZ800);

uint16_t colors[] = {
  matrix.Color(255, 255, 255), matrix.Color(0, 255, 0)
};
double framerate = 300l;
double delaytime = 1000000/framerate;
void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

unsigned long loopstart = 0;
float xp1 = 2;
float yp1 = 14;
float prevXp1 = 2;
float prevYp1 = 15;
int dirp1 = 2;
int pixelNumberp1;
float p1timera = 0;
float p1timerb = 0;
float xp2 = 13;
float yp2 = 1;
float prevXp2 = 13;
float prevYp2 = 0;
int dirp2 = 1;
int pixelNumberp2;
float spood = 0.07;
int timeout = 0;
void loop() {
  //Auto mode
  if (timeout > 1) timeout--;
  else
  {
    if(random(1, 20) == 1)
    {
    if(random(1, 3) == 1)
    {
    dirp1 = 4;
    }
    else{
    dirp1 = 2;
    }
    }
if(random(1, 20) == 1)
    {
    if(random(1, 3) == 1)
    {
   dirp2 = 1;
    }
    else{
   dirp2 = 3;
  }
    }
  }
//Controls
  if(digitalRead(2) == false && dirp1 != 3)
  {
    timeout = 500;
    dirp2 = 2;
  }
  if(digitalRead(3) == false && dirp1 != 4)
  {
    timeout = 500;
    dirp2 = 1;
  }
  if(digitalRead(4) == false && dirp1 != 2)
  {
    timeout = 500;
    dirp2 = 3;
  }
  if(digitalRead(5) == false && dirp1 != 1)
  {
    timeout = 500;
    dirp2 = 4;
  }
  switch(dirp1)
  {
    case 1: 
      xp1 = xp1 - spood;
      break;
    case 2: 
      yp1 = yp1 - spood;
      break;
    case 3: 
      yp1 = yp1 + spood;
      break;
    case 4: 
      xp1 = xp1 + spood;
      break;
  }
  if(analogRead(A4) == 1022 && dirp1 != 3)
  {
    timeout = 500;
    dirp1 = 2;
  }
  if(analogRead(A1) == 1022 && dirp1 != 4)
  {
    timeout = 500;
    dirp1 = 1;
  }
  if(analogRead(A2) == 1022 && dirp1 != 2)
  {
    timeout = 500;
    dirp1 = 3;
  }
  if(analogRead(A3) == 1022 && dirp1 != 1)
  {
    timeout = 500;
    dirp1 = 4;
  }
  switch(dirp2)
  {
    case 1: 
      xp2 = xp2 - spood;
      break;
    case 2: 
      yp2 = yp2 - spood;
      break;
    case 3: 
      yp2 = yp2 + spood;
      break;
    case 4: 
      xp2 = xp2 + spood;
      break;
  }


  if(xp1 > 15) xp1 = 0;
  if(xp1 < 0) xp1 = 15;
  if(yp1 > 15) yp1 = 0;
  if(yp1 < 0) yp1 = 15;
  if(xp2 > 15) xp2 = 0;
  if(xp2 < 0) xp2 = 15;
  if(yp2 > 15) yp2 = 0;
  if(yp2 < 0) yp2 = 15;

  
  if(round(prevXp1) != round(xp1) || round(prevYp1) != round(yp1))
  {
  matrix.drawPixel(round(prevXp1), round(prevYp1),matrix.Color(255,255,0));
  }
  prevXp1 = xp1;
  prevYp1 = yp1;
  loopstart = micros();
  if (round(xp1) % 2 == 1)  // if y is odd
  pixelNumberp1 = (abs(round(xp1) - 15) * 16) + (15 - abs(round(yp1)));
  else  //y is even
  pixelNumberp1 = (abs(round(xp1) - 15) * 16) + abs((round(yp1)));

  if(round(prevXp2) != round(xp2) || round(prevYp2) != round(yp2))
  {
  matrix.drawPixel(round(prevXp2), round(prevYp2),matrix.Color(0,0,255));
  }
  prevXp2 = xp2;
  prevYp2 = yp2;
  loopstart = micros();
  if (round(xp2) % 2 == 1)  // if y is odd
  pixelNumberp2 = (abs(round(xp2) - 15) * 16) + (15 - abs(round(yp2)));
  else  //y is even
  pixelNumberp2 = (abs(round(xp2) - 15) * 16) + abs((round(yp2)));
  matrix.show();
  if(matrix.getPixelColor(pixelNumberp1) == 14013696 || matrix.getPixelColor(pixelNumberp1) == 213)
  {
    dirp1 = 0;
    dirp2 = 0;
    for(int i = 1; i < 10; i++)
    {
      matrix.setPixelColor(pixelNumberp1, 255, 0, 0);
      matrix.show();
      delay(100);
      matrix.setPixelColor(pixelNumberp1, 255, 127, 0);
      matrix.show();
      delay(100);
    }
    if(matrix.getPixelColor(pixelNumberp2) == 13969920 || matrix.getPixelColor(pixelNumberp2) == 14013696 || pixelNumberp1 == pixelNumberp2)
    {
    matrix.fillScreen(matrix.Color(127, 0, 0));
    }
    else
    {
    matrix.fillScreen(matrix.Color(0, 0, 127));
    }
    matrix.show();
    delay(2000);
    reset();
  }
  matrix.drawPixel(round(xp1), round(yp1),matrix.Color(255,127,0));

  if(matrix.getPixelColor(pixelNumberp2) == 213 || matrix.getPixelColor(pixelNumberp2) == 14013696)
  {
    dirp2 = 0;
    dirp1 = 0;
    for(int i = 1; i < 10; i++)
    {
      matrix.setPixelColor(pixelNumberp2, 255, 0, 0);
      matrix.show();
      delay(100);
      matrix.setPixelColor(pixelNumberp2, 127, 0, 255);
      matrix.show();
      delay(100);
    }
    matrix.fillScreen(matrix.Color(127, 127, 0));
    matrix.show();
    delay(2000);
    reset();
  }
  matrix.drawPixel(round(xp2), round(yp2),matrix.Color(255, 0, 255));
  
  if(delaytime > micros() - loopstart){

    delayMicroseconds(delaytime - (micros() - loopstart));

  }
  Serial.println(matrix.getPixelColor(5));

}

void reset() {
  matrix.fillScreen(0);
  xp1 = 2;
  yp1 = 14;
  prevXp1 = 2;
  prevYp1 = 15;
  dirp1 = 2;
  pixelNumberp1;
  p1timera = 0;
  p1timerb = 0;
  xp2 = 13;
  yp2 = 1;
  prevXp2 = 13;
  prevYp2 = 0;
  dirp2 = 3;
  pixelNumberp2;
  spood = 0.07;
}
