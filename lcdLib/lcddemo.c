/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

void drawHourglass(int, int, int, u_int);
void drawCat();

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a > b ? b : a; }
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_LIME_GREEN);
  /*
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  */
  //fillRectangle(25, 25, 60, 60, COLOR_RED);
  //drawCat();
  drawBunny();
  //drawOpenEyes();
  drawClosedEyes();
  //drawClosedMouth();
  drawOpenMouth();
  /**/
  //drawHourglass(screenWidth >> 1, screenHeight >> 1, 30, COLOR_PINK);
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

void drawBunny(){
  fillRectangle(31, 69, 64, 45, COLOR_WHITE);
  fillRectangle(31, 39, 16, 30, COLOR_WHITE);
  fillRectangle(79, 39, 16, 30, COLOR_WHITE);
  fillRectangle(35, 44, 8, 25, COLOR_PINK);
  fillRectangle(83, 44, 8, 25, COLOR_PINK);
}

void drawOpenEyes(){
  fillRectangle(43, 79, 10, 10, COLOR_RED);
  fillRectangle(73, 79, 10, 10, COLOR_RED);
}


void drawClosedMouth(){
  fillRectangle(57, 100, 12, 2, COLOR_PINK);  
}

void drawOpenMouth(){
  fillRectangle(57, 98, 12, 7, COLOR_PINK);
}

void drawClosedEyes(){
  fillRectangle(43, 86, 10, 3, COLOR_PINK);
  fillRectangle(73, 86, 10, 3, COLOR_PINK);
}
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

//Todo- draw rectangle, draw diamond, make functions
