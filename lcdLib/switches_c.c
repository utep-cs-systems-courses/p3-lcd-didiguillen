#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

extern int state;
extern int redrawScreen;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

int switches = 0;

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
  sec_noBtnPress = -1250;
  btnPress = 1;
  redrawScreen = 1;
}

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if(P2IFG & SW1){
    P2IFG &= ~SW1;
    switch_interrupt_handler();
    clearBtm();
    state_select(1);
  }
  else if(P2IFG & SW2){
    P2IFG &= ~SW2;
    switch_interrupt_handler();
    clearBtm();
    state_select(2);
  }
  else if(P2IFG & SW3){
    P2IFG &= ~SW3;
    switch_interrupt_handler();
    clearBtm();
    state_select(3);
  }
  else if(P2IFG & SW4){
    P2IFG &= ~SW4;
    switch_interrupt_handler();
    clearBtm();
    state_select(4);
  }
}
