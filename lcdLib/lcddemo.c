/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

#define LED BIT6

int redrawScreen = 1;

int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  switch_init();
  clearScreen(COLOR_LIME_GREEN);
  enableWDTInterrupts();
  or_sr(0x8);
  drawBunny();
  eyes_status = 1;
  mouth = 2;
  happy = 1;
  drawString5x7(40, 20, "Margaret", COLOR_WHITE, COLOR_LIME_GREEN);
  open_eyes = 1;
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      update_eyes(eyes_status);
      if(!ball)
	drawMouth(mouth);
      else
	drawOpenSmile();
    }
    P1OUT &= ~LED;
    or_sr(0x10);
    P1OUT |= LED;
  }
}

void wdt_c_handler()
{
  static int sec_mouth = 0;
  static int sec_eyes = 0;
  if(open_eyes){
    if(sec_eyes++ >= 1250) {
      sec_eyes = 0;
      eyes_status = 0;
      if(happy)
	redrawScreen = 1;
    }
    if(sec_eyes++ >= 200 && !eyes_status) {
      sec_eyes = 0;
      eyes_status = 1;
      if(happy)
	redrawScreen = 1;
    }
  }
  else{
    eyes_status = 0;
    if(sec_eyes++ >= 2000){
      sec_eyes = 0;
      open_eyes = 1;
    }
  }
  if(sleep){
    sec_mouth = 0;
    if(sec_sleep++ >= 2000){
      sec_sleep = 0;
      mouth = 2;
      sec_mouth = -750;
      sleep = 0;
      clearBtm();
    }
  }
  if(carrot){
    if(sec_carrot++ >= 1250){
      sec_carrot = 0;
      sec_mouth = 750;
      carrot = 0;
      clearBtm();
    }
  }
  if(soap){
    sec_mouth = 0;
    if(sec_soap++ >= 2000){
      sec_soap = 0;
      mouth = 2;
      sec_mouth = -750;
      soap = 0;
      clearBtm();
    }
  }
  if(ball){
    if(sec_ball++ >= 2000){
      sec_ball = 0;
      mouth = 2;
      sec_mouth = -750;
      ball = 0;
      clearBtm();
    }
  }
  if(!btnPress)
    sec_noBtnPress++;
  if(btnPress)
    btnPress = 0;
  if(sec_mouth++ >= 1250 && sec_noBtnPress >= 1250){
    sec_mouth = 0;
    if(mouth > 0)
      mouth--;
    else
      mouth = 0;
    if(!mouth && sec_noBtnPress >= 1250){
      happy = 0;
      drawFrown();
      redrawScreen = 0;
    }
  }
}
