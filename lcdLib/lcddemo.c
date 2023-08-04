/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED BIT6

void drawHourglass(int, int, int, u_int);
void drawCat();
int eyes_status = 1; //1 for open, 0 for closed
int mouth_status = 0; //1 for open, 0 for closed
int redrawScreen = 1;
int mouth = 2; //neutral

//int max(int a, int b) { return a > b ? a : b; }
//int min(int a, int b) { return a > b ? b : a; }
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_LIME_GREEN);
  enableWDTInterrupts();
  or_sr(0x8);
  drawBunny();
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      //drawBunny();
      update_eyes();
      //drawSmile();
      drawMouth();
      //drawClosedMouth();
    }
    P1OUT &= ~LED;
    or_sr(0x10);
    P1OUT |= LED;
  }
  /*
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  */
  //fillRectangle(25, 25, 60, 60, COLOR_RED);
  //drawCat();
  //drawBunny();
  //drawOpenEyes();
  //drawClosedEyes();
  //drawClosedMouth();
  //drawOpenMouth();
  /**/
  //drawHourglass(screenWidth >> 1, screenHeight >> 1, 30, COLOR_PINK);
}

void update_eyes()
{
  if(eyes_status)
    drawOpenEyes();
  else
    drawClosedEyes();
}

void drawCat()
{
  fillRectangle(41, 38, 40, 27, COLOR_PINK);
  fillRectangle(41, 28, 9, 10, COLOR_PINK);
  fillRectangle(72, 28, 9, 10, COLOR_PINK);
  fillRectangle(46, 44, 10, 14, COLOR_WHITE);
  fillRectangle(66, 44, 10, 14, COLOR_WHITE);
  fillRectangle(48, 44, 7, 10, COLOR_BLACK);
  fillRectangle(67, 44, 7, 10, COLOR_BLACK);
}

void drawBunny()
{
  fillRectangle(31, 69, 64, 45, COLOR_WHITE);
  fillRectangle(31, 39, 16, 30, COLOR_WHITE);
  fillRectangle(79, 39, 16, 30, COLOR_WHITE);
  fillRectangle(35, 44, 8, 25, COLOR_PINK);
  fillRectangle(83, 44, 8, 25, COLOR_PINK);
}

void drawOpenEyes()
{
  fillRectangle(43, 79, 10, 10, COLOR_RED);
  fillRectangle(73, 79, 10, 10, COLOR_RED);
}


void drawClosedMouth()
{
  fillRectangle(53, 96, 20, 12, COLOR_WHITE);
  fillRectangle(57, 100, 12, 2, COLOR_PINK);  
}

void drawSmile()
{
  drawClosedMouth();
  fillRectangle(55, 98, 2, 2, COLOR_PINK);
  fillRectangle(53, 96, 2, 2, COLOR_PINK);
  fillRectangle(69, 98, 2, 2, COLOR_PINK);
  fillRectangle(71, 96, 2, 2, COLOR_PINK);
}

void drawFrown()
{
  drawClosedMouth();
  fillRectangle(55, 102, 2, 2, COLOR_PINK);
  fillRectangle(53, 104, 2, 2, COLOR_PINK);
  fillRectangle(69, 102, 2, 2, COLOR_PINK);
  fillRectangle(71, 104, 2, 2, COLOR_PINK);
}

void drawOpenMouth()
{
  drawClosedMouth();
  fillRectangle(57, 98, 12, 7, COLOR_PINK);
}

void drawMouth()
{
  switch(mouth){
  case 0:
    drawFrown();
    break;
  case 1:
    drawClosedMouth();
    break;
  case 2:
    drawSmile();
    break;
  default:
    drawOpenMouth();
  }
}

void drawClosedEyes()
{
  fillRectangle(43, 79, 10, 10, COLOR_WHITE);
  fillRectangle(73, 79, 10, 10, COLOR_WHITE);
  fillRectangle(43, 86, 10, 3, COLOR_PINK);
  fillRectangle(73, 86, 10, 3, COLOR_PINK);
}
/*
void drawHourglass(int controlCol, int controlRow, int size, u_int color)
{
  int c = 0;
  int r = 0;
  for(int j = 0; j < 30; j++){
    int upper = min(-r, +r);
    int lower = max(-r, +r);
    int drawCol = c;
    for(int drawRow = upper; drawRow <= lower; drawRow++){
      drawPixel(controlCol+drawCol, controlRow+drawRow, color);
      drawPixel(controlCol-drawCol, controlRow+drawRow, color);
    }
    c+=1;
    r+=1;
  }
}
*/
//Todo- draw rectangle, draw diamond, make functions
void wdt_c_handler()
{
  static int sec_mouth = 0;
  static int sec_eyes = 0;
  if(sec_eyes++ >= 1250) {
    sec_eyes = 0;
    eyes_status = 0;
    redrawScreen = 1;
  }
  if(sec_eyes++ >= 200 && !eyes_status) {
    sec_eyes = 0;
    eyes_status = 1;
    redrawScreen = 1;
  }

  if(sec_mouth++ >= 1250){
    sec_mouth = 0;
    if(mouth > 0)
      mouth--;
    else
      mouth = 2;
    redrawScreen = 1;
  }
}
