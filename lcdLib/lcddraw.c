/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawChar11x16(u_char rcol, u_char rrow, char c, u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 10, rrow + 16);
  while(row < 17){
    while(col < 11){
      u_int colorBGR = (font_11x16[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

void drawString11x16(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while(*string){
    drawChar11x16(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols+= 12;
  }
}
/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

void drawBunny()
{
  fillRectangle(31, 69, 64, 45, COLOR_WHITE); //head
  fillRectangle(31, 39, 16, 30, COLOR_WHITE); //left ear
  fillRectangle(79, 39, 16, 30, COLOR_WHITE); //right ear
  fillRectangle(35, 44, 8, 25, COLOR_PINK); //inner ear
  fillRectangle(83, 44, 8, 25, COLOR_PINK);
}

void drawOpenEyes()
{
  fillRectangle(43, 79, 10, 10, COLOR_RED);
  fillRectangle(73, 79, 10, 10, COLOR_RED);
}

void drawClosedEyes()
{
  fillRectangle(43, 79, 10, 10, COLOR_WHITE);
  fillRectangle(73, 79, 10, 10, COLOR_WHITE);
  fillRectangle(43, 86, 10, 3, COLOR_PINK);
  fillRectangle(73, 86, 10, 3, COLOR_PINK);
}

//try converting to assy?
void update_eyes(int eyes_status)
{
  if(eyes_status)
    drawOpenEyes();
  else
    drawClosedEyes();
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
  drawClosedEyes();
  fillRectangle(40, 89, 4, 4, COLOR_SKY_BLUE);
  fillRectangle(82, 89, 4, 4, COLOR_SKY_BLUE);
}

void drawOpenMouth()
{
  drawClosedMouth();
  fillRectangle(57, 98, 12, 7, COLOR_PINK);
}

void drawMouth(int mouth)
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

void drawCarrot()
{
  fillRectangle(54, 128, 20, 10, COLOR_ORANGE);
  fillRectangle(52, 129, 2, 8, COLOR_ORANGE);
  fillRectangle(50, 130, 2, 6, COLOR_ORANGE);
  fillRectangle(48, 131, 2, 4, COLOR_ORANGE);
  fillRectangle(46, 132, 2, 2, COLOR_ORANGE);
  fillRectangle(74, 131, 4, 4, COLOR_FOREST_GREEN);
  fillRectangle(78, 127, 4, 4, COLOR_FOREST_GREEN);
  fillRectangle(78, 135, 4, 4, COLOR_FOREST_GREEN);
}
