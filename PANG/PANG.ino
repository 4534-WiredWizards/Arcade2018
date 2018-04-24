#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 9
#define ONE_LEFT 5
#define ONE_UP 4
#define ONE_RIGHT 3
#define ONE_DOWN 2
#define ONE_FIRE 6
#define TWO_LEFT 28
#define TWO_UP 26
#define TWO_RIGHT 24
#define TWO_DOWN 30
#define TWO_FIRE 22
#define RESTART 10
#define SELECT_GAME 8
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

uint16_t colors[] = {
  matrix.Color(255, 255, 255), matrix.Color(0, 255, 0)};
double framerate = 300l;
double delaytime = 1000000/framerate;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(RESTART, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
}
int w = matrix.width();
double cursorxtop = matrix.width();
double cursorxbot = matrix.width();
double p1 = 0;
double p2 = 0;
unsigned long loopstart = 0;
double ballxmovement = .1;
double ballymovement = .1;
double ballx = 7;
double bally = 7;
double ballmaxychange = .1;
bool gameover = false;
double AA = 1;
double cycle = 0;
//uint16_t color[] = {
//  matrix.Color(255,255,255),};
void loop() {
//  Serial.println("one left");
//  Serial.println(digitalRead(ONE_LEFT));
//  Serial.println("one right");
//  Serial.println(digitalRead(ONE_RIGHT));
//  Serial.println("one up");
//  Serial.println(digitalRead(ONE_UP));
//  Serial.println("one down");
//  Serial.println(digitalRead(ONE_DOWN));
//  Serial.println("one fire");
//  Serial.println(digitalRead(ONE_FIRE));
//  Serial.println("two up");
//  Serial.println(digitalRead(TWO_UP));
//  Serial.println("two left");
//  Serial.println(digitalRead(TWO_LEFT));
//  Serial.println("two down");
//  Serial.println(digitalRead(TWO_DOWN));
//  Serial.println("two right");
//  Serial.println(digitalRead(TWO_RIGHT));
//  Serial.println("two fire");
//  Serial.println(digitalRead(TWO_FIRE));
//  Serial.println("restart");
//  Serial.println(digitalRead(RESTART));
//  Serial.println("select game");
//  Serial.println(digitalRead(SELECT_GAME));
  loopstart = micros();
  matrix.fillScreen(0);
  // put your main code here, to run repeatedly:
  if(gameover == false){
    for(int i = 0; i < 1 ; i++){
      ballx = ballx + ballxmovement;
      bally = bally + ballymovement;
//      matrix.drawPixel(ballx,bally,matrix.Color(0,255,0));
      if(ballx < 0 && (abs((p1) - bally)) <= 2){
        ballxmovement = -ballxmovement;
        if(ballymovement < 0){
          ballymovement = ballmaxychange*((-(p1) + bally)/2.0);
        }else{
          ballymovement = ballmaxychange*((+(p1) - bally)/2.0);
        }
      } else if(ballx < 0){
        gameover = true;
        
      } else if(ballx > 15 && (abs((p2) - bally)) <= 2){
        ballxmovement = -ballxmovement;
        if(ballymovement < 0){
          ballymovement = ballmaxychange*(((p1) - bally)/2.0);
        }else{
          ballymovement = ballmaxychange*((-(p1) + bally)/2.0);
        }
      }else if(ballx > 15){
        gameover = true;
      }
      if(bally < 0 || bally > 15){
        ballymovement = -ballymovement;
      }
    }
    for(int x = 0; x < 16; x++){
      for(int y = 0; y < 16; y++){
        if(x <= (ballx+1) && x >= (ballx-1) && y <= (bally+1) && y >= (bally-1)){
          AA = sqrt(sq(ballx-x) + sq(bally-y));
          AA = (sqrt(2)-AA)/sqrt(2);
        }else{
          AA = 0;
        }
        matrix.drawPixel(x,y,matrix.Color(255*AA,255*AA,255*AA));
      }
    }
    if( digitalRead(ONE_DOWN) == false && p1 < 14){
      p1 = p1+.4;
    }else if( digitalRead(ONE_UP) == false && p1 > 2){
      p1 = p1-.4;
    }
    //matrix.drawFastVLine(0,p1,4,colors[0]);
    if(digitalRead(TWO_DOWN) == false && p2 < 14){
      p2 = p2+.4;
    }else if(digitalRead(TWO_UP) == false && p2 > 2){
      p2 = p2-.4;
    }
    //matrix.drawFastVLine(15,p2,4,colors[0]);
    for(int i = 0; i < 8; i++){
      if(i <= 3){
        matrix.drawPixel(0,p1+i-2,matrix.Color(255,255,255));
      }else{
        matrix.drawPixel(15,p2+(i-4)-2,matrix.Color(255,255,255));
      }
    }
//    Serial.println((delaytime - (micros() - loopstart)));
//    Serial.println(delaytime);
    if(delaytime > micros() - loopstart){
      delayMicroseconds(delaytime - (micros() - loopstart));
    }
    matrix.show();
    

    
  }else{
    if(digitalRead(RESTART) == false){
      gameover = false;
      ballx = 7;
      bally = 7;
      ballymovement = random(-1,1)/10.0;
      ballxmovement = .1;
      cursorxtop = w;
    }
    if(cycle == 0){
      matrix.setCursor(cursorxtop,0);
      matrix.print(F("Game Over"));
      matrix.setTextColor(matrix.Color(255,0,0));
      cursorxtop = cursorxtop - .1;
    if(cursorxtop < -53){
      cursorxtop = w;
      cycle++;
    }
    matrix.show();
    }else{
      matrix.print(F("Wired Wizards Wired Wizards"));
      matrix.setTextColor(matrix.Color(255,255,255));
      cursorxtop = cursorxtop - .15;
      if(cursorxtop < -30){
         cursorxtop = 0;
      }
      matrix.setCursor(cursorxtop,0);
      matrix.show();
      matrix.print(F("4534 4534"));
      matrix.setTextColor(matrix.Color(255,0,0));
      cursorxbot = cursorxbot - .15;
      if(cursorxbot < -163){
         cursorxbot = 0;
      }
      matrix.setCursor(cursorxbot,7);
      matrix.show();
    }
  }
}
//Worst Me-Me of all time:
//someeee
//body once toucha 
//my sphaget
//i aint the sharpest tool in the shed
